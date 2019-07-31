#include <stdio.h>

#define chao 0            //indica o lugar trafegavel
#define parede 1          //indica o lugar nao trafegavel

/*Funcao que serve para escrever a matriz/caminhos do labirinto
Parametro: labirinto/matriz travada 7x7
Retorno: void
*/
void alocarmatriz (int mat[7][7]){

  int n;                  //variavel representando o numero de linhas
  int m;                  //veriavel representando o numero de colunas

  //Alocacao da matriz/caminhos do labirinto
  for (n = 0; n<7; n++){
    for (m = 0; m<7; m++){
      scanf("%d", &mat[n][m]);
    }
  }
}

int main () {

  int labirinto[7][7];           //tamanho da matriz/labirinto
  int inicio;                   //variavel representando a entrada do labirinto
  int caminho[20] = {0};        //vetor que guarda o caminho para saida do labirinto
  int pos_camin;                //ajuda a guardar o caminho do labirinto indicando o proximo valor de caminho
  int ctrl;                     //variavel de controle e por fim ajuda a imprimir o caminho percorrido
  int lin = 1;                  //auxilia com o caminho na matriz pelas linhas
  int col = 1;                  //auxilia com o caminho na matriz pelas colunas

  //Informar a matriz/caminhos do labirinto
  alocarmatriz(labirinto);

  //Informar a entrada do labirinto
  scanf ("%d", &inicio);
  caminho [0] = inicio;

  /*Descobrir o menor caminho a ser percorrido no labirinto
  ctrl -> se (== 1) inicia o labirinto; se (== 0) segue como 'true' para seguir adiante no labirinto; se (== 2) reinicializa o labirinto e modifica este
  Se (lin == 0 || lin == 6 || col == 0 || col == 6) representa os cantos do labirinto, portanto a saida esta alocada em algum desses lugares
  */
  while (lin!=0 && col!=0 && lin!=6 && col!=6) {
    //Inicializa lin e col com a entrada do labirinto
    lin = inicio/7;
    col = inicio%7;
    ctrl = 1;
    pos_camin = 1;

    //Serve para percorrer o labirinto e guardar o caminho
    while(ctrl<2){
      if(ctrl){
        ctrl=0;

        /*As condicoes dos caminhos a serem seguidos estao em ordem de:
        se o proximo caminho segue o chao
        se o proximo caminho e' igual a um anterior
        se o caminho chega ao fim
        */
        //Segue para cima
        while(labirinto[lin-1][col] == chao && ((lin-1)*7)+col!=caminho[pos_camin-2] && lin!=0){
          caminho[pos_camin] = ((lin-1)*7)+col;
          lin--;
          pos_camin++;
          ctrl = 1;
        }

        //Segue para direita
        while(labirinto[lin][col+1] == chao && (lin*7)+col+1!=caminho[pos_camin-2] && col!=6){
          caminho[pos_camin] = (lin*7)+col+1;
          col++;
          pos_camin++;
          ctrl = 1;
        }

        //Segue para esquerda
        while(labirinto[lin][col-1] == chao && (lin*7)+col-1!=caminho[pos_camin-2] && col!=0){
          caminho[pos_camin] = (lin*7)+col-1;
          col--;
          pos_camin++;
          ctrl = 1;
        }

        //Segue para baixo
        while(labirinto[lin+1][col] == chao && ((lin+1)*7)+col!=caminho[pos_camin-2] && lin!=6){
          caminho[pos_camin] = ((lin+1)*7)+col;
          lin++;
          pos_camin++;
          ctrl = 1;
        }
      }

      //Reinicializa o labirinto e substitui chao por parede no lugar sem saida
      else {
        labirinto [lin][col] = parede;
        ctrl = 2;
      }
    }
  }

  //Imprime o menor caminho percorrido
  for (ctrl = 0; ctrl<pos_camin ; ctrl++){
    printf("%d ", caminho[ctrl]);
  }

  return 0;

}
