#include "src/Matrix.h"
#include <cassert>

int main()
{
	matrix::Matrix<int, 0> mat;
	const auto diagonal = 10;

	for (auto i = 0; i < diagonal; ++i)
	{
		mat[i][i] = i;

		mat[i][diagonal - i - 1] = diagonal - i - 1;
	}

	for (auto i = 1; i < 9; ++i)
	{
		for (auto j = 1; j < 9; ++j)
		{
			std::cout << mat[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "matrix size: " << mat.size() << std::endl;

	mat.Print();

	return 0;
}