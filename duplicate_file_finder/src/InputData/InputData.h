#pragma once
#include <string>
#include <vector>
#include <memory>

enum class HashAlgorithm
{
	CRC32,
	MD5,
};

class InputData
{
public:
	InputData(int argc, char** argv);

	const std::vector<std::string>& GetScanDirs() const;
	const std::vector<std::string>& GetExcludeScanDirs() const;
	bool ScanAllDirs() const;
	size_t GetMinFileSize() const;
	const std::vector<std::string>& GetFileMasks() const;
	size_t GetBufferSize() const;
	HashAlgorithm GetHashAlgorithm() const;

private:
    class Impl;
    std::shared_ptr<Impl> m_impl;
};