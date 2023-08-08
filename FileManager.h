#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "Game.h"

using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

class FileManager
{
public:
	FileManager(const char* path);
	~FileManager();

	void normalize(string &str);
	void writeFile(const char* path, string str);
	vector<string> getData();

private:
	vector<string> arr;
};
