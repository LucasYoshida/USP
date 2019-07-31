/*
***************************************************

  USP - ICMC
  ALG - SCC0210 - 2018
  
  STL5 - Football(aka Soccer)

  Março - 2018

  Lucas Noriyuki Yoshida - 10262586

****************************************************
*/

#include <stdio.h>
#include <iostream>
#include <map>
#include <string.h>
#include <algorithm>
using namespace std;

struct team {
    char name[105];
    int pt, win, lose, tie, score, invscore;
    void init() {
        pt = win = lose = tie = 0;
        score = invscore = 0;
    }
    void record(int a, int b) {
        if(a > b)   
        	win++, pt += 3;
        else if(a < b)  
        	lose++;
        else    
        	tie++, pt++;
        score += a, invscore += b;
    }
};

bool cmp(team a, team b) {
    if(a.pt != b.pt)    
    	return a.pt > b.pt;
    if(a.win != b.win)  
    	return a.win > b.win;
    if(a.score-a.invscore != b.score-b.invscore)
        return a.score-a.invscore > b.score-b.invscore;
    if(a.score != b.score)
        return a.score > b.score;
    if(a.win+a.lose+a.tie != b.win+b.lose+b.tie)
        return a.win+a.lose+a.tie < b.win+b.lose+b.tie;
    return strcasecmp(a.name, b.name) < 0;
}

int main() {

	int a;

	scanf("%d", &a);
	getchar();

    int n, m = 0, i;
    char* name;
    char* buff;

    int num = 0;

    name = (char*)calloc(105, sizeof(char));
    buff = (char*)calloc(105, sizeof(char));

    while(fgets(name, 105, stdin)){

        scanf("%d", &n);
        getchar();

        map<string, int> R;

        printf("%s", name);
        
        team A[50];
        
        for(i = 0; i < n; i++) {
            fgets(A[i].name, 105, stdin);
            for(int cont = 0; cont < 105; cont++){
            	if(A[i].name[cont] == '\n')
            		A[i].name[cont] = '\0';
            }
            A[i].init();
            R[A[i].name] = i;
        }
        
        scanf("%d", &m);
        getchar();
        
        while(m--) {
            fgets(buff, 105, stdin);
            char name1[50], name2[50];
            int num1, num2;
            
            sscanf(buff, "%[^#]#%d@%d#%[^\n]", name1, &num1, &num2, name2);
            
            A[R[name1]].record(num1, num2);
            A[R[name2]].record(num2, num1);
        }
        
        sort(A, A+n, cmp);
        
        for(i = 0; i < n; i++)
            printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n",
                    i+1, A[i].name, A[i].pt, A[i].win+A[i].lose+A[i].tie,
                    A[i].win, A[i].tie, A[i].lose, A[i].score-A[i].invscore,
                    A[i].score, A[i].invscore);

        if(num == 0){
        	printf("\n");
        }
        num++;

    }

    free(name);
    free(buff);

    return 0;

}