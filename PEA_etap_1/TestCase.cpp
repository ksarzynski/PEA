#include "TestCase.h"

TestCase::TestCase() {
	this->isFromFile = false;
	this->fileName = "";
	this->howManyTests = 1;
}

TestCase::TestCase(bool _isFromFile, std::string _fileName, int _size, int _algorithm, int _howManyTests) {
	this->isFromFile = _isFromFile;
	this->fileName = _fileName;
	this->size = _size;
	this->algorithm = _algorithm;
	this->howManyTests = _howManyTests;
}

bool TestCase::getIsFromFile() {
	return this->isFromFile;
}

std::string TestCase::getFileName() {
	return this->fileName;
}

int TestCase::getSize() {
	return this->size;
}

int TestCase::getAlgorithm() {
	return this->algorithm;
}

int TestCase::getHowManyTests() {
	return this->howManyTests;
}

void TestCase::setIsFromFile(bool _isFromFile) {
	this->isFromFile = _isFromFile;
}

void TestCase::setFileName(std::string _fileName) {
	this->fileName = _fileName;
}

void TestCase::setSize(int _size) {
	this->size = _size;
}

void TestCase::setAlgorithm(int _algorithm) {
	this->algorithm = _algorithm;
}

void TestCase::setHowManyTests(int _howManyTests) {
	this->howManyTests = _howManyTests;
}
