#include "PackageController.h"
#include "../block/Block.h"
#include "../logger/Logger.h"

namespace
{
std::string BLOCK_START_SYMBOL = "{";
std::string BLOCK_END_SYMBOL = "}";
std::string DELIMITER = ", ";

using NativeStorage = std::vector<std::pair<std::string, std::chrono::system_clock::time_point>>;

std::filesystem::path CreatePath(auto time)
{
	return std::filesystem::current_path() / ("bulk" + std::to_string(time) + ".log");
}
} // namespace

class PackageController::Storage
{
public:
	Storage(size_t capacity)
		: m_limitedCache{ capacity }
	{
	}

	void IncreaseNesting()
	{
		m_nestingLevel++;
	}

	void DecreaseNesting()
	{
		m_nestingLevel--;
	}

	size_t GetNestingLevel() const
	{
		return m_nestingLevel;
	}

	void StoreInLimitedCache(std::string data)
	{
		m_limitedCache.Push(data);
	}

	void StoreInUnlimitedCache(std::string data)
	{
		m_unlimitedCache.Push(data);
	}

	const NativeStorage& GetDataFromLimitedCache() const
	{
		return m_limitedCache.GetAllData();
	}

	const NativeStorage& GetDataFromUnlimitedCache() const
	{
		return m_unlimitedCache.GetAllData();
	}

	bool IsUnlimitedCacheFull() const
	{
		return m_unlimitedCache.IsFull();
	}

	bool IsLimitedCacheFull() const
	{
		return m_limitedCache.IsFull();
	}

	void ResetLimitedCache()
	{
		return m_limitedCache.Reset();
	}

	void ResetUnlimitedCache()
	{
		return m_unlimitedCache.Reset();
	}

private:
	block::Block<std::string> m_limitedCache;
	block::Block<std::string> m_unlimitedCache{ 0 };
	size_t m_nestingLevel = 0;
};

PackageController::PackageController(std::istream& input, std::ostream& defaultOutput, size_t blockCapacity)
	: m_input{ input }
	, m_defaultOutput{ defaultOutput }
	, m_storage{ std::make_shared<Storage>(blockCapacity) }
{
}

void PackageController::StartProcessCommand()
{
	std::string line;
	bool isDynamicBlock = false;
	while (std::getline(m_input, line))
	{
		if (line == BLOCK_START_SYMBOL)
		{
			isDynamicBlock = true;

			if (m_storage->GetNestingLevel() == 0)
			{
				WriteStoredData();
				m_storage->ResetLimitedCache();
			}

			m_storage->IncreaseNesting();

			continue;
		}

		if (line == BLOCK_END_SYMBOL && isDynamicBlock)
		{
			m_storage->DecreaseNesting();

			if (m_storage->GetNestingLevel() == 0)
			{
				isDynamicBlock = false;
				WriteStoredData();
				m_storage->ResetUnlimitedCache();
			}
			continue;
		}

		if (isDynamicBlock)
		{
			m_storage->StoreInUnlimitedCache(std::move(line));
			continue;
		}

		m_storage->StoreInLimitedCache(std::move(line));

		if (m_storage->IsLimitedCacheFull())
		{
			WriteStoredData();
			m_storage->ResetLimitedCache();
		}
	}

	if (m_storage->GetNestingLevel() == 0)
	{
		WriteStoredData();
	}
}

void PackageController::WriteStoredData()
{
	auto prepareData = [&](const NativeStorage& data) {
		std::string output;
		for (const auto& [str, _] : data)
		{
			output += output.empty() ? str : DELIMITER + str;
		}
		return output;
	};

	std::filesystem::path path;
	std::string data;

	if (const auto& limitedCache = m_storage->GetDataFromLimitedCache(); !limitedCache.empty())
	{
		path = CreatePath(limitedCache[0].second.time_since_epoch().count());
		data = prepareData(limitedCache);
	}
	else if (const auto& unlimitedCache = m_storage->GetDataFromUnlimitedCache(); !unlimitedCache.empty())
	{
		path = CreatePath(unlimitedCache[0].second.time_since_epoch().count());
		data = prepareData(unlimitedCache);
	}

	if (!data.empty())
	{
		m_defaultOutput << data << std::endl;
		logger::Logger::Log(path, data);
	}
}
