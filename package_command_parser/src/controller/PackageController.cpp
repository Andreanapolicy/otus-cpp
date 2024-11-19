#include "PackageController.h"
#include "../block/Block.h"
#include <numeric>

namespace
{
std::string BLOCK_START_SYMBOL = "{";
std::string BLOCK_END_SYMBOL = "}";

using NativeStorage = std::vector<std::pair<std::string, std::chrono::system_clock::time_point>>;
} // namespace

class PackageController::Storage
{
public:
	Storage(int capacity)
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
	block::Block<std::string> m_unlimitedCache{ -1 };
	size_t m_nestingLevel = 0;
};

PackageController::PackageController(std::istream& input, std::ostream& defaultOutput, int blockCapacity)
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
		if (isDynamicBlock)
		{
			m_storage->StoreInUnlimitedCache(std::move(line));
			continue;
		}

		m_storage->StoreInLimitedCache(std::move(line));

		if (m_storage->IsLimitedCacheFull())
		{
			WriteStoredData(); // output limited cache
			m_storage->ResetLimitedCache();
			continue;
		}

		if (line == BLOCK_START_SYMBOL)
		{
			isDynamicBlock = true;
			m_storage->IncreaseNesting();

			if (m_storage->GetNestingLevel() == 1)
			{
				WriteStoredData(); // output limited cache
				m_storage->ResetLimitedCache();
			}
			continue;
		}

		if (line == BLOCK_END_SYMBOL)
		{
			if (m_storage->GetNestingLevel() == 0)
			{
				isDynamicBlock = false;
				WriteStoredData();
			}
			m_storage->DecreaseNesting();
		}
	}
}

void PackageController::WriteStoredData()
{
	auto writeData = [&](const NativeStorage& data) {
		std::string output;
		std::for_each(
			data.cbegin(),
			data.cend(),
			[&output](const std::pair<std::string, std::chrono::system_clock::time_point>& s) {
				return output.empty() ? s.first : output + "," + s.first;
			});

		m_defaultOutput << output;
	};

	if (const auto& limitedCache = m_storage->GetDataFromLimitedCache(); !limitedCache.empty())
	{
		writeData(limitedCache);
		return;
	}

	if (const auto& unlimitedCache = m_storage->GetDataFromUnlimitedCache(); !unlimitedCache.empty())
	{
		writeData(unlimitedCache);
		return;
	}
}
