#include "encodeStr.h"

long encodeStr(std::string& str)
{
	//take string, turn into number. yay.
	//we do this every time the vector gets filled up.
}

bool flushChars(std::vector<int>& vec, std::string filename, int &count, bool check, int vecsize)
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

	//flushes the current vector into the text document, along with encoding it.
	int offset = rand() % 9 + 1; //I know rand() isn't the best but idrc

	std::string mainStr;
	mainStr += std::to_string(offset);

	//make main string
	for (int &str : vec)
	{
		mainStr += '0';
		mainStr += std::to_string(offset + str);
		//result: offset 0 str1 0 str2 0 str3 ... 0 strfinal
	}
	
	if (std::filesystem::exists(filename))
		doesFileExist = true;

	std::fstream textfile(filename, std::ios::out | std::ios::app);
	//check if not open, handle error.
	if (!textfile.is_open())
	{
		++count;
		flushChars(vec, filename, count);
	}


	if (!doesFileExist || std::filesystem::file_size(filename) == 0) //text document empty.
	{
		textfile << "# DO NOT DELETE THIS FILE\n";
	}

	textfile.seekp(0, std::ios::end);
	textfile << mainStr << '\n';
	vec.clear();

	textfile.close();
	return true;
}