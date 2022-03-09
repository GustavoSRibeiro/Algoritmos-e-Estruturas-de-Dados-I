//GUSTAVO SILVEIRA RIBEIRO 156560 NB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char marca[15];
    char modelo[25];
    int ano;
    char placa[6];
    int quilometragem;
    int portas;
    char ar_condicionado;
}registro_carros;

//funcao inserir usando alocacao dinamica, nao funciona corretamente no codeblocks
int inserir() {
    int achou = 0;
    registro_carros t, r, *pt = (registro_carros*) malloc(sizeof(registro_carros));
    if(pt == NULL) { //teste se conseguiu alocar espaco
        printf("\nNao conseguiu alocar memoria");
        return 1;
    }
    FILE *parq;
    parq = fopen("carros.txt","r+");
    if(parq == NULL) { //teste se abriu corretamente o arquivo
        printf("\nNao foi possivel abrir o arquivo");
        return 2;
    }
    printf("-----------------------------------------------\n" "Digite a marca: ");
    getc(stdin); scanf(" %s", pt->marca);
    printf("Digite o modelo: ");
    getc(stdin); scanf(" %s", pt->modelo);
    printf("Digite o ano de fabricacao: ");
    getc(stdin); scanf(" %d", &pt->ano);
    printf("Digite a placa: ");
    getc(stdin); scanf(" %s", pt->placa);
    printf("Digite a quilometragem: ");
    getc(stdin); scanf(" %d", &pt->quilometragem);
    printf("Digite a numero de portas: ");
    getc(stdin); scanf(" %d", &pt->portas);
    printf("Digite se possui ar condicionado: ");
    getc(stdin); scanf(" %c", &pt->ar_condicionado);

    //teste para verificar se ja ha outro registro com a mesma placa
    //caso sim, nao registra e avisa, caso contrario, registra normalmente
    while(fscanf(parq,"%s\n%s\n%d\n%s\n%d\n%d\n%c\n", r.marca, r.modelo, &r.ano, r.placa, &r.quilometragem, &r.portas, &r.ar_condicionado) != EOF) {
        if(strcmp(r.placa, pt->placa) == 0) {
            printf("Ja Existe Um Registro Com Essa Placa");
            achou = 1;
            fclose(parq);
            free(pt);
            getchar();
            return 0;
        }
    }
    if(achou == 0){
        fprintf(parq, "%s\n", pt->marca);
        fprintf(parq, "%s\n", pt->modelo);
        fprintf(parq, "%d\n", pt->ano);
        fprintf(parq, "%s\n", pt->placa);
        fprintf(parq, "%d\n", pt->quilometragem);
        fprintf(parq, "%d\n", pt->portas);
        fprintf(parq, "%c\n", pt->ar_condicionado);
    }
    fclose(parq);
    free(pt);
    return 0;
}


/*int inserir() {
    int achou = 0;
    registro_carros t, r;
    FILE *parq;
    parq = fopen("carros.txt","r+");
    if(parq == NULL) { //teste se abriu corretamente o arquivo
        printf("\nNao foi possivel abrir o arquivo");
        return 1;
    }
    printf("-----------------------------------------------\n" "Digite a marca: ");
    scanf("%s", t.marca);
    printf("Digite o modelo: ");
    scanf("%s", t.modelo);
    printf("Digite o ano de fabricacao: ");
    scanf("%d", &t.ano);
    printf("Digite a placa: ");
    scanf("%s", t.placa);
    printf("Digite a quilometragem: ");
    scanf("%d", &t.quilometragem);
    printf("Digite a numero de portas: ");
    scanf("%d", &t.portas);
    printf("Digite se possui ar condicionado: ");
    getc(stdin); scanf("%c", &t.ar_condicionado);

    //teste para verificar se ja ha outro registro com a mesma placa
    //caso sim, nao registra e avisa, caso contrario, registra normalmente
    while(fscanf(parq,"%s\n%s\n%d\n%s\n%d\n%d\n%c\n", r.marca, r.modelo, &r.ano, r.placa, &r.quilometragem, &r.portas, &r.ar_condicionado) != EOF) {
        if(strcmp(r.placa, t.placa) == 0) {
            printf("Ja Existe Um Registro Com Essa Placa");
            achou = 1;
            fclose(parq);
            getch();
            return 0;
        }
    }
    if(achou == 0){
        fprintf(parq, "%s\n", t.marca);
        fprintf(parq, "%s\n", t.modelo);
        fprintf(parq, "%d\n", t.ano);
        fprintf(parq, "%s\n", t.placa);
        fprintf(parq, "%d\n", t.quilometragem);
        fprintf(parq, "%d\n", t.portas);
        fprintf(parq, "%c\n", t.ar_condicionado);
    }
    fclose(parq);
    return 0;
}*/

int mostrar() {
    registro_carros t;
    int achou = 0;
    char digplaca[7];
    printf("-----------------------------------------------\n" "Digite a placa: ");
    scanf("%s",digplaca);

    FILE *parq;
    parq = fopen("carros.txt","a+");
    if(parq == NULL){ //teste se abriu corretamente o arquivo
        printf("\nNao foi possivel abrir o arquivo");
        return 2;
    }

    //busca em todo arquivo a placa digitada
    //caso encontre, mostra o registro e aguarda qualque tecla para continuar, caso contrario, avisa
    while(fscanf(parq,"%s\n%s\n%d\n%s\n%d\n%d\n%c\n", t.marca, t.modelo, &t.ano, t.placa, &t.quilometragem, &t.portas, &t.ar_condicionado) != EOF) {
        if(strcmp(t.placa,digplaca) == 0) {
            printf("-----------------------------------------------\n" "Marca: %s\nModelo: %s\nAno de Fabricacao: %d\nPlaca: %s\nQuilometragem: %d\nPortas: %d\nAr Condicionado: %c\n", t.marca, t.modelo, t.ano, t.placa, t.quilometragem, t.portas, t.ar_condicionado);
            achou = 1;
            break;
        }
    }
    if(achou == 0) {
      printf("-----------------------------------------------\n" "Nao foi possivel encontrar o registro do carro\n");
    }
    fclose(parq);
    getch();
    return 0;
}

//em "alterar" e "apagar" é utilizado um arquivo auxiliar, que recebe do original os registro anteriores
//ao procurado, quando encontra, os recebe alterado quando "alterar" ou nao recebe quando "apagar"
//em seguida recebe os seguintes registros até o fim do arquivo original. O original é apagado e o auxiliar
//recebe o nome do original
int alterar() {
    registro_carros t;
    int achou = 0, item;
    char digplaca[7];
    printf("-----------------------------------------------\n" "Digite a placa: ");
    scanf("%s",digplaca);

    FILE *parq, *pcop, *parq2;
    parq = fopen("carros.txt","a+");
    if(parq == NULL){//teste se abriu corretamente o arquivo
        printf("\nNao foi possivel abrir o arquivo");
        return 1;
    }
    pcop = fopen("copiacarros.txt","w+");
    if(pcop == NULL){//teste se abriu corretamente o arquivo
        printf("\nNao foi possivel abrir o arquivo");
        return 2;
    }

    //busca em todo arquivo original a placa digitada
    while(fscanf(parq,"%s\n%s\n%d\n%s\n%d\n%d\n%c\n", t.marca, t.modelo, &t.ano, t.placa, &t.quilometragem, &t.portas, &t.ar_condicionado) != EOF) {
        if(strcmp(t.placa,digplaca) == 0) {
            printf("-----------------------------------------------\n" "Marca: %s\nModelo: %s\nAno de Fabricacao: %d\nPlaca: %s\nQuilometragem: %d\nPortas: %d\nAr Condicionado: %c\n", t.marca, t.modelo, t.ano, t.placa, t.quilometragem, t.portas, t.ar_condicionado);
            achou = 1;
            break;
        }
        else {
            fprintf(pcop,"%s\n%s\n%d\n%s\n%d\n%d\n%c\n", t.marca, t.modelo, t.ano, t.placa, t.quilometragem, t.portas, t.ar_condicionado);
        }
    }
    //caso nao encontre, avisa
    if(achou == 0) {
      printf("-----------------------------------------------\n" "Nao foi possivel encontrar o registro do carro\n");
    remove("copiacarros.txt");
    fclose(parq);
    fclose(pcop);
    return 0;
    }
    //caso encontre, pergunta o que quer alterar, pede confirmacao, e pergunta se quer alterar mais dados
    else {
      char troca1[15], troca2[25], troca6, confirma, confirmafim, lixo;
      int troca3, troca4, troca5;
      do {
      printf("-----------------------------------------------\n"
              "Escolha o item que deseja alterar:"
              "\n1)Marca\n2)Modelo\n3)Ano de Fabricacao\n4)Quilometragem\n5)Portas\n6)Ar Condicionado\n"
              "-----------------------------------------------\n");
      scanf("%d", &item);
      printf("-----------------------------------------------\n");
      switch(item) {
        case 1:
            printf("Marca antiga: %s\nDigite a nova marca: ", t.marca);
            scanf("%s", troca1);
            do {printf("Confirma a alteracao? ");
                getc(stdin); scanf("%c", &confirma);
                if(confirma == 's') {strcpy(t.marca,troca1);}
            } while(confirma != 's' && confirma != 'n');
            break;
        case 2:
            printf("Modelo antigo: %s\nDigite o novo modelo: ", t.modelo);
            scanf(" %s", troca2);
            do {printf("Confirma a alteracao? ");
                getc(stdin); scanf("%c", &confirma);
                if(confirma == 's') {strcpy(t.modelo, troca2);}
            } while(confirma != 's' && confirma != 'n');
            break;
        case 3:
            printf("Ano antigo: %d\nDigite o novo ano: ", t.ano);
            scanf("%d", &troca3);
            do {printf("Confirma a alteracao? ");
                getc(stdin); scanf("%c", &confirma);
                if(confirma == 's') {t.ano = troca3;}
            } while(confirma != 's' && confirma != 'n');
            break;
        case 4:
            printf("Quilometragem antiga: %d\nDigite a nova quilometragem: ", t.quilometragem);
            scanf("%d", &troca4);
            do {printf("Confirma a alteracao? ");
                getc(stdin); scanf("%c", &confirma);
                if(confirma == 's') {t.quilometragem = troca4;}
            } while(confirma != 's' && confirma != 'n');
            break;
        case 5:
            printf("Numero de portas antigo: %d\nDigite o novo numero de portas: ", t.portas);
            scanf("%d", &troca5);
            do {printf("Confirma a alteracao? ");
                getc(stdin); scanf("%c", &confirma);
                if(confirma == 's') {t.portas= troca5;}
            } while(confirma != 's' && confirma != 'n');
            break;
        case 6:
            printf("Ar condicionado antigo: %c\nDigite se tem ar condicionado: ", t.ar_condicionado);
            getc(stdin); scanf("%c", &troca6);
            do {printf("Confirma a alteracao? ");
                getc(stdin); scanf("%c", &confirma);
                if(confirma == 's') {t.ar_condicionado = troca6;}
            } while(confirma != 's' && confirma != 'n');
            break;
      }
      //teste se quer continuar alterando
      printf("-----------------------------------------------\n" "Deseja alterar o registro novamente? ");
      do{scanf("%s", &confirmafim);
          if(confirmafim != 's' && confirmafim != 'n') {
            printf("-----------------------------------------------\n" "Resposta Invalida\nDigite s ou n\n" "Deseja alterar o registro novamente? ");}
      }while(confirmafim != 's' && confirmafim != 'n');
      if(confirmafim == 'n'){printf("-----------------------------------------------\n" "Fim das alteracoes\n");getch();}
      }while(confirmafim == 's');
      fprintf(pcop,"%s\n%s\n%d\n%s\n%d\n%d\n%c\n", t.marca, t.modelo, t.ano, t.placa, t.quilometragem, t.portas, t.ar_condicionado);
      while(fscanf(parq,"%s\n%s\n%d\n%s\n%d\n%d\n%c\n", t.marca, t.modelo, &t.ano, t.placa, &t.quilometragem, &t.portas, &t.ar_condicionado) != EOF) {
          fprintf(pcop,"%s\n%s\n%d\n%s\n%d\n%d\n%c\n", t.marca, t.modelo, t.ano, t.placa, t.quilometragem, t.portas, t.ar_condicionado);
      }
      fclose(parq);
      fclose(pcop);
      //apaga "carros" renomeia "copiacarros" como "carros"
      remove("carros.txt");
      rename("copiacarros.txt","carros.txt");
      return 0;
    }
}

int apagar() {
    registro_carros t;
    int achou = 0, item;
    char digplaca[7];
    printf("-----------------------------------------------\n" "Digite a placa: ");
    scanf("%s", digplaca);

    FILE *parq, *pcop, *parq2;
    parq = fopen("carros.txt","a+");
    if(parq == NULL){
        printf("\nNao foi possivel abrir o arquivo");
        return 1;
    }
    pcop = fopen("copiacarros.txt","w+");
        if(pcop == NULL){
        printf("\nNao foi possivel abrir o arquivo");
        return 2;
    }
    //busca em todo arquivo original a placa digitada, quando encontrada, continua
    while(fscanf(parq,"%s\n%s\n%d\n%s\n%d\n%d\n%c\n", t.marca, t.modelo, &t.ano, t.placa, &t.quilometragem, &t.portas, &t.ar_condicionado) != EOF) {
        if(strcmp(t.placa,digplaca) == 0) {
            printf("-----------------------------------------------\n" "Marca: %s\nModelo: %s\nAno de Fabricacao: %d\nPlaca: %s\nQuilometragem: %d\nPortas: %d\nAr Condicionado: %c\n", t.marca, t.modelo, t.ano, t.placa, t.quilometragem, t.portas, t.ar_condicionado);
            achou = 1;
            break;
        }
        else {
            fprintf(pcop,"%s\n%s\n%d\n%s\n%d\n%d\n%c\n", t.marca, t.modelo, t.ano, t.placa, t.quilometragem, t.portas, t.ar_condicionado);
        }
    }
    //caso nao encontre, avisa
    if(achou == 0) {
        printf("-----------------------------------------------\n" "Nao foi possivel encontrar o registro do carro\n");
        fclose(parq);
        fclose(pcop);
        return 0;
    }
    //caso encontre, pede confirmacao
    //se confirmado, ignora o registro e copia os seguintes para o arquivo auxiliar
    //se nao confirmado, copia o registro e tambem os seguintes para o auxiliar
    else {
        char confirma;
        printf("-----------------------------------------------\n" "Tem certeza que deseja apagar o registro? ");
        do { scanf("%s", &confirma);
            if(confirma == 's') {
                while(fscanf(parq,"%s\n%s\n%d\n%s\n%d\n%d\n%c\n", t.marca, t.modelo, &t.ano, t.placa, &t.quilometragem, &t.portas, &t.ar_condicionado) != EOF) {
                    fprintf(pcop,"%s\n%s\n%d\n%s\n%d\n%d\n%c\n", t.marca, t.modelo, t.ano, t.placa, t.quilometragem, t.portas, t.ar_condicionado);
                }
                printf("-----------------------------------------------\n" "Registro Apagado\n");
            }
            else if(confirma == 'n') {
                fprintf(pcop,"%s\n%s\n%d\n%s\n%d\n%d\n%c\n", t.marca, t.modelo, t.ano, t.placa, t.quilometragem, t.portas, t.ar_condicionado);
                printf("-----------------------------------------------\n" "O Registro Nao Foi Apagado\n");

            }
            if(confirma != 's' && confirma != 'n') {
                printf("-----------------------------------------------\n" "Resposta Invalida\nDigite s ou n\n" "Tem certeza que deseja apagar o registro? ");
            }
        }while(confirma != 's' && confirma != 'n');

        fclose(parq);
        fclose(pcop);
        remove("carros.txt");
        rename("copiacarros.txt","carros.txt");
        getch();
        return 0;
    }
}

int main() {
    int opcao;
    do {
        printf( "-----------------------------------------------\n" "Digite o numero da opcao desejada:\n"
        "1) Inserir novo cadastro de veiculo\n" "2) Alterar cadastro\n" "3) Mostrar os dados de um veiculo\n"
        "4) Apagar registro\n" "5) Sair\n" "-----------------------------------------------\n");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1: inserir(); break;
            case 2: alterar(); break;
            case 3: mostrar(); break;
            case 4: apagar(); break;
            default: break;
            }
    } while (opcao != 5);
    return 0;
}
