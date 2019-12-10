#pragma once
#include <iostream>
#include <map>

using namespace std;

class Translator
{
public:
	Translator();
	
	string dest(string destM, unsigned long& lineNr);
	string comp(string compM, unsigned long& lineNr);
	string jump(string jumpM, unsigned long& lineNr);

private: 
	map<string, string> destTable;
	map<string, string> compTable;
	map<string, string> jumpTable;
};

