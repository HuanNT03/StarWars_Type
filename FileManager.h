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
	void writeFile(string str);
	vector<string> getData();
	string getDataAt(int index);
	long long getSize() { return arr.size(); }

private:
	vector<string> arr;
	const char* filePath;
};
