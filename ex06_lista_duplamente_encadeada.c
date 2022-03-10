//GUSTAVO SILVEIRA RIBEIRO 156560
#include <stdio.h>
#include <stdlib.h>

typedef struct lista2{
    int coef;
    int grau;
    struct lista2* ant;
    struct lista2* prox;
}TLista2;

typedef TLista2 *PLista2;

PLista2 comeca(PLista2 l);
PLista2 pre_insere(PLista2 l);
PLista2 Insere_Ordenado(PLista2 l, int coef, int grau);
void remove_coef_zero(PLista2 l);
PLista2 calcula(PLista2 p3, PLista2 p1, PLista2 p2, int sinal);
PLista2 deriva(PLista2 d, PLista2 p);
void imprime(PLista2 l);
void liberar(PLista2 l);


/*na "main" eh onde declara e e liberas as listas, eh onde tem o menu de opcoes, 
o programa nao faz com que inicie ja inserindo os polinomios, porem as outras 
opcoes soh seram acessiveis assim que ja ter valores inseridos nas listas, logo
a primeira opcao que deve ser escolhida eh a 1, as opcoes 2, 3 e 4 sao para somar
subtrair e derivar, respectivamente, a 5 eh para finalizar o programa, qualquer 
outro valor ira mostrar uma mensagem de erro e pedir uma opcao valida*/
int main() {
    PLista2 p1 = NULL, p2 = NULL;
    int opcao;

    do{ //informa as opcoes e recebe a opcao digitada
        printf("--------------------------\n");
        printf("ESCOLHA UMA OPCAO:\n\n");
        printf("1)Inserir novos polinomios\n");
        printf("2)Somar polinomios\n");
        printf("3)Subtrair polinomios\n");
        printf("4)Derivar um polinomio\n");
        printf("5)Sair\n");
        printf("--------------------------\n");
        scanf("%d", &opcao);
        printf("--------------------------\n");

        switch(opcao){

            //INSERIR
            case 1: //nesse caso, ira inserir novas listas, caso nao tenha nenhuma, apenas comeca
                if(p1 != NULL && p2 != NULL){//caso tenha, libera as que tinha, inicializa novamente
                    liberar(p1); //inicializa novamente e comeca
                    liberar(p2);
                    p1 = NULL;
                    p2 = NULL;
                }
                p1 = comeca(p1);
                p2 = comeca(p2);
                break;

            //SOMAR
            case 2: //nesse caso, verifica primeiro se foi inserido listas anteriorente
                if(p1 != NULL && p2 != NULL){ //CASO SIM, cria uma lista para guardar o resultado(p3)
                    PLista2 p3 = NULL; //e passa para funcao "calcula" as 3 lista e o valor 1
                    p3 = calcula(p3, p1, p2, 1); //relativo a opcao entre somar e subtrair, 
                    printf("Resultado = ");      //nesse caso somar
                    imprime(p3);//imprime a lista resultado e libera ela
                    liberar(p3);
                    printf("\n");
                }
                else{ //CASO NAO, informa a mensagem de erro e pede para inseris as lista na opcao 1
                    printf("Nao ha polinomios para calcular\n");
                    printf("Insira-os na opcao 1\n");
                }
                break;

            //SUBTRAIR
            case 3: //nesse caso, eh exatamente o mesmo caso da 2, com excecao de que e enviado
                if(p1 != NULL && p2 != NULL){ //-1 para funcao "calcula", relativo a oopcao entre
                    PLista2 p3 = NULL;        //somar e subtrair, nesse caso subtrair
                    p3 = calcula(p3, p1, p2, -1);
                    printf("Resultado = ");
                    imprime(p3);
                    liberar(p3);
                    printf("\n");
                }
                else{
                    printf("Nao ha polinomios para calcular\n");
                    printf("Insira-os na opcao 1\n");
                }
                break;

            //DERIVAR
            case 4: //nesse caso, verifica primeiro se foi inserido listas anteriorente
                if(p1 != NULL && p2 != NULL){
                    PLista2 p3 = NULL;//CASO SIM, cria uma lista para guardar o resultado(p3)

                    do{//pergunta qual dos polinomios(listas) deseja derivar
                        printf("Qual polinomio deseja derivar(1 ou 2)?\n");
                        printf("P1 = "); //mostra os dois polinomios
                        imprime(p1);
                        printf("\nP2 = ");
                        imprime(p2);
                        printf("\n--------------------------\n");
                        scanf("%d", &opcao);
                        printf("--------------------------");

                        if(opcao == 1){//de acordo com a opcao(1 ou 2), manda a p3 e o polinomio 
                            p3 = deriva(p3, p1); //a deriva para funcao "deriva"
                        }
                        else if(opcao == 2){
                            p3 = deriva(p3, p2);
                        }
                        else{//caso nao escolha 1 nem 2, informa o erro e pede para inserir uma
                            printf("\nOPCAO INVALIDA!!!\n"); //dessas duas opcoes
                            getc(stdin);//isso evita bugs no sistema quando inserido caracteres indevidos
                            printf("--------------------------\n");
                        }

                    }while(opcao != 1 && opcao != 2);

                    printf("\nResultado = ");
                    imprime(p3);//imprime a lista resultado e libera ela
                    liberar(p3);
                    printf("\n");

                }
                else{//CASO NAO, informa a mensagem de erro e pede para inseris as lista na opcao 1
                    printf("Nao ha polinomios para calcular\n");
                    printf("Insira-os na opcao 1\n");
                }
                break;
            
            //SAIR
            case 5:
                printf("Fim do Programa.");
                break;

            default: 
                printf("OPCAO INVALIDA!!!\n");
                getc(stdin);//isso evita bugs no sistema quando inserido caracteres indevidos
                break;
        }

    }while(opcao != 5);//finaliza quando escolher a opcao 5

    liberar(p1);//liberas as listas
    liberar(p2);
    return 0;
}


/* funcao "comeca" pede um polinomio e chama "pre insere" que vai filtrar e inserir 
o polinomio, quando volta ao "comeca", verifica se o primeiro monomio, que é o maior, 
tem coeficiente ZERO, CASO SIM, informa o erro, libera a lista e reinicia ela pedindo 
um novo polinomio, CASO NAO, verifica no polinomio se ha monomios com coeficiente ZERO, 
caso encontrar, remove tal monomio */
PLista2 comeca(PLista2 l){
    do{
      
        printf("insira um polinomio: ");
        l = pre_insere(l);

        if(l->coef == 0){ //nao aceita polinomios cujo o monomio de maior grau tenha coef ZERO
            printf("ERRO!!!\n"); // invalida o polinomio inteiro e pede que insira outro
            liberar(l);
            l = NULL;
        }
        else if(l != NULL){ //remove os monomios com coef ZERO, exceto o maior
            remove_coef_zero(l);
        }

    }while(l == NULL);

    return l;
}


/*funcao "pre insere" funciona como um filtro, eh lido um caracter por vez e ele passa 
pelo filtro para verificar se eh o coeficiente, o "x", o "^" e o grau, e todos sao lidos 
como tipo char, quando sao digitos eles sao convertidos para int, espacos sao ignorados, 
quando capturado as informacoes de um monomio, eh passado como parametro para funcao 
"insere ordenado", entende o fim do monomio ao encontrar um operador '+' ou '-' e 
finaliza o polinomio ao encontrar '\n'*/
PLista2 pre_insere(PLista2 l){
    int coef = 0, grau=0, y=0, coef_grau=0, ok_coef=0;
    char sinal = ' ', x;

    scanf(" %c", &x);
    do{
        do{   

            if(x == ' '){ //ignora espacos
                scanf("%c", &x);
            }

            if(x == '-' || x == '+'){ //captura o operador para alterar o sinal do coef caso necessario
                sinal = x;    //geralmente o 1o monomio nao tem, mas pode ter caso seja o "-"
                scanf("%c", &x);
            }

            if(x == 'x'){ //quando encontra o 'x', significa que acabou o coef, se em seguida vier "^",
                          //le o proximo em busca do "^"
                scanf("%c", &x); 
                                  
                while(x == ' '){
                    scanf("%c", &x);//evita erros com espaco, ignora espacos
                }

                if(x == '^'){ //caso encontre, ativa a chave para add valor ao grau
                    coef_grau=1;
                }

                else{ // caso nao, subentende que o grau eh 1
                    grau = 1;
                    break;
                }
            }

            y = x - '0'; //conversor baseado nos valores inteiros que os caracteres tem na tabela ASCII
            if(y >= 0 && y <= 9){ //quando corresponder a um numero, testara se eh o coef ou o grau
                                  //o parametro do teste vem do teste do "x^", que deixa em ZERO
                if(coef_grau == 0){//quando coef, e em UM quando grau
                    coef = coef * 10 + y;
                    ok_coef = 1;
                }

                else{
                    grau = grau * 10 + y;//tanto o grau quanto o coef eh calculado somando o valor 
                }    // capturado atual com o valor que pode ter anteriormente, 
                    //que sao as seguintes casas decimais, por isso a multiplicacao por 10
            }

            if(x == '\n')// forca a parada quando encontra o '/n', ou seja, o fim do polinomio
                break;

            scanf("%c", &x); 

        }while(x != '-' && x != '+'); //ao encontrar o operador, termina de capturar o monomio

        if(ok_coef == 0) //no caso de nao ter coef, subentende que o coef eh 1
            coef = 1;

        if(sinal == '-') //quando "-", negativa o coef
          coef *= -1;

        l = Insere_Ordenado(l, coef, grau); // insere o monomio na lista, em seguida ZERA as variaveis
        coef = 0;                           // para repetir processo
        grau = 0;
        coef_grau = 0;
        ok_coef = 0; 

    }while(x != '\n');

    return l;
}


/*funcao "insere ordenado" recebe os valores de "pre insere", eh ordenado decrescente 
em relacao ao grau, eh alocado um novo noh e ele eh posicionado no na posicao correta 
na lista duplamente encadeada*/
PLista2 Insere_Ordenado(PLista2 l, int coef, int grau){
    PLista2 aux;
    PLista2 novo = (PLista2) malloc(sizeof(TLista2)); //aloca o novo noh

    novo->grau = grau; //insere as informacoes no noh
    novo->coef = coef;

    if (l == NULL) { //caso a lista vazia, apenas insere e aponta ant e prox pra NULL 
        novo->ant = NULL; 
        novo->prox = NULL;
        l = novo;
    }

    else{ //caso contrario, procura o local a inserir o noh
        aux = l; //aux sera o noh atual que esta sendo comparado

        while(aux->prox != NULL && aux->grau > grau){ //enquanto o prox nao for NULL, ou seja,
            aux = aux->prox;//o atual nao for o ultimo E o atual for maior que o novo, avanca na lista
        }
        
        if(aux->grau > grau){ //caso chegue aq por ter chegado ao fim, insere o noh no final
            aux->prox = novo; //o ultimo aponta para o novo, o nova aponta pro ultimo(ant) para NULL
            novo->prox = NULL;//e o novo passa a ser o ultimo
            novo->ant = aux;
        }

        else{ // caso chegue aqui por que o novo foi maior que o atual, o novo aponta para o atual(prox)
            novo->prox = aux; //e para o ant que o atual apontava
            novo->ant = aux->ant;

            if(aux->ant != NULL){ //se o ant nao era NULL, o ant aponta para o novo
                aux->ant->prox = novo;
            }

            else{ // se era NULL. novo passa a ser o primeiro(l), e ele aponta para NULL(ant)
                l = novo;
                novo->ant = NULL;
            }
            aux->ant = novo; //o atual aponta para o novo(ant)
        }
    }

    return l;
}


/*funcao "remove coef zero" remove os monomios com o coeficiente ZERO*/
void remove_coef_zero(PLista2 l){
    PLista2 aux;

    while(l != NULL){

        if(l->coef == 0){//quando encotra um monomio com coef ZERO remove ele, mas antes mantem
                          //o encadeamento da lista
            if(l->prox != NULL){//se nao for o ultimo, faz com que o proximo do que sera excluido(atual)
                l->prox->ant = l->ant; //aponte para o anterior do atual
            }

            if(l->ant != NULL){//se nao for o primeiro, faz com que o anterio do que sera excluido(atual)
                l->ant->prox = l->prox;//aponte para o proximo do atual
            }

            aux = l; //guarda o endereco do atual
            l = l->prox;//avanca na lista
            free(aux); //exclui o atual
        }

        else {//se nao encontra o coef ZERO, avanca na lista
            l = l->prox;
        }
    }
}


/*funcao "calcula" executa a soma e a subtracao, dependendo do parametro sinal, 
quando for subtrair o programa multiplica o 2o monomio por -1, invertendo o sinal 
dele, e dessa forma a soma "P1 + (-P2) = P1 - P2", a funcao compara o grau dos 
monomios, quando iguais, soma-os, insere na lista resultado e avanca em ambas listas, 
quando nao, apenas pega o de que possui grau maior(ou pode ser o caso da outra ter 
acabado), adiciona apenas esse monomio na lista resultado e avanca apenas nessa lista, 
e finaliza quando acabar as duas listas*/
PLista2 calcula(PLista2 p3, PLista2 p1, PLista2 p2, int sinal){
    int coef, grau, nulo=0;

    do{

        if(p1 != NULL && p2 != NULL){//enquanto houver monomios nas duas lista

            if(p1->grau > p2->grau){//caso do grau da PRIMEIRA ser MAIOR que o grau da SEGUNDA
                coef = p1->coef; //pega apenas os dados da 1a
                grau = p1->grau;
                p1 = p1->prox; //avanca apenas na 1a
            }
            else if(p1->grau < p2->grau){//caso do grau da PRIMEIRA ser MENOR que o grau da SEGUNDA
                coef =p2->coef * sinal; //sempre quando pega o coef da 2a, ele e multiplicado 
                grau = p2->grau;        //pelo sinal, eh oq define a soma ou subtracao
                p2 = p2->prox;          //avanca apenas na 2a
            }
            else if(p1->grau == p2->grau){ ///caso do grau da PRIMEIRA ser IGUAL ao grau da SEGUNDA
                coef =p1->coef + (p2->coef * sinal); //pega a soma, lembrando que a seguda eh
                grau = p1->grau;            // multiplicada em questao da soma/subtracao
                p1 = p1->prox;      
                p2 = p2->prox;              // avanca em ambas listas
            }
        }
        else{//quando pelo menos uma acabar

            if(p2 == NULL){ // caso acabe a 2a, pega apenas da 1a
                coef = p1->coef;
                grau = p1->grau;
                p1 = p1->prox;
            }
            else if(p1 == NULL){ // caso acabe a 1a, pega apenas da 2a
                coef =p2->coef * sinal;
                grau = p2->grau;
                p2 = p2->prox;
            }
        }

        p3 = Insere_Ordenado(p3, coef, grau); //insere na lista resultado(p3) o coef e o grau obtido
        
    }while(p1 != NULL || p2 != NULL); //acaba quando nenhuma for nao NULL, ou seja, quando ambas NULL
    
    remove_coef_zero(p3);   //remove os monomios com coef ZERO
    
    if(p3 == NULL)    //pode haver o caso da soma/subtracao vier todos monomios com coef ZERO,
        p3 = Insere_Ordenado(p3, 0, 0);//e eles seram removidas, mas para a p3 nao ficar vazia, 
                                      //nesse caso, eh inserido um monomio de coef e grau ZERO
    return p3;
}


/*funcao "deriva" faz a derivada do polinomio, a derivada de cada monomio eh da 
segunte forma, o coef eh igual ao coef vezes o grau(coef=coef*grau), o grau eh 
igual ao grau -1(grau=grau-1), monimio que eh termo idependente de x(com grau igual 
a ZERO somem ao derivar, monomio com grau 1 ficam apenas com o coef apos derivar*/
PLista2 deriva(PLista2 d, PLista2 p){
    int coef, grau;

    do{
        if(p->grau > 0){                //so pega monomios cujo grau maior que zero
            coef = p->coef * p->grau;   //a regra do tombo na derivada eh multiplicar o 
            grau = p->grau - 1;         //coef pelo grau e subtrair 1 do grau
            d = Insere_Ordenado(d, coef, grau); //insere o valor derivado na lista resultado
        }
        p = p->prox;    //avanca na lista a ser derivada
        
    }while(p != NULL);  //acaba quando chega ao fim da lista a derivar

    return d;
}


/*funcao "imprime" imprime a lista formatados e forma de polinomio, utiliza de recursividade*/
void imprime(PLista2 l){

    if(l->coef > 0 && l->ant != NULL)//como o sinal "+" de positivo nao aparece naturalmente
        printf("+"); //a frente de num positivos, ele eh colocado, exceto quando o primeiro
                     //monomio do polinomio, no caso do "-" do negativo nao eh necessario
    if(l->grau == 0) //quando o grau zero, eh o termo independente de x, ou seja, apenas coef
        printf("%d", l->coef);

    if(l->grau == 1) //quando o grau 1, o grau fica oculto, ou seja, apenas coef e "x"
        printf("%dx", l->coef);

    if(l->grau > 1) //quando o grau maior que 1, aparece o coef, "x^" e o grau
        printf("%dx^%d", l->coef, l->grau);

    if(l->prox != NULL) //enquanto ainda houver proximo na lista, avanca com recursividade
        imprime(l->prox); //para imprimir os proximos tbm
}


/*funcao "libera" que libera cada noh da lista com recursividade, a funcao testa se 
o atual noh eh NULL, caso nao, chama "libera" com o proximo da lista resursivamente, 
ate que o proximo seja NULL, ai entao ele volta liberando cada noh do final ao inicio*/
void liberar(PLista2 l){
    if(l != NULL){
        liberar(l->prox);
        free(l);
    }
}
