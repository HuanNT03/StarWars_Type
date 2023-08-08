#include"FileManager.h"
#include"config.h"

FileManager::FileManager(const char* path)
{
	ifstream data(path);
	if (data.is_open()) 
	{
		cout << "Successful open data file!" << endl;
		string line;
		while (!data.eof())
		{
			data >> line;
			normalize(line);
			arr.push_back(line);
		}
	}
	else
	{
		cout << "Fail to open data file!" << endl;
	}
	data.close();
}

FileManager::~FileManager()
{

}

void FileManager::normalize(string &str)
{
	for(int i = str.size() - 1; i >= 0; i--)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] = str[i] + ('a' - 'A');
		}
		else if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || str[i] == ' ')
		{
			str[i] = str[i];
		}
		else
		{
			str.erase(i,1);
		}
	}
}

void FileManager::writeFile(const char* path, string str)
{

}

vector<string> FileManager::getData()
{
	return arr;
}
