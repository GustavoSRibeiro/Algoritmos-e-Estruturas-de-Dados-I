//GUSTAVO SILVEIRA RIBEIRO 156560
#include <stdio.h>
#include <stdlib.h>

struct RegAluno {
    int ra;
    char nome[50];
    float nota1;
    float nota2;
    float nota3;
    float media;
};

typedef struct arv {
    struct RegAluno aluno;
    struct arv* esq;
    struct arv* dir;
}TArv;
typedef TArv *PArv;

PArv libera(PArv a);
void imprime(PArv a, int nivel);
PArv insere(PArv a, struct RegAluno b);
int verificaRA(PArv a, int ra);
void buscaReprov(PArv a);
void buscaRA(PArv a, int ra);
PArv percorre(PArv a);
PArv remover(PArv a);
struct RegAluno ler_dados(struct RegAluno novo, PArv arvore);

/*a main apresenta o menu de opcoes e recebe a opcao escolhida, chama as funcoes dependendo 
da opcao e finaliza quando o usuario escolher a opcao 7 q sai do loop, caso contrario ele
voltarar a oferecer o menu de opcoes*/
int main(){
    int opcao=0, procRA;
    PArv arvore = NULL;
    struct RegAluno novo;

    do{

        printf( "ESCOLHA UMA OPCAO ABAIXO:\n\n"
                "1) Inserir um aluno na árvore;\n2) Imprimir a árvore atual;\n"
                "3) Mostrar os dados dos alunos que foram reprovados;\n"
                "4) Excluir da árvore todos os alunos que foram reprovados;\n"
                "5) Mostrar todos os alunos com chave menor ou igual a um dado RA;\n"
                "6) Iniciar uma nova árvore;\n7) Sair.\n\nOpcao: ");

        scanf("%d", &opcao);

        switch (opcao){

            case 1: // INSERIR NOVO ALUNO
                /*chama a funcao que le os dados e depois a que insere na arvore o novo noh*/
                novo = ler_dados(novo, arvore);
                arvore = insere(arvore, novo);
                printf("\nAluno inserido. (TECLE ENTER)\n");
                getc(stdin); //serve para pausar
                getc(stdin);
                break;

            case 2: // IMPRIMIR ARVORE
                /*imprime a arvore formada ate entao*/
                printf("\n");
                if(arvore != NULL){
                    imprime(arvore, 0);
                    printf("\nArvore imprimida. (TECLE ENTER)\n");
                }
                else{
                    printf("Arvore vazia. (TECLE ENTER)\n");
                }
                getc(stdin);
                getc(stdin);
                break;

            case 3: // MOSTRAR REPROVADOS
                /*chama a funcao que busca e imprime os alunos come media  < 6.00*/
                printf("\nLista de alunos reprovados: \n\n");
                buscaReprov(arvore);
                printf("Fim da lista. (TECLE ENTER)\n");
                getc(stdin);
                getc(stdin);
                break;
            
            case 4: // EXCLUIR REPROVADOS
                /*chama a funcao que percorre e exclui da arvore os reprovados*/
                arvore = percorre(arvore);
                printf("\nReprovados excluidos. (TECLE ENTER)\n");
                getc(stdin);
                getc(stdin);
                break;
           
            case 5: // MOSTRAR ALUNOS > OU =
                /*pede um RA e chama a funcao que busca e imprime os RAs menor ou igual aquele pedido*/
                printf("\nInsira um RA: ");
                while(scanf("%d", &procRA) == 0){
                    getc(stdin);
                    printf("\nDIGITO INVALIDO!!!\nInsira um RA: ");
                }
                printf("\nLista de alunos com RA menor ou igual: \n\n");
                buscaRA(arvore, procRA);
                printf("Fim da lista. (TECLE ENTER)\n");
                getc(stdin);
                getc(stdin);
                break;
              
            case 6: // NOVA ARVORE
                /*libera a arvore ate entao inserida e deixa pronto para comecar inserir uma nova*/
                arvore = libera(arvore);
                
                printf("\nArvore apagada. Pronto para receber Nova Arvore!\n\n");
                getc(stdin);
                getc(stdin);
                break;

            case 7: // SAIR
                /*apenas libera a arvore e deixa pronto para finalizar o programa*/
                arvore = libera(arvore);
                printf("\nFim do Programa.\n");
                break;

            default:
                /*quando inserido uma opcao diferente das acima, ou quando insere um caracter indevido*/
                printf("\nOPCAO INVALIDA!!! (TECLE ENTER)\n\n");
                getc(stdin);
                getc(stdin);
                break;
        }

    }while(opcao != 7);
    return 0;
}

/*funcao que le os dados q serao digitados e guarda num registro, e chama a funcao que 
verifica se o ra eh repetido*/
struct RegAluno ler_dados(struct RegAluno novo, PArv arvore){
    int testeRA;
    char x;

    do{

        printf("\nDigite o RA do aluno: ");
        // verifica se nao foi inserido um digito indevido na entrada de inteiro
        while(scanf("%d", &novo.ra) == 0){ 
            getc(stdin);
            printf("\nDIGITO INVALIDO!!!\nDigite o RA do aluno: ");
        }

        testeRA = verificaRA(arvore, novo.ra);
        if(testeRA)
            printf("\nO RA informado ja foi inserido. Insira um RA diferente.\n");

    }while(testeRA);

    getc(stdin);
    printf("\nDigite o NOME do aluno: ");
    scanf("%[^\n]s", novo.nome);

    // verifica se nao foi inserido um digito indevido na entrada de float
    // ou se nao esta no intervalo de 0 a 10
    printf("\nDigite a 1o NOTA do aluno: ");
    while(scanf("%f", &novo.nota1) == 0 || novo.nota1 < 0 || novo.nota1 > 10){
        getc(stdin);
        printf("\nDIGITO INVALIDO!!!\nDigite a 1o NOTA do aluno: ");
    }

    printf("\nDigite a 2o NOTA do aluno: ");
    while(scanf("%f", &novo.nota2) == 0 || novo.nota2 < 0 || novo.nota2 > 10){
        getc(stdin);
        printf("\nDIGITO INVALIDO!!!\nDigite a 2o NOTA do aluno: ");
    }

    printf("\nDigite a 3o NOTA do aluno: ");        
    while(scanf("%f", &novo.nota3) == 0 || novo.nota3 < 0 || novo.nota3 > 10){
        getc(stdin);
        printf("\nDIGITO INVALIDO!!!\nDigite a 3o NOTA do aluno: ");  
    }
    
    novo.media = (novo.nota1 + novo.nota2 + novo.nota3) / 3.0;
    
    return novo;
}

/*a funcao "remover" verifica a media, caso menor que 6 verifica 4 possiveis casos do noh:
1o - o noh eh uma folha, nesse caso apenas da free e retorna NULL;
2o - quando o noh soh tem filho a esquerda, entao o filho a esquerda ira sobrescrever esse noh;
3o - quando o noh soh tem filho a direita, semelhante ao caso 2;
4o - quando tem filho dos dois lados, entao se busca o maior noh na subarvore a esquerda, ele 
substituira o noh retirado, ele vai ser copiado para o novo local e sera apagado do antigo local.*/
PArv remover(PArv a){
    PArv aux = NULL, pai, filho;

    if(a == NULL)
        return NULL;

    if(a->aluno.media < 6.00){

        if(a->esq == NULL && a->dir == NULL){ // 1o caso

            free(a);
            return NULL;
        }

        else if(a->esq != NULL && a->dir == NULL){ // 2o caso
            aux = a;
            a = a->esq;
            free(aux);
        }

        else if(a->esq == NULL && a->dir != NULL){ // 3o caso
            aux = a;
            a = a->dir;
            free(aux);
        }

        else{ // 4o caso
            pai = a;
            filho = a->esq;

            while(filho->dir != NULL){
                pai = filho;
                filho = filho->dir;
            }

            a->aluno = filho->aluno;

            if(pai == a){
                pai->esq = filho->esq;
            }

            else{
                pai->dir = filho->esq;
            }
            free(filho);
        }
    }
    return a;
}

/*percorre toda a arvore e chama "remover" em todos os nohs, retorna NULL quando o noh 
eh removido e quando nao retorna o mesmo endereco*/
PArv percorre(PArv a){
    do{
        a = remover(a);
    }while(a != NULL && a->aluno.media < 6);

    if(a != NULL){

        a->esq = percorre(a->esq);
      
        a->dir = percorre(a->dir);
    }
    else{
        return NULL;
    }
    return a;
}

/*pecorre toda a arvore e imprime apenas quando for menor ou igual a um dado RA*/
void buscaRA(PArv a, int ra){

    if(a != NULL){
      
        buscaRA(a->esq, ra);

        if(ra >= a->aluno.ra){
            printf("RA: %d\n", a->aluno.ra);
            printf("NOME: %s\n", a->aluno.nome);
            printf("NOTA 1: %.2f\n", a->aluno.nota1);
            printf("NOTA 2: %.2f\n", a->aluno.nota2);
            printf("NOTA 3: %.2f\n", a->aluno.nota3);
            printf("MEDIA: %.2f\n\n", a->aluno.media);
        }
        //enquanto ra menor que o ra do noh ele chama a direita
        if(ra > a->aluno.ra)
            buscaRA(a->dir, ra);
    }
}

/*percorre recursivamente toda a arvore comparando o ra dos nohs com o novo ra, 
caso encontrar retornara 1 para indicar que eh repetido*/
void buscaReprov(PArv a){

    if(a != NULL){

        buscaReprov(a->esq);

        if(a->aluno.media < 6.00){
            printf("RA: %d\n", a->aluno.ra);
            printf("NOME: %s\n", a->aluno.nome);
            printf("NOTA 1: %.2f\n", a->aluno.nota1);
            printf("NOTA 2: %.2f\n", a->aluno.nota2);
            printf("NOTA 3: %.2f\n", a->aluno.nota3);
            printf("MEDIA: %.2f\n\n", a->aluno.media);
        }

        buscaReprov(a->dir);
    }
}

/*percorre recursivamente toda a arvore comparando o ra dos nohs com o novo ra, 
caso encontrar retornara 1 para indicar que eh repetido*/
int verificaRA(PArv a, int ra){
    int x=0;
    if(a != NULL){
        if(ra == a->aluno.ra){
            return 1;
        }
        else if(ra > a->aluno.ra){
            x = verificaRA(a->dir, ra);
        }
        else{
            x = verificaRA(a->esq, ra);
        }
    }
    return x;
}

/*a funcao "insere" aloca um novo no caso esteja NULL, caso contrario ele testa se o ra 
eh menor ou maior que o ra do noh, entao ele recursivamente avanca para os filhos para 
inserir o ra no lugar que deve ficar*/
PArv insere(PArv a, struct RegAluno b){
    PArv novo;
    if(a == NULL){
        novo = (PArv) malloc(sizeof(TArv));
        novo->aluno = b;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    else if(b.ra < a->aluno.ra){
        a->esq = insere(a->esq, b);
    }
    else{
        a->dir = insere(a->dir, b);
    }
    return a;
}

/*a funcao imprime usa de recursividade, ela avanca nos nohs a esquerda ate encontrar
um noh terminal e entao volta a recursao imprimindo e chamando os nohs a direita, durante
a recursao, eh usado um contador para saber a altura do noh terminal, e imprimir essa
altura vezes "\t" para ficar com a identacao correta*/
void imprime(PArv a, int nivel){

    if(a != NULL){
        imprime(a->esq, nivel+1);

        for(int i = 0; i < nivel; i++)
            printf("\t");
        printf("%d\n", a->aluno.ra);

        imprime(a->dir, nivel+1);
    }
}

/*recursivamente vai ate os nohs terminais e volta liberando a memoria alocada*/
PArv libera(PArv a){

    if(a != NULL){
        a->esq = libera(a->esq);
        a->dir = libera(a->dir);
        free(a);
    }
    return NULL;
}