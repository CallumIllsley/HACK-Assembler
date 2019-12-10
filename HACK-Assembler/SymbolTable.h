#pragma once
#include <map>
#include <iostream>

using namespace std;

class SymbolTable
{
public:
	SymbolTable();
	void addToTable(string name, int value);
	bool tableContains(string name);
	int getAddress(string name);
private:
	map<string, int> symbolAddressTable;
};

