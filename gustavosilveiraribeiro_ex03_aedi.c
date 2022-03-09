//GUSTAVO SILVEIRA RIBEIRO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PILHA 50

typedef struct {
  char vet[MAX_PILHA];
  int topo;
} Tpilha;

Tpilha* nova();
int push(Tpilha *p, char x);
char pop(Tpilha *p);
void listar(Tpilha *p);
Tpilha *remover (Tpilha* p);
Tpilha *inverter(Tpilha *pout);
int num_spa_ope(Tpilha *p);
Tpilha *infixa_posfixa(Tpilha *pout, Tpilha *pin);
Tpilha *calcular(Tpilha *p);

int main(){
  printf("%c", 1);
  char x;
  Tpilha *infixa = nova(), *posfixa = nova();
  scanf("%c", &x);
  do{
      push(infixa, x);
      scanf("%c", &x);
  }while(x != '\n');
  
  infixa = inverter(infixa);

  posfixa = infixa_posfixa(infixa, posfixa);

  posfixa = inverter(posfixa);
  listar(posfixa);

  printf("\n");

  //posfixa = calcular(posfixa);
  
  remover(posfixa);
  remover(infixa);
  return 0;
}

Tpilha *nova(){
  Tpilha *np = (Tpilha *) malloc(sizeof (Tpilha));
  np->topo = -1;
  return np;
}

int push(Tpilha* p, char x){
    if(p->topo >= MAX_PILHA-1){
        return -1;
    }
    (p->topo)++;
    p->vet[p->topo] = x;
    return 0;
}

char pop(Tpilha *p){
  char x;
  if (p->topo < 0){
      return -1;
  }
  x = p->vet[p->topo];
  p->topo--;
  return x;
}

void listar(Tpilha *p){
  for (int i = 0; i <= p->topo; i++) {
      printf ("%c", p->vet[p->topo-i]);
  }
}

Tpilha *remover (Tpilha* p){
  free (p);
  return (NULL);
}

Tpilha *inverter (Tpilha *p){
  Tpilha *paux = nova();
  do{
    if(num_spa_ope(p) >=1 && num_spa_ope(p) <= 5){
      (paux->topo)++;
      paux->vet[paux->topo] = p->vet[p->topo];
    }
    (p->topo)--;
  }while(p->topo >= 0);
  remover(p);
  return paux;
}

/*Tpilha *calcular(Tpilha *p){
  char aux1[p->topo], aux2[p->topo];
  int i=0, int1, int2, int3;
  Tpilha *paux = nova();
  do{
    if(num_spa_ope(p) > 3 ){
      (paux->topo)++;
      paux->vet[paux->topo] = p->vet[p->topo];
    }
    if(num_spa_ope(p) <= 3 && num_spa_ope(p) >= 1 ){
      pop(paux);
      do{
        aux2[i] = pop(paux);
        i++;
      }while(aux2[i] == ' ');
      int2 =  strtol(aux2, NULL, 10);
      i = 0;
      do{
        aux1[i] = pop(paux);
        i++;
      }while(aux1[i] == ' ');
      int1 =  strtol(aux1, NULL, 10);

      int3 = int1 + int2;
      

    }
    p->topo--;
  }while(p->topo >= 0);
  remover(p);
  return paux;
}*/

Tpilha *infixa_posfixa(Tpilha *pout, Tpilha *pin){
  int ok = 0;
  Tpilha *paux = nova();
  do{
    switch (num_spa_ope(pout)) {

      case 4 : 
      push(pin,pop(pout));
      break;

      default :
        do{
          if(paux->topo < 0 || num_spa_ope(pout) > num_spa_ope(paux)){
            push(pin,' ');
            push(paux,pop(pout));
            ok = 1;
          }
          else{
            push(pin,' ');
            push(pin,pop(paux));
          }
        }while(ok != 1);
        ok = 0;
        break;
    }
  }while(pout->topo >= 0);

  while(paux->topo >= 0){
    push(pin,' ');
    push(pin,pop(paux));
  }

  remover(paux);
  return pin;
}

int num_spa_ope(Tpilha *p){
  switch (p->vet[p->topo]){
    case '0': return 4;
    case '1': return 4;
    case '2': return 4;
    case '3': return 4;
    case '4': return 4;
    case '5': return 4;
    case '6': return 4;
    case '7': return 4;
    case '8': return 4;
    case '9': return 4;
    case ' ': return 5;
    case '+': return 1;
    case '-': return 1;
    case '*': return 2;
    case '/': return 2;
    case '^': return 3;
  }
  return 0;
}