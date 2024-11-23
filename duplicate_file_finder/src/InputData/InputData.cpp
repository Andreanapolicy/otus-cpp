#include "InputData.h"
#include "ParseException.h"
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <exception>
#include <iostream>

namespace po = boost::program_options;

class InputData::Impl
{
public:
	Impl(int argc, char** argv)
	{
		po::options_description description("Duplicate file finder");
		// clang-format off
        description.add_options()
            ("help", "produce help message")
            ("include-dirs,i", po::value<std::vector<std::string>>(), "Include dirs to scan")
            ("exclude-dirs,e", po::value<std::vector<std::string>>(), "Exclude dirs to scan")
            ("scan-all-dirs,a", po::value<size_t>()->default_value(0), "Set 1 if scan all dirs recursively")
            ("min-file-size,s", po::value<size_t>()->default_value(1), "Min file size to process")
            ("file-masks,f", po::value<std::vector<std::string>>(), "File masks to scan")
            ("buffer-size,b", po::value<size_t>(), "Buffer size to process file")
            ("hash,hs", po::value<std::string>(), "Hash: md5 or crc32");
		// clang-format on

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, description), vm);
		po::notify(vm);

		if (vm.count("help"))
		{
			std::cout << description << std::endl;
			throw std::logic_error("See --help");
		}

		if (vm.count("include-dirs"))
		{
			m_scanDirs = vm["include-dirs"].as<std::vector<std::string>>();
		}
		else
		{
			throw ParseException("include-dirs is required. See --help");
		}

		if (vm.count("exclude-dirs"))
		{
			m_excludedScanDirs = vm["exclude-dirs"].as<std::vector<std::string>>();
		}

		if (vm.count("scan-all-dirs"))
		{
			m_scanAllDirs = vm["scan-all-dirs"].as<size_t>();
		}

		if (vm.count("min-file-size"))
		{
			m_minFileSize = vm["min-file-size"].as<size_t>();
		}

		if (vm.count("file-masks"))
		{
			m_fileMasks = vm["file-masks"].as<std::vector<std::string>>();
		}

		if (vm.count("buffer-size"))
		{
			m_bufferSize = vm["buffer-size"].as<size_t>();
		}
		else
		{
			throw ParseException("buffer-size is required. See --help");
		}

		if (vm.count("hash"))
		{
			if (const auto hash = vm["hash"].as<std::string>(); hash == "md5" || hash == "crc32")
			{
                m_hash = hash == "mda5" ? HashAlgorithm::MD5 : HashAlgorithm::CRC32;
			}
			else
			{
				throw ParseException("hash must be one of [md5, crc32]");
			}
		}
		else
		{
			throw ParseException("buffer-size is required. See --help");
		}
	}

	const std::vector<std::string>& GetScanDirs() const
	{
		return m_scanDirs;
	}

	const std::vector<std::string>& GetExcludeScanDirs() const
	{
		return m_excludedScanDirs;
	}

	bool ScanAllDirs() const
	{
		return m_scanAllDirs;
	}

	size_t GetMinFileSize() const
	{
		return m_minFileSize;
	}

	const std::vector<std::string>& GetFileMasks() const
	{
		return m_fileMasks;
	}

	size_t GetBufferSize() const
	{
		return m_bufferSize;
	}

	HashAlgorithm GetHashAlgorithm() const
	{
		return m_hash;
	}

private:
	std::vector<std::string> m_scanDirs{};
	std::vector<std::string> m_excludedScanDirs{};
	bool m_scanAllDirs{ false };
	size_t m_minFileSize{ 1 };
	std::vector<std::string> m_fileMasks{};
	size_t m_bufferSize{ 1 };
	HashAlgorithm m_hash{ HashAlgorithm::MD5 };
};

InputData::InputData(int argc, char** argv)
	: m_impl{ std::make_shared<Impl>(argc, argv) }
{
}

const std::vector<std::string>& InputData::GetScanDirs() const
{
	return m_impl->GetScanDirs();
}

const std::vector<std::string>& InputData::GetExcludeScanDirs() const
{
	return m_impl->GetExcludeScanDirs();
}

bool InputData::ScanAllDirs() const
{
	return m_impl->ScanAllDirs();
}

size_t InputData::GetMinFileSize() const
{
	return m_impl->GetMinFileSize();
}

const std::vector<std::string>& InputData::GetFileMasks() const
{
	return m_impl->GetFileMasks();
}

size_t InputData::GetBufferSize() const
{
	return m_impl->GetBufferSize();
}

HashAlgorithm InputData::GetHashAlgorithm() const
{
	return m_impl->GetHashAlgorithm();
}
