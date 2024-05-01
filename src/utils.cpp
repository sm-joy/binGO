#include "..\include\utils.hpp"

namespace Utils
{
	int randInt(int pMin, int pMax)
	{
		std::random_device randomDevice;
		std::mt19937 gen(randomDevice());

		std::uniform_int_distribution<int> distribution;

		if (distribution.min() != pMin || distribution.max() != pMax)
			distribution = std::uniform_int_distribution<int>(pMin, pMax);

		return distribution(gen);
	}


	void randIntToStr(int pMin, int pMax, char* pString)
	{
		std::string tempString = std::to_string(randInt(pMin, pMax));
		const char* tempCStr = tempString.c_str();
		pString = new char[tempString.size() + 1];
		
		for (int i = 0; i < tempString.size() + 1; i++)
		{
			*(pString + i) = *(tempCStr + i);
		}
	}



	bool isUnique(Cell** pCells, const char* pString)
	{
		if (pString == nullptr) return false;
		for (int i = 0; i < 5; i++)
		{
			for(int j = 0; i < 6; j++)
			{
				if (pCells[i][j].getText() == nullptr) return true;
				else if (*(pCells[i][j].getText()) == (*pString)) return false;
			}
		}

		return true;
	}

	void print(std::vector<std::vector<std::string>>* pVector)
	{
		for (std::vector<std::string>& vector : *pVector)
		{
			std::cout << "\n[";
			for (std::string& string : vector)
			{
				std::cout << string << ", ";
			}
			std::cout << "]";
		}
	}
	void stringCopy(char* pDestination, const char* pSource, int limit)
	{
		if (pDestination == nullptr || pSource == nullptr) return;

		char* ptrSrc = (char*)pSource;
		char* ptrDst = pDestination;
		int i;
		for (i = 0; i < limit && *ptrSrc != '\0'; i++)
		{
			*(ptrDst + i) = *(ptrSrc + i);
			if (*(ptrDst + i) == '\0') break;
		}
		*(ptrDst + i) = '\0';
	}

};