/* ********************    Trabalho 4 - CSI - A Missao!    ***********************
  Programa para modificar imagens de diferentes formas e selecionadas pelo usuario
  sendo essas: Log, Contrast Stretching e Flood fill
	Lucas Noriyuki Yoshida - 10262586
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/*struct que serve para auxiliar na alocacao dos dados referentes a imagem selecionada pelo usuario
O typedef serve para ajudar na hora de declarar a struct na main
*/
typedef struct imagem {

   char nomeArq[30]; //armazena o nome do arquivo
   char tipo[3]; //armazena o tipo ('P2' ou 'P5')
   char comen[100]; //armazena o comentario
   int XDIM; //armazena a dimensao das colunas
   int YDIM; //armazena a dimensao das linhas
   int MaxVal; //armazena o valor maximo de cor que a imagem pode ter
   FILE * arq; //serve para abrir/ler/fechar o arquivo
   unsigned char max; //pixel de maior valor na imagem
   unsigned char min; //pixel de menor valor na imagem
   unsigned char ** matriz; //armazena a imagem passada em uma matriz

}Imagem;


/*Funcao que lê a imagem passada pelo usuario e aloca esta em forma de matriz na heap
Parametro: Imagem * foto  == ponteiro referente a struct 'imagem'
*/
void leFoto(Imagem *foto) {
   //pega o nome do arquivo
   scanf("%s", (*foto).nomeArq);

   //abre o arquivo
   (*foto).arq = fopen((*foto).nomeArq, "rb");

   //suponha que leia 'P2' ou 'P5'
   fgets((*foto).tipo, 3, (*foto).arq);
   fgetc((*foto).arq);

   //suponha que leia o comentario
   fgets((*foto).comen, 100, (*foto).arq);
   (*foto).comen[strlen((*foto).comen)-1] = '\0';

   //leia dois inteiros a partir do arquivo
   fscanf((*foto).arq, "%d %d", &(*foto).XDIM, &(*foto).YDIM);

   //total de niveis de cinza MaxVal
   fscanf((*foto).arq, "%d", &(*foto).MaxVal);

}

/*Funcao que aloca a imagem em forma de matriz na heap
Parametros: Imagem * foto == ponteiro referente a struct 'imagem'
*/
void alocaMatriz (Imagem * foto){

   // guardar o endereco da matriz

   // aloca as linhas (ponteiros para os vetores)
   (*foto).matriz = (unsigned char**) malloc(sizeof(unsigned char*) * ((*foto).YDIM));

   // nesse ponto eu tenho um vetor com 'XDIM' ponteiros
   for (int i = 0; i < (*foto).YDIM; i++) {
      // aloca cada coluna (vetor de char)
      (*foto).matriz[i] = (unsigned char *) malloc((*foto).XDIM);
   }

   //declarando valores para auxiliar na ajuda dos valores dos pixels de maior e menor possiveis
   (*foto).max = 0;
   (*foto).min = 255;

   // para cada coluna (vetor de char) alocado
   for (int i = 0; i < (*foto).YDIM; i++) {
      for (int j = 0; j < (*foto).XDIM; j++) {
         unsigned char pixel; //variavel para ajudar na alocacao dos pixels da imagem
         //le do arquivo cada pixel da imagem na forma ASCII
         if ((*foto).tipo[1] == '2'){
            fscanf((*foto).arq, "%hhu", &pixel);
         }
         //le do arquivo cada pixel da imagem na forma BINARIA
         else if ((*foto).tipo[1] == '5'){
            if (i == 0 && j == 0){
               fgetc((*foto).arq);
            }
            fread(&pixel, sizeof(pixel), 1, (*foto).arq);
         }
         (*foto).matriz[i][j] = pixel;
         //parte de verificacao qual eh o maior e menor valor de pixel na imagem
	 if ((*foto).matriz[i][j] > (*foto).max){
            (*foto).max = (*foto).matriz[i][j];
         }
         if ((*foto).matriz[i][j] < (*foto).min){
            (*foto).min = (*foto).matriz[i][j];
         }
      }
   }

}

/*Funcao que serve para fazer a operacao de Log quando selecionada pelo usuario
Parametros: Imagem * foto == ponteiro referente a struct 'imagem'
*/
void opeLog (Imagem *foto){

   float c; //constante que ajuda no calculo do Log

   c = 255/(float)log(1 + (*foto).max);

   for (int i = 0; i < (*foto).YDIM; i++){
      for(int j = 0; j < (*foto).XDIM; j++){
         (*foto).matriz[i][j] = (unsigned char)(c * (float)log(1+(*foto).matriz[i][j]));
      }
   }

}

/*Funcao que serve para fazer a operacao de Contrast Stretching quando selecionada pelo usuario
Parametros: Imagem * foto == ponteiro referente a struct 'imagem'
*/
void contStret(Imagem *foto){

   for (int i = 0; i < (*foto).YDIM; i++){
      for(int j = 0; j < (*foto).XDIM; j++){
         (*foto).matriz[i][j] = (unsigned char)(255 * (((*foto).matriz[i][j] - (*foto).min)/(float)((*foto).max - (*foto).min)));
      }
   }

}

/*Funcao que serve para fazer a operacao de Floof Fill de forma recursiva quando selecionada pelo usuario
Parametros: Imagem * foto == ponteiro referente a struct 'imagem'
            i == refere as linhas da matriz
            j == refere as colunas da matriz
*/
void floodFill (Imagem * foto, int i, int j){

   if((*foto).matriz[i][j] == 0){
      (*foto).matriz[i][j] = 100;
      floodFill(foto, i+1, j);
      floodFill(foto, i, j+1);
      floodFill(foto, i-1, j);
      floodFill(foto, i, j-1);
   }

}

/*Funcao que serve especificamente para mostrar a saida que se espera da imagem
Parametros: Imagem * foto == ponteiro referente a struct 'imagem'
*/
void saida (Imagem * foto){

   //imprime tipo('P2'), comentario, dimensoes e valor maximo que pode ser encontrado
   printf("P2\n# CREATOR: Image Generator SCC-221 - ICC I\n%i %i\n%i\n",(*foto).XDIM, (*foto).YDIM, (*foto).MaxVal);

   //imprime a nova imagem formatada
   for (int i = 0; i < (*foto).YDIM; i++){
      for (int j = 0; j < (*foto).XDIM; j++){
         printf("%hhu\n",(*foto).matriz[i][j]);
      }
   }

}

/*Funcao que serve exclusivamente para liberar a heap alocada para trabalhar com a imagem em forma de matriz
Parametros: Imagem * foto == ponteiro referente a struct 'imagem'
*/
void liberaHeap (Imagem * foto){

   for(int i = 0; i < (*foto).YDIM; i++){
      free((*foto).matriz[i]);
   }

   free((*foto).matriz);
   (*foto).matriz = NULL;

}

int main() {

   char operacao; //serve para ver a operação selecionada pelo usuario
   Imagem foto; //variavel que representa a struct 'imagem'

   scanf("%c", &operacao); //usuario seleciona a operacao

   leFoto(&foto);

   alocaMatriz(&foto);

   //caso a operacao == 1 ela seleciona a operacao de Log
   if (operacao == '1'){
      opeLog(&foto);
      saida(&foto);
   }

   //caso a operacao == 2 ela seleciona a operacao de Contrast Stretching
   else if (operacao == '2'){
      contStret(&foto);
      saida(&foto);
   }

   //caso a operacao == 3 ela seleciona a operacao de Flood Fill
   else if(operacao == '3'){
      floodFill(&foto, foto.XDIM/2, foto.YDIM/2);
      saida(&foto);
   }

   liberaHeap(&foto);

   return 0;

}
