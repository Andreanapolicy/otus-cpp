#include "DuplicateFileFinder.h"
#include <boost/crc.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/regex.hpp>
#include <iostream>

class DuplicateFileFinder::Impl
{
	struct File
	{
		File(const boost::filesystem::path& originalPath)
			: path{ originalPath }
		{
		}

		boost::filesystem::path path;
		std::vector<size_t> hash;
		size_t size;
	};

public:
	Impl(InputData data)
		: m_data{ std::move(data) }
	{
		m_buffer.reserve(m_data.GetBufferSize());
		std::cout << "m_buffer.reserve(m_data.GetBufferSize());" << std::endl;
	}

	void Find()
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

			m_files.emplace_back(currentPath.path());
		}
	}

private:
	InputData m_data;
	std::vector<File> m_files;
	std::vector<char> m_buffer;
};

DuplicateFileFinder::DuplicateFileFinder(InputData data)
	: m_impl{ std::make_shared<Impl>(std::move(data)) }
{
}

void DuplicateFileFinder::Find()
{
	m_impl->Find();
}
