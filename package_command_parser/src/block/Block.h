#pragma once
#include <chrono>
#include <exception>
#include <vector>

namespace block
{
template <typename T>
class Block
{
	using Storage = std::vector<std::pair<T, std::chrono::system_clock::time_point>>;

public:
	Block(size_t capacity)
		: m_capacity{ capacity }
	{
	}

	void Push(T value)
	{
		if (m_capacity > 0 && IsFull())
		{
			throw std::logic_error("Error, storage is full");
		}

		m_data.emplace_back(std::move(value), std::chrono::system_clock::now());
	}

	const Storage& GetAllData() const
	{
		return m_data;
	}

	bool IsFull() const
	{
		return m_data.size() >= m_capacity;
	}

	void Reset()
	{
		m_data.clear();
	}

private:
	Storage m_data;
	size_t m_capacity;
};

} // namespace block