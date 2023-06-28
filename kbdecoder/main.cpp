#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <filesystem>
#include <fstream>
#include <vector>

/*
	Decoder logic changed, we're using '|' to separate numbers.
	This is because fucking around with zeroes did not do us too well.
*/

std::vector<int> findNumsBetweenChars(std::string& str, char ch)
{
	std::vector<int> ret{};
	std::string off = str.substr(0, 1);
	int offset = std::stoi(off); //why can't we have choi AND stoi :(

	str.erase(0, 1); //erase offset
	while (str.length() > 0)
	{
		auto first = str.find_first_of(ch);
		auto second = str.find(ch, first + 1);
		auto num = str.substr(first + 1, second - 1);

		auto realnum = std::stoi(num) - offset;
		ret.push_back(realnum);

		str.erase(0, second - first);
	}
	return ret;
}

std::vector<std::string> convToCharWOffset(std::vector<std::string>& vec, int& offset) //use string for shit like backspace
{
	std::vector<std::string> ret{};
	for (std::string str : vec)
	{
		int ch = std::stoi(str) - offset;
		switch (ch)
		{
		case 8:
			ret.push_back("BACKSPACE");
			break;
		case 9:
			ret.push_back("TAB");
			break;
		case 13:
			ret.push_back("ENTER");
			break;
		case 27:
			ret.push_back("ESC");
			break;
		case 32:
			ret.push_back("SPACE");
			break;
		default:
			ret.push_back(std::string(1, (char)ch));
			break;
		}
	}
	return ret;
}

//"0 20 0 30 0"

//0 5 0 65 0 19 0 30 0 5

bool readFile(std::string filename)
{
	std::string line;
	std::ifstream textFile(filename);
	if (textFile.is_open())
	{
		while (std::getline(textFile, line))
		{
			//used for some socialenginnering (#DONT DELETE THIS FILE) at the top or smth
			if (line.find_first_of('#') == std::string::npos)
				continue;

			//operate on the line:
			if (line[0] == 0)
			{
				std::cout << "Massive errror, no offset found!";
				return -1;
			}

			int offset = line[0]; //offset for every single int-basd char.
			line.erase(0, 1); //erase it, we don't need it :)

		}
		textFile.close();
	}
	else
		return false;
}

int main()
{
	std::cout << "Enter test string...\n";
	std::string testStr = "";
	std::cin >> testStr;

	std::vector<int> a = findNumsBetweenChars(testStr, '|');

	for (int integer : a)
	{
		std::cout << integer << '\n';
	}

	
}