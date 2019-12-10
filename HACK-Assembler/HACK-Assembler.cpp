#include <iostream>
#include <fstream>
#include "SymbolTable.h";
#include "Parser.h";
#include "Translator.h";
#include <bitset>

using namespace std;

int main()
{
	string filepath;
	cout << "Enter filename to assemble." << endl;
	cin >> filepath;
	ofstream fout;
	string outFilepath = filepath.substr(0, filepath.length() - 4) + ".hack";
	fout.open(outFilepath);

	SymbolTable symbolTable;
	Parser parser(filepath);

	unsigned long lineNumberP = 0;
	unsigned long lineNumberR = 0;
	int addressNum = 0;

	while (true) {
		parser.advance(lineNumberP);

		if (!parser.hasMoreCommands()) break;

		if (parser.commandType(lineNumberP) == 'A' || parser.commandType(lineNumberP) == 'C') {
			lineNumberR++;
		}

		else if (parser.commandType(lineNumberP) == 'L') {
			symbolTable.addToTable(parser.symbol(), lineNumberR);
		}
	}

	Parser secondParse(filepath);
	Translator translator;

	lineNumberP = 0;
	addressNum = 16;

	while (true) {
		if (!secondParse.hasMoreCommands()) break;

		secondParse.advance(lineNumberP);

		switch(secondParse.commandType(lineNumberP)) {
		case 'A':
			fout << 0;

			if (secondParse.symbol().find_first_not_of("0123456789") == string::npos) {
				fout << bitset<15>(stoi(secondParse.symbol())).to_string();
			}
			else {
				if (!symbolTable.tableContains(secondParse.symbol())) {
					symbolTable.addToTable(secondParse.symbol(), addressNum++);
				}
				fout << bitset<15>(symbolTable.getAddress(secondParse.symbol())).to_string();
			}
			fout << endl;
			break;
		case 'C':
			fout << 111;
			fout << translator.comp(secondParse.compM(), lineNumberP);
			fout << translator.dest(secondParse.destM(), lineNumberP);
			fout << translator.jump(secondParse.jumpM(), lineNumberP);
			fout << endl;
			break;
		} 
	}

	fout.close();
	return 0;
}
