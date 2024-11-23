#include "DuplicateFileFinder.h"
#include <boost/algorithm/hex.hpp>
#include <boost/crc.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/regex.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <fstream>
#include <iostream>

namespace
{
void PrintFiles(const std::vector<std::string>& files)
{
	for (const auto& file : files)
	{
		std::cout << file << std::endl;
	}

	std::cout << std::endl;
}
} // namespace

class DuplicateFileFinder::Impl
{
	struct File
	{
		File(const boost::filesystem::path& originalPath, size_t originalSize)
			: path{ originalPath }
			, size{ originalSize }
		{
		}

		boost::filesystem::path path;
		std::vector<std::string> hash;
		size_t size;
		bool processed = false;
	};

public:
	Impl(InputData data)
		: m_data{ std::move(data) }
	{
	}

	void Find()
	{
		IndexAllFiles();
		FindDuplicates();
	}

	void FindDuplicates()
	{
		for (size_t i = 0; i < m_files.size(); i++)
		{
			std::vector<std::string> duplicateFiles;
			if (m_files[i].processed)
			{
				continue;
			}

			for (size_t j = i + 1; j < m_files.size(); j++)
			{
				if (m_files[i].size != m_files[j].size)
				{
					continue;
				}

				if (!CheckFilesHash(m_files[i], m_files[j]))
				{
					continue;
				}

				duplicateFiles.push_back(m_files[j].path.c_str());
			}

			if (!duplicateFiles.empty())
			{
				duplicateFiles.push_back(m_files[i].path.c_str());
				PrintFiles(duplicateFiles);
			}
		}
	}

	bool CheckFilesHash(File& first, File& second)
	{
		const auto bufferSize = m_data.GetBufferSize();
		size_t bufferBlocksCount = first.size / bufferSize;

		if (first.size % bufferSize)
		{
			bufferBlocksCount++;
		}

		for (size_t bufferBlockNumber = 0; bufferBlockNumber < bufferBlocksCount; bufferBlockNumber++)
		{
			if (bufferBlockNumber == first.hash.size())
			{
				CalculateFileHash(first, bufferBlockNumber);
			}

			if (bufferBlockNumber == second.hash.size())
			{
				CalculateFileHash(second, bufferBlockNumber);
			}

			if (first.hash.size() != second.hash.size())
			{
				return false;
			}

			if (first.hash[bufferBlockNumber] != second.hash[bufferBlockNumber])
			{
				return false;
			}
		}

		first.processed = true;
		second.processed = true;
		return true;
	}

	void CalculateFileHash(File& file, size_t bufferBlockNumber)
	{
		const auto bufferSize = m_data.GetBufferSize();
		std::vector<char> buffer;
		buffer.reserve(bufferSize);

		memset(buffer.data(), 0, bufferSize);
		std::ifstream fd(file.path, std::ifstream::binary);
		fd.seekg(bufferBlockNumber * bufferSize);
		fd.read(buffer.data(), bufferSize);

		if (m_data.GetHashAlgorithm() == HashAlgorithm::CRC32)
		{
			boost::crc_32_type hash;
			hash.process_bytes(buffer.data(), bufferSize);
			file.hash.push_back(std::to_string(hash.checksum()));
		}
		else
		{
			boost::uuids::detail::md5 hash;
			boost::uuids::detail::md5::digest_type digest;

			hash.process_bytes(buffer.data(), bufferSize);
			hash.get_digest(digest);

			const auto charDigest = reinterpret_cast<const char*>(&digest);
			std::string result;
			boost::algorithm::hex(charDigest, charDigest + sizeof(boost::uuids::detail::md5::digest_type), std::back_inserter(result));

			file.hash.push_back(result);
		}
	}

	void IndexAllFiles()
	{
		for (const auto& path : m_data.GetScanDirs())
		{
			if (m_data.ScanAllDirs())
			{
				ProcessFolder<boost::filesystem::recursive_directory_iterator>(path);
			}
			else
			{
				ProcessFolder<boost::filesystem::directory_iterator>(path);
			}
		}
	}

	template <typename T>
	void ProcessFolder(const std::string& path)
	{
		auto isSubpath = [](const auto& childPath,
							 const auto& parentPath) -> bool {
			auto relativePath = boost::filesystem::relative(childPath, parentPath);
			return !relativePath.empty() && relativePath.native()[0] != '.';
		};

		for (T iter{ path }; iter != T{}; iter++)
		{
			const auto& currentPath = *iter;
			const auto status = boost::filesystem::status(currentPath);

			if (status.type() != boost::filesystem::regular_file)
			{
				continue;
			}

			if (std::any_of(m_data.GetExcludeScanDirs().cbegin(),
					m_data.GetExcludeScanDirs().cend(),
					[&](const auto& excludedPath) {
						return isSubpath(currentPath.path(), excludedPath);
					}))
			{
				continue;
			}

			if (boost::filesystem::file_size(currentPath.path()) < m_data.GetMinFileSize())
			{
				continue;
			}

			if (const auto& masks = m_data.GetFileMasks(); !masks.empty())
			{
				if (!std::any_of(masks.begin(), masks.end(), [&currentPath](const auto& mask) {
						return boost::regex_match(currentPath.path().filename().string(), boost::regex{ mask });
					}))
				{
					continue;
				}
			}

			m_files.emplace_back(currentPath.path(), boost::filesystem::file_size(currentPath.path()));
		}
	}

private:
	InputData m_data;
	std::vector<File> m_files;
};

DuplicateFileFinder::DuplicateFileFinder(InputData data)
	: m_impl{ std::make_shared<Impl>(std::move(data)) }
{
}

void DuplicateFileFinder::Find()
{
	m_impl->Find();
}
