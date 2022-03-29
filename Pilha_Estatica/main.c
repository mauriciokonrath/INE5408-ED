#include <stdio.h>
#include <stdlib.h>
#define MAXTAM 100

typedef struct {
  int Item[MAXTAM];
  int Topo;

} TPilha;

void TPilha_Inicia(TPilha *p){
  p->Topo = -1;
}

int TPila_Vazia(TPilha *p){
  if (p->Topo == -1){
    return 1;
  } else{
    return 0;
  }
}

int TPila_Cheia(TPilha *p){
  if (p->Topo == MAXTAM-1){
    return 1;
  } else {
    return 0;
  }
}

void TPilha_Insere (TPilha *p, int x) {
  if (TPila_Cheia(p) == 1){
    printf("\nERRO: Pilha cheia");
  } else {
      p->Topo++; //Inserindo numa posição a mais (na próxima)
      p->Item[p->Topo] = x; //Inserir o valor(x) dentro de uma posição, nesse caso no topo
  }
}

int TPilha_Retira(TPilha *p){ // int pois vai depender do tipo de variavel que eu vou remover
  int aux;
  if (TPila_Vazia(p) == 1){
    printf("\nERRO: Pilha vazia");
  } else {
    aux = p->Item[p->Topo];
    p->Topo--;
    return aux;
  }
}

int main(){
  TPilha *p = (TPilha*)malloc(sizeof(TPilha));
  TPilha_Inicia(p);

  TPilha_Insere(p, 1); //insere o valor 1 na pilha
  TPilha_Insere(p, 2);
  TPilha_Insere(p, 3);

  int aux;

  aux = TPilha_Retira(p); //Remove o 3

  printf("\nSAIU: %d", aux);


  return 0;
}
