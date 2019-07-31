#include <stdio.h>

#define chao 0            //indica o lugar trafegavel
#define parede 1          //indica o lugar nao trafegavel

int main () {

  int caminho[200] = {0};        //vetor que guarda o caminho para saida do labirinto
  int loop;
  int pos_camin;                //ajuda a guardar o caminho do labirinto indicando o proximo valor de caminho
  int ctrl;                     //variavel de controle e por fim ajuda a imprimir o caminho percorrido
  int lin = 1;                  //auxilia com o caminho na matriz pelas linhas
  int col = 1;                  //auxilia com o caminho na matriz pelas colunas
    int inicio;
    int controle = 0;
    int mat[100][100];
    int n, m;
    char entrada, saida;
	int x, y;
	int e1, e2;
    int s1, s2;

	scanf("%c %c %d %d", &entrada, &saida, &x, &y);

 for (n = 0; n<x; n++){
    for (m = 0; m<y; m++){
      scanf("%d", &mat[n][m]);
    }
  }

   if(entrada == 'O'){
      e2 = 0;
      for(int cont = 0;cont < x; cont++){
         if(mat[cont][0] == 0){
            e1 = cont;
         }
      }
   }
   if(entrada == 'L'){
      e2 = y - 1;
      for(int cont = 0; cont < x; cont++){
         if(mat[cont][y - 1] == 0){
            e1 = cont;
         }
      }
   }
   if(entrada == 'N'){
      e1 = 0;
      for(int cont = 0; cont < y; cont++){
         if(mat[0][cont] == 0){
            e2 = cont;
         }
      }
   }
   if(entrada == 'S'){
      e1 = x - 1;
      for(int cont = 0; cont < lin; cont++){
         if(mat[x - 1][cont]){
            e2 = cont;
         }
      }
   }
   if(saida == 'O'){
      s2 = 0;
      for(int cont = 0; cont < x; cont++){
         if(mat[cont][0] == 0){
            s1 = cont;
         }
      }
   }
   if(saida == 'L'){
      s2 = y - 1;
      for(int cont = 0; cont < x; cont++){
         if(mat[cont][y - 1] == 0){
            s1 = cont;
         }
      }
   }
   if(saida == 'N'){
      s1 = 0;
      for(int cont = 0; cont < y; cont++){
         if(mat[0][cont] == 0){
            s2 = cont;
         }
      }
   }
   if(saida == 'S'){
      s1 = x - 1;
      for(int cont = 0; cont < x; cont++){
         if(mat[x - 1][cont] == 0){
            s2 = cont;
         }
      }
   }

  inicio = (e1*(x-1) + e2);
  //Informar a entrada do labirinto
  caminho [0] = inicio; 

  /*Descobrir o menor caminho a ser percorrido no labirinto
  ctrl -> se (== 1) inicia o labirinto; se (== 0) segue como 'true' para seguir adiante no labirinto; se (== 2) reinicializa o labirinto e modifica este
  Se (lin == 0 || lin == 6 || col == 0 || col == 6) representa os cantos do labirinto, portanto a saida esta alocada em algum desses lugares
  */
  while (lin!=s1 && col!=s2) {
    //Inicializa lin e col com a entrada do labirinto
    lin = e1;
    col = e2;
    ctrl = 1;
    pos_camin = 1;

    //Serve para percorrer o labirinto e guardar o caminho
    while(ctrl<2){
      if(ctrl){
        ctrl = 0;

        /*As condicoes dos caminhos a serem seguidos estao em ordem de:
        se o proximo caminho segue o chao
        se o proximo caminho e' igual a um anterior
        se o caminho chega ao fim
        */
        //Segue para cima
        while(mat[lin-1][col] == chao && ((lin-1)*(x-1))+col!=caminho[pos_camin-2] && lin!=0){
          caminho[pos_camin] = ((lin-1)*(x-1))+col;
          lin--;
          pos_camin++;
          ctrl = 1;
        }

        //Segue para direita
        while(mat[lin][col+1] == chao && (lin*(x-1))+col+1!=caminho[pos_camin-2] && col!=y-1){
          caminho[pos_camin] = (lin*(x-1))+col+1;
          col++;
          pos_camin++;
          ctrl = 1;
        }

        //Segue para esquerda
        while(mat[lin][col-1] == chao && (lin*(x-1))+col-1!=caminho[pos_camin-2] && col!=0){
          caminho[pos_camin] = (lin*(x-1))+col-1;
          col--;
          pos_camin++;
          ctrl = 1;
        }

        //Segue para baixo
        while(mat[lin+1][col] == chao && ((lin+1)*(x-1))+col!=caminho[pos_camin-2] && lin!=x-1){
          caminho[pos_camin] = ((lin+1)*(x-1))+col;
          lin++;
          pos_camin++;
          ctrl = 1;
        }
      }

      //Reinicializa o labirinto e substitui chao por parede no lugar sem saida
      else {
        mat[lin][col] = parede;
        ctrl = 2;
      }
    }
  loop++;
     if(loop >= 1000){
       controle = 1;
       break;
     }
  }
   
   if(controle == 0){
      printf("Existe saida %c - %c.", entrada, saida);
   }
   else {
      printf("Nao existe saida %c - %c.", entrada, saida);
   }

  return 0;

}
