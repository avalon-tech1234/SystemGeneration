#pragma once
#include <random> 

namespace random
{
	class RandomEngine
	{
	private:
		std::mt19937 gen; // ������� ��������� �����

	public:

		RandomEngine();

		const std::mt19937& getRandomEngine() const;

	};
}


