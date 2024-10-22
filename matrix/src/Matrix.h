#pragma once
#include <iostream>
#include <map>

namespace matrix
{
template <typename T, T defaultValue> class MatrixProxy;

template <typename T, T defaultValue>
class Matrix
{
	using Storage = std::map<std::pair<size_t, size_t>, T>;

public:
	using iterator = typename Storage::iterator;
	using const_iterator = typename Storage::const_iterator;

	Matrix() = default;

	size_t size() const
	{
		return m_storage.size();
	}

	iterator begin()
	{
		return m_storage.begin();
	}

	const_iterator cbegin() const
	{
		return m_storage.cbegin();
	}

	iterator end()
	{
		return m_storage.end();
	}

	const_iterator cend() const
	{
		return m_storage.cend();
	}

	void Print() const
	{
		for (const auto& elem : m_storage)
		{
			std::cout << "[" << elem.first.first << ", " << elem.first.second << "] = " << elem.second << std::endl;
		}
	}

	MatrixProxy<T, defaultValue> operator[](size_t row)
	{
		return MatrixProxy<T, defaultValue>(*this, row);
	}

private:
	Storage m_storage{};
	friend MatrixProxy<T, defaultValue>;
};

template <typename T, T defaultValue>
class MatrixProxy
{
public:
	MatrixProxy(Matrix<T, defaultValue>& matrix, size_t row)
		: m_row{ row }
		, m_matrix(matrix)
	{
	}

	MatrixProxy& operator[](size_t column)
	{
		m_column = column;
		return *this;
	}

	void operator=(T value)
	{
		const auto pair = std::make_pair(m_row, m_column);

		if (value == defaultValue)
		{
			auto it = m_matrix.m_storage.find(pair);

			if (it == m_matrix.m_storage.end())
			{
				return;
			}

			m_matrix.m_storage.erase(it);
			return;
		}

		m_matrix.m_storage[pair] = value;
	}

	operator T()
	{
		const auto pair = std::make_pair(m_row, m_column);

		if (m_matrix.m_storage.find(pair) == m_matrix.m_storage.end())
		{
			return defaultValue;
		}

		return m_matrix.m_storage[pair];
	}

private:
	size_t m_row{};
	size_t m_column{};
	Matrix<T, defaultValue>& m_matrix;
};
} // namespace matrix