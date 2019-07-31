/*
***************************************************

	USP - ICMC
	ALG - SCC0210 - 2018
	
	STL2 - QWERTYU

	Março - 2018

	Lucas Noriyuki Yoshida - 10262586

****************************************************
*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <map>
using namespace std;

int main (){

	map <char,char> keymap;

	keymap['O'] = 'I';
	keymap['S'] = 'A';
	keymap[','] = 'M';
	keymap['G'] = 'F';
	keymap['M'] = 'N';
	keymap['R'] = 'E';
	keymap['Y'] = 'T';
	keymap['P'] = 'O';
	keymap['F'] = 'D';
	keymap['U'] = 'Y';
	keymap['/'] = '.';
	keymap['J'] = 'H';
	keymap['E'] = 'W';
	keymap['T'] = 'R';
	keymap['I'] = 'U';
	keymap[' '] = ' ';
	
	map <char, char>::iterator itr;

	char** frase;

	frase = (char**)calloc(2, sizeof(char*));
	for(int cont = 0; cont < 2; cont++){
		frase[cont] = (char*)calloc(20, sizeof(char));
	}

	for(int cont = 0; cont < 2; cont++){
		fgets(frase[cont], 20, stdin);
		for(int cont1 = 0; cont1 < 20; cont1++){
			if(frase[cont][cont1] == '\n' || frase[cont][cont1] == '\r')
				break;
			itr = keymap.find(frase[cont][cont1]);
			cout << itr->second;
		}
		cout << "\n";
	}

	return 0;

}