#include "SymbolTable.h"
#include <iostream>
#include <map>

using namespace std;

SymbolTable::SymbolTable() {
	symbolAddressTable["R0"] = 0;
	symbolAddressTable["R1"] = 1;
	symbolAddressTable["R2"] = 2;
	symbolAddressTable["R3"] = 3;
	symbolAddressTable["R4"] = 4;
	symbolAddressTable["R5"] = 5;
	symbolAddressTable["R6"] = 6;
	symbolAddressTable["R7"] = 7;
	symbolAddressTable["R8"] = 8;
	symbolAddressTable["R9"] = 9;
	symbolAddressTable["R10"] = 10;
	symbolAddressTable["R11"] = 11;
	symbolAddressTable["R12"] = 12;
	symbolAddressTable["R13"] = 13;
	symbolAddressTable["R14"] = 14;
	symbolAddressTable["R15"] = 15;
	symbolAddressTable["SCREEN"] = 16384;
	symbolAddressTable["KBD"] = 24576;
	symbolAddressTable["SP"] = 0;
	symbolAddressTable["LCL"] = 1;
	symbolAddressTable["ARG"] = 2;
	symbolAddressTable["THIS"] = 3;
	symbolAddressTable["THAT"] = 4;
	symbolAddressTable["LOOP"] = 4;
	symbolAddressTable["WRITE"] = 18;
	symbolAddressTable["END"] = 22;
}

void SymbolTable::addToTable(string name, int value) {
	if (symbolAddressTable.find(name) == symbolAddressTable.end()) {
		symbolAddressTable[name] = value;
	}
}

bool SymbolTable::tableContains(string name) {
	return (symbolAddressTable.find(name) != symbolAddressTable.end());
}

int SymbolTable::getAddress(string name) {
	if (symbolAddressTable.find(name) != symbolAddressTable.end()) return symbolAddressTable[name];
	return 0;
}