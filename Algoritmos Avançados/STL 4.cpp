/*
***************************************************

  USP - ICMC
  ALG - SCC0210 - 2018
  
  STL4 - Qual estrutura de dados

  Março - 2018

  Lucas Noriyuki Yoshida - 10262586

****************************************************
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <queue>
using namespace std;

int main() {
	int n, estrutura, a;

	while (scanf("%d", &n) != EOF) {
		
		queue<int> queue;
		stack<int> stack;
		priority_queue<int> priqueue;
		
		bool pilha = true, fila = true, filapri = true;

		for(int cont = 0; cont < n; cont++){
			scanf("%d %d", &estrutura, &a);

			switch(estrutura){

			case 1:
				if (pilha)
					stack.push(a);
				if (fila)
					queue.push(a);
				if (filapri)
					priqueue.push(a);
				break;

			case 2:
				if (pilha){
					if (stack.empty() || stack.top() != a)
						pilha = false;
					else
						stack.pop();
				}
				if (fila){
					if (queue.empty() || queue.front() != a)
						fila = false;
					else
						queue.pop();
				}
				if (filapri){
					if (priqueue.empty() || priqueue.top() != a)
						filapri = false;
					else
						priqueue.pop();
				}
				break;
			}
		}

		if (pilha == true && fila == false && filapri == false)
			cout << "stack" << endl;
		else if (pilha == false && fila == true && filapri == false)
			cout << "queue" << endl;
		else if (pilha == false && fila == false && filapri == true)
			cout << "priority queue" << endl;
		else if (pilha == false && fila == false && filapri == false)
			cout << "impossible" << endl;
		else
			cout << "not sure" << endl;
	}
}