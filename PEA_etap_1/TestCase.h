#pragma once
#include <string>
#include "Enums.h"
class TestCase
{
public:

	TestCase();
	
	TestCase(bool _isFromFile, std::string _fileName, int _size, algorithmEnum _algorithm , int _howManyTests);

	bool getIsFromFile();

	std::string getFileName();

	int getSize();

	int getAlgorithm();

	int getHowManyTests();

	void setIsFromFile(bool _isFromFile);

	void setFileName(std::string _fileName);

	void setSize(int _size);

	void setAlgorithm(algorithmEnum _algorithm);

	void setHowManyTests(int _howManyTests);

private:

	bool isFromFile;
	std::string fileName;
	int size;
	int algorithm;
	int howManyTests;
};

