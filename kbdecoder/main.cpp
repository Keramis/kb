#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <filesystem>
#include <fstream>



bool readFile(std::string filename)
{
	std::string line;
	std::ifstream textFile(filename);
	if (textFile.is_open())
	{
		while (std::getline(textFile, line))
		{
			//operate on the line:

		}
		textFile.close();
	}
	else
		return false;
}

int main()
{
	std::string str = "0helddddlo00000";

}