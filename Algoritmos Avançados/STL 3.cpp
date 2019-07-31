/*
***************************************************

  USP - ICMC
  ALG - SCC0210 - 2018
  
  STL3 - Matrioshkas

  Março - 2018

  Lucas Noriyuki Yoshida - 10262586

****************************************************
*/

#include <iostream>  
#include <stack> 
#include <vector>
#include <sstream>  
using namespace std;  

struct node{

    int v,soma;  
    node(int a,int b):v(a),soma(b){}  

};  

bool check(vector<int>& v){  
    stack<node>pilha;

    int j = v.size();
    
    for(int i = 0; i < j; i++){  
        if(v[i] < 0)  
            pilha.push(node(v[i], v[i]));  
        else{  
            if(!pilha.empty() && pilha.top().v + v[i] == 0){  
                pilha.pop();  
                if(!pilha.empty()){  
                    node topo = pilha.top(); pilha.pop();  
                    topo.soma += v[i];  
                    if(topo.soma >= 0)return false;  
                        pilha.push(topo);  
                }  
            }  
            else return false;  
        }  
    }  

    return pilha.empty();

}  

int main(){  
    string linha;  
    while(getline(cin, linha)){  
        vector<int>v;  
        int num;  
        istringstream in(linha);  
        while(in >> num)v.push_back(num);  
        if(check(v))  
            cout << ":-) Matrioshka!" << endl;  
        else cout << ":-( Try again." << endl;  
    }  
    return 0;  
}  