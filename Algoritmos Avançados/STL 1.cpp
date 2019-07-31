/*
***************************************************

	USP - ICMC
	ALG - SCC0210 - 2018
	
	STL1 - Vector

	Março - 2018

	Lucas Noriyuki Yoshida - 10262586

****************************************************
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int main (){

	vector <int> vetor;
	int i;
	int* inteiros;

	inteiros = (int*)calloc(10, sizeof(int));

	for(i = 0; i < 8; i++){
		scanf("%d", &inteiros[i]);
	}

	for(i = 0; i < 8; i++){
    	vetor.push_back(inteiros[i]);
  	}

    std::sort (vetor.begin(), vetor.end());

    for(i = 0; i < 8; i++){
      cout << vetor[i] << endl;
  	}

  	cout << "\n";

  	for(i = 7; i >= 0; i--){
      cout << vetor[i] << endl;
  	}

   	free(inteiros);

	return 0;

}