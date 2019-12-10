#include "Parser.h"

using namespace std;

Parser::Parser(string filename) {
	fin.open(filename);

	if (fin.fail()) {
		cout << filename << " not found" << endl;
	}

	commandTable['@'] = 'A';
	commandTable['A'] = 'C';
	commandTable['D'] = 'C';
	commandTable['M'] = 'C';
	commandTable['0'] = 'C';
	commandTable['1'] = 'C';
	commandTable['-'] = 'C';
	commandTable['!'] = 'C';
	commandTable['('] = 'L';
}

bool Parser::hasMoreCommands() {
	return !fin.eof();
}

void Parser::advance(unsigned long& lineNr) {
	string currentLine;
	unsigned long commentPos;
	bool commandFound = false;

	while (!commandFound && getline(fin, currentLine)) {
		lineNr++;

		currentLine.erase(remove_if(currentLine.begin(), currentLine.end(), ::isspace), currentLine.end());

		commentPos = currentLine.find("/");
		if (commentPos != string::npos) {
			currentLine.erase(commentPos, currentLine.length() - commentPos);
		}
		commandFound = !currentLine.empty();
	}
	currentItem = currentLine;
}

char Parser::commandType(unsigned long& lineNr) {
	if (commandTable.find(currentItem[0]) != commandTable.end()) {
		return commandTable[currentItem[0]];
	}
}

string Parser::symbol() {
	unsigned long openBracketPos = currentItem.find('(');
	unsigned long closeBracketPos = currentItem.find(')'); 

	if (currentItem[0] == '@') {
		return currentItem.substr(1, currentItem.length() - 1);
	}
	else if (openBracketPos != string::npos && closeBracketPos != string::npos) {
		return currentItem.substr(openBracketPos + 1, closeBracketPos - 1);
	}

	return "";
}

string Parser::destM() {
	unsigned long equalsPos = currentItem.find('=');

	if (equalsPos != string::npos) {
		return currentItem.substr(0, equalsPos);
	}
	
	return "";
}

string Parser::compM() {
	unsigned long equalsPos = currentItem.find('=');
	unsigned long semiPos = currentItem.find(';');

	if (equalsPos != string::npos) {
		if (semiPos != string::npos) {
			return currentItem.substr(equalsPos + 1, semiPos - equalsPos - 1);
		}
		return currentItem.substr(equalsPos + 1, currentItem.length() - equalsPos - 1);
	}
	else if (semiPos != string::npos) {
		return currentItem.substr(0, semiPos);
	}
	return "";
}

string Parser::jumpM() {
	unsigned long semiPos = currentItem.find(';');

	if (semiPos != string::npos) {
		return currentItem.substr(semiPos + 1, currentItem.length() - semiPos - 1);
	}

	return "";
}