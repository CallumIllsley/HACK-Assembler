#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class Parser
{
public:
	Parser(string filename);
	bool hasMoreCommands();
	void advance(unsigned long& lineNr);
	char commandType(unsigned long& lineNr);

	string symbol();
	string destM();
	string compM();
	string jumpM();
private:
	string currentItem;
	map<char, char> commandTable;
	ifstream fin;
};


