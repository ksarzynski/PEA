#pragma once
#include <string>
class TestCase
{
public:

	TestCase();
	
	TestCase(bool _isFromFile, std::string _fileName, int _size, int _algorithm, int _howManyTests);

	bool getIsFromFile();

	std::string getFileName();

	int getSize();

	int getAlgorithm();

	int getHowManyTests();

	void setIsFromFile(bool _isFromFile);

	void setFileName(std::string _fileName);

	void setSize(int _size);

	void setAlgorithm(int _algorithm);

	void setHowManyTests(int _howManyTests);

private:

	bool isFromFile;
	std::string fileName;
	int size;
	// 0 - brute force
	// 1 - dynamic
	// 2 - branch and bound
	int algorithm;
	int howManyTests;
};

