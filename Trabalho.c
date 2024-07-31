#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20000000
#define MAX_NOME 100
#define TAM_NOME_ARQUIVO 100
#define LINESIZE 1024

typedef struct
{
    int RG;
    char nome[MAX_NOME];
} Registro;

typedef struct
{
    Registro *A;
    int nElem;
} ListaSeq;

typedef struct{
    int RG;
    char nome[MAX_NOME];
} RegistroEnc;

typedef struct aux{
    Registro B;
    struct aux* prox;
} ElementoEnc;

typedef struct{
    ElementoEnc* inicio;
} ListaEnc;

void iniciaLista(char* nomeArquivo);

void inicializaLista(ListaSeq* lista);
void lerArquivo(ListaSeq* lista, char* nome);
void exibirLista(ListaSeq* lista);

void inserirNoInicio(ListaSeq* lista, ListaEnc* listaE);
void inserirNoFim(ListaSeq* lista, ListaEnc* listaE);
void inserirNoPosicaoN(ListaSeq* lista, ListaEnc* listaE);
void excluirNoInicio(ListaSeq* lista, ListaEnc* listaE);
void excluirNoFim(ListaSeq* lista, ListaEnc* listaE);
void excluirNoPosicaoN(ListaSeq* lista, ListaEnc* listaE);
void buscaSequencial(ListaSeq* lista, ListaEnc* listaE);
void salvarLista(ListaSeq* lista, char* nome);

void imprimeApresentacao(char* nome, int RG, double tempo, int C, int M, int N);

void inicializarListaEnc(ListaEnc* listaE);
int tamanhoListaEnc(ListaEnc* listaE);
void exibirListaEnc(ListaEnc* listaE);
void lerArquivoEnc(ListaEnc* listaE, char* nome);

void buscaSequencialEnc(ListaEnc* listaE, int RG);
void inserirNoInicioEnc(ListaEnc* listaEnc, char* nome, int RG);
void funcaoAux(ListaEnc* listaEnc, ElementoEnc** ant, int* M, int* N);
void funcaoAux2(ListaEnc* listaEnc, ElementoEnc** ant, int* M, int* N);
void funcaoAux3(ListaEnc* listaEnc, ElementoEnc** ant, ElementoEnc**atual, int* M, int* N);
void funcaoAux4(ListaEnc* listaEnc, ElementoEnc** ant, ElementoEnc**atual, int* M, int* N, int pos);
void inserirNoFimEnc(ListaEnc* listaEnc, char* nome, int RG);
void inserirNoPosicaoNEnc(ListaEnc* listaEnc, char* nome, int RG, int pos);
int listaVazia(ListaEnc* listaEnc);
void excluirNoInicioEnc(ListaEnc* listaEnc);
void excluirNoFimEnc(ListaEnc* listaEnc);
void excluirNoPosicaoNEnc(ListaEnc* listaEnc, int pos);
void salvarListaEnc(ListaEnc* listaEnc, char* nome);
void reinicializarListaEnc(ListaEnc* listaEnc);

int main()
{
    char opcaoLista, nomeArquivo[TAM_NOME_ARQUIVO];

    do
    {
        printf("Abertura inicial de arquivo...\n(a) Arquivo 10\n(b) Arquivo 50\n(c) Arquivo 100\n(d) Arquivo 1K\n(e) Arquivo 10K\n(f) Arquivo 1M\n(g) Arquivo 100M\n");
        printf("Insira a opcao que deseja utilizar: ");
        scanf("%c", &opcaoLista);
        switch(opcaoLista)
        {
            case 'a':
                system("cls");
                printf("Arquivo 10 escolhido para leitura\n\n");
                strcpy(nomeArquivo, "NomeRG10");
                iniciaLista(nomeArquivo);
                break;
            case 'b':
                system("cls");
                printf("Arquivo 50 escolhido para leitura\n\n");
                strcpy(nomeArquivo, "NomeRG50");
                iniciaLista(nomeArquivo);
                break;
            case 'c':
                system("cls");
                printf("Arquivo 100 escolhido para leitura\n\n");
                strcpy(nomeArquivo, "NomeRG100");
                iniciaLista(nomeArquivo);
                break;
            case 'd':
                system("cls");
                printf("Arquivo 1K escolhido para leitura\n\n");
                strcpy(nomeArquivo, "NomeRG1K");
                iniciaLista(nomeArquivo);
                break;
            case 'e':
                system("cls");
                printf("Arquivo 10K escolhido para leitura\n\n");
                strcpy(nomeArquivo, "NomeRG10K");
                iniciaLista(nomeArquivo);
                break;
            case 'f':
                system("cls");
                printf("Arquivo 1M escolhido para leitura\n\n");
                strcpy(nomeArquivo, "NomeRG1M");
                iniciaLista(nomeArquivo);
                break;
            case 'g':
                system("cls");
                printf("Arquivo 100M escolhido para leitura\n\n");
                strcpy(nomeArquivo, "NomeRG100M");
                iniciaLista(nomeArquivo);
                break;
            default:
                printf("\nOpcao invalida...\n");
                system("pause");
                getchar();
                system("cls");
        }
    } while(opcaoLista != 'a' || opcaoLista != 'b' || opcaoLista != 'c' || opcaoLista != 'd' || opcaoLista != 'e' || opcaoLista != 'f' || opcaoLista != 'g');

    return 0;
}

void iniciaLista(char* nomeArquivo)
{
    ListaSeq listaS;
    ListaEnc listaE;
    int encerraPrograma = 0;
    int funcaoEscolhida;
    char nomeArquivoP[TAM_NOME_ARQUIVO];

    listaS.A = (Registro*) malloc (sizeof(Registro) * MAX);
    if(listaS.A == NULL)
    {
        printf("Erro na alocacao da lista sequencial...");
        exit(1);
    }

    inicializaLista(&listaS);
    inicializarListaEnc(&listaE);
    lerArquivo(&listaS, nomeArquivo);
    lerArquivoEnc(&listaE, nomeArquivo);

    while(encerraPrograma != 1)
    {
        printf("Escolha alguma das funcoes abaixo:\n");
        printf("(1) Insercao de um no no inicio da lista e apresentar Nome, RG, C(n), M(n), Tempo de execucao e sua posicao N na lista.\n");
        printf("(2) Insercao de um no no fim da lista e apresentar Nome, RG, C(n), M(n), Tempo de execucao e sua posicao N na lista.\n");
        printf("(3) Insercao de um no na posicao N e apresentar Nome, RG, C(n), M(n), Tempo de execucao e sua posicao N na lista.\n");
        printf("(4) Retirar um no do inicio da lista e apresentar Nome, RG, C(n), M(n), Tempo de execucao e sua posicao N na lista.\n");
        printf("(5) Retirar um no no fim da lista e apresentar Nome, RG, C(n), M(n), Tempo de execucao e sua posicao N na lista.\n");
        printf("(6) Retirar um no na posicao N e apresentar Nome, RG, C(n), M(n), Tempo de execucao e sua posicao N na lista.\n");
        printf("(7) Procurar um no com o campo RG e apresentar Nome, RG, C(n), M(n), Tempo de execucao e sua posicao N na lista.\n");
        printf("(8) Mostrar a lista na tela.\n");
        printf("(9) Salvar a lista em um arquivo.\n");
        printf("(10) Ler a lista de um arquivo.\n");
        printf("(11) Sair do sistema.\n");
        scanf("%d", &funcaoEscolhida);

        switch(funcaoEscolhida)
        {
            case 1:
                inserirNoInicio(&listaS, &listaE);
                system("cls");
                break;
            case 2:
                inserirNoFim(&listaS, &listaE);
                system("cls");
                break;
            case 3:
                inserirNoPosicaoN(&listaS, &listaE);
                system("cls");
                break;
            case 4:
                excluirNoInicio(&listaS, &listaE);
                system("cls");
                break;
            case 5:
                excluirNoFim(&listaS, &listaE);
                system("cls");
                break;
            case 6:
                excluirNoPosicaoN(&listaS, &listaE);
                system("cls");
                break;
            case 7:
                buscaSequencial(&listaS, &listaE);
                system("cls");
                break;
            case 8:
                system("cls");
                printf("Exibindo as listas na tela:\n\n");
                exibirLista(&listaS);
                exibirListaEnc(&listaE);
                break;
            case 9:
                system("cls");
                getchar();
                printf("Digite o nome do arquivo que deseja salvar a lista sequencial (sem o .txt): ");
                if(fgets(nomeArquivoP, TAM_NOME_ARQUIVO, stdin))
                {
                    nomeArquivoP[strcspn(nomeArquivoP, "\n")] = 0;
                    printf("Salvando arquivo...\n");
                    salvarLista(&listaS, nomeArquivoP);
                    printf("Arquivo salvo com sucesso.\n");
                    system("pause");
                    system("cls");
                    printf("Digite o nome do arquivo que deseja salvar a lista encadeada (sem o .txt): ");
                    if(fgets(nomeArquivoP, TAM_NOME_ARQUIVO, stdin))
                    {
                        nomeArquivoP[strcspn(nomeArquivoP, "\n")] = 0;
                        printf("Salvando arquivo...\n");
                        salvarListaEnc(&listaE, nomeArquivoP);
                        printf("Arquivo salvo com sucesso.\n");
                        system("pause");
                        system("cls");
                    }
                }
                break;
            case 10:
                system("cls");
                getchar();
                printf("Digite o nome do arquivo que deseja ler (sem o .txt): ");
                if(fgets(nomeArquivoP, TAM_NOME_ARQUIVO, stdin))
                {
                    nomeArquivoP[strcspn(nomeArquivoP, "\n")] = 0;
                    inicializaLista(&listaS);
                    lerArquivo(&listaS, nomeArquivoP);
                    reinicializarListaEnc(&listaE);
                    lerArquivoEnc(&listaE, nomeArquivoP);
                }
                break;
            case 11:
                system("cls");
                printf("Encerrando o programa...");
                free(listaS.A);
                reinicializarListaEnc(&listaE);
                exit(0);
                break;
            default:
                printf("Opcao invalida...\n");
                system("pause");
                system("cls");
        }
    }
}

void inicializaLista(ListaSeq* lista)
{
    lista->nElem = 0;
}

void lerArquivo(ListaSeq* lista, char* nome)
{
    clock_t inicio_t, fim_t;
    double t;
    FILE *arquivo;
    char linha[LINESIZE], *token, nomeArquivo[TAM_NOME_ARQUIVO];
    int i;

    sprintf(nomeArquivo, "%s.txt", nome);

    arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo...");
        exit (1);
    }

    inicio_t = clock();
    i = 0;
    while(fgets(linha, sizeof(linha), arquivo))
    {
        token = strtok(linha, ",");
        strcpy(lista->A[i].nome, token);
        token = strtok(NULL, ",");
        lista->A[i].RG = atoi(token);
        i++;
        lista->nElem++;
    }
    fclose(arquivo);
    fim_t = clock();
    t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
    printf("A abertura de arquivo para a lista sequencial levou: %f\n\n", t);
}

void exibirLista(ListaSeq* lista)
{
    int i;

    printf("Lista Sequencial (%d):\n", lista->nElem);
    for(i=0; i<lista->nElem; i++)
    {
        printf("%s, %d\n", lista->A[i].nome, lista->A[i].RG);
    }
    printf("\n");
}

void inserirNoInicio(ListaSeq* lista, ListaEnc* listaE)
{
    clock_t inicio_t, fim_t;
    double t;
    char nome[MAX_NOME];
    int j;
    int RG, C = 0, M = 0, N;

    getchar();
    printf("Digite o nome: ");
    if(fgets(nome, MAX_NOME, stdin))
    {
        nome[strcspn(nome, "\n")] = 0;
        printf("Insira o RG: ");
        scanf("%d", &RG);

        inicio_t = clock();
        for(j=lista->nElem; j>0; j--)
        {
            strcpy(lista->A[j].nome, lista->A[j-1].nome);
            lista->A[j].RG = lista->A[j-1].RG;
            M+=2;
        }
        strcpy(lista->A[0].nome, nome);
        lista->A[0].RG = RG;
        lista->nElem++;
        N = 1;
        M+=4;
        fim_t = clock();
        t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;

        system("cls");
        printf("Informacoes sobre a lista sequencial:\n\n");
        imprimeApresentacao(nome, RG, t, C, M, N);
        inserirNoInicioEnc(listaE, nome, RG);
    }
}

void inserirNoFim(ListaSeq* lista, ListaEnc* listaE)
{
    clock_t inicio_t, fim_t;
    double t;
    char nome[MAX_NOME];
    int j;
    int RG, C = 0, M = 0, N;

    getchar();
    printf("Digite o nome: ");
    if(fgets(nome, MAX_NOME, stdin))
    {
        nome[strcspn(nome, "\n")] = 0;
        printf("Insira o RG: ");
        scanf("%d", &RG);

        inicio_t = clock();
        strcpy(lista->A[lista->nElem].nome, nome);
        lista->A[lista->nElem].RG = RG;
        lista->nElem++;
        N = lista->nElem;
        M+=4;
        fim_t = clock();
        t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;

        system("cls");
        printf("Informacoes sobre a lista sequencial:\n\n");
        imprimeApresentacao(nome, RG, t, C, M, N);
        inserirNoFimEnc(listaE, nome, RG);
    }
}

void inserirNoPosicaoN(ListaSeq* lista, ListaEnc* listaE)
{
    clock_t inicio_t, fim_t;
    double t;
    char nome[MAX_NOME];
    int i, j;
    int RG, C = 0, M = 0, N;
    int ehPossivel = 1;

    getchar();
    printf("Digite o nome: ");
    if(fgets(nome, MAX_NOME, stdin))
    {
        nome[strcspn(nome, "\n")] = 0;
        printf("Insira o RG: ");
        scanf("%d", &RG);
        printf("Insira a posicao que deseja colocar o elemento: ");
        scanf("%d", &i);

        inicio_t = clock();
        if(lista->nElem == MAX || i<0 || i>lista->nElem)
        {
            ehPossivel = 0;
            printf("Nao foi possivel colocar o elemento nessa posicao...\n");
            system("pause");
        }
        if(ehPossivel == 1)
        {
            N = i;
            i--;
            for(j=lista->nElem; j>i; j--)
            {
                strcpy(lista->A[j].nome, lista->A[j-1].nome);
                lista->A[j].RG = lista->A[j-1].RG;
                M+=2;
            }
            strcpy(lista->A[i].nome, nome);
            lista->A[i].RG = RG;
            lista->nElem++;
            C+=2;
            M+=5;
            fim_t = clock();
            t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;

            system("cls");
            printf("Informacoes sobre a lista sequencial:\n\n");
            imprimeApresentacao(nome, RG, t, C, M, N);
            inserirNoPosicaoNEnc(listaE, nome, RG, i);
        }
    }
}

void excluirNoInicio(ListaSeq* lista, ListaEnc* listaE)
{
    clock_t inicio_t, fim_t;
    double t;
    char nome[MAX_NOME];
    int j;
    int RG, C = 0, M = 0, N;

    inicio_t = clock();
    strcpy(nome, lista->A[0].nome);
    RG = lista->A[0].RG;
    M+=2;
    if(lista->nElem>0)
    {
        for(j=0; j<lista->nElem; j++)
        {
            strcpy(lista->A[j].nome, lista->A[j+1].nome);
            lista->A[j].RG = lista->A[j+1].RG;
            M+=2;
        }
        lista->nElem--;
        C++;
        N = 1;
        M+=2;
        fim_t = clock();
        t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;

        system("cls");
        printf("Informacoes sobre a lista sequencial:\n\n");
        imprimeApresentacao(nome, RG, t, C, M, N);
        excluirNoInicioEnc(listaE);
    }
    else
    {
        printf("Nao eh possivel remover o elemento, pois a lista esta vazia...\n");
        system("pause");
    }
}

void excluirNoFim(ListaSeq* lista, ListaEnc* listaE)
{
    clock_t inicio_t, fim_t;
    double t;
    char nome[MAX_NOME];
    int RG, C = 0, M = 0, N;

    inicio_t = clock();
    if(lista->nElem>0)
    {
        N = lista->nElem;
        lista->nElem--;
        strcpy(nome, lista->A[lista->nElem].nome);
        RG = lista->A[lista->nElem].RG;
        M+=4;
        C++;
        fim_t = clock();
        t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;

        system("cls");
        printf("Informacoes sobre a lista sequencial:\n\n");
        imprimeApresentacao(nome, RG, t, C, M, N);
        excluirNoFimEnc(listaE);
    }
    else
    {
        printf("Nao eh possivel remover o elemento, pois a lista esta vazia...\n");
        system("pause");
    }
}

void excluirNoPosicaoN(ListaSeq* lista, ListaEnc* listaE)
{
    clock_t inicio_t, fim_t;
    double t;
    char nome[MAX_NOME];
    int i, j;
    int RG, C = 0, M = 0, N;
    int ehPossivel = 1;

    printf("Insira a posicao do elemento que deseja excluir: ");
    scanf("%d", &i);

    inicio_t = clock();
    if(lista->nElem == MAX || i<0 || i>lista->nElem)
    {
        ehPossivel = 0;
        printf("Nao foi possivel excluir o elemento dessa posicao...\n");
        system("pause");
    }
    C++;

    if(ehPossivel == 1)
    {
        N = i;
        i--;
        strcpy(nome, lista->A[i].nome);
        RG = lista->A[i].RG;
        for(j=i; j<lista->nElem; j++)
        {
            strcpy(lista->A[j].nome, lista->A[j+1].nome);
            lista->A[j].RG = lista->A[j+1].RG;
            M+=2;
        }
        lista->nElem--;
        C++;
        M+=5;
        fim_t = clock();
        t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;

        system("cls");
        printf("Informacoes sobre a lista sequencial:\n\n");
        imprimeApresentacao(nome, RG, t, C, M, N);
        excluirNoPosicaoNEnc(listaE, i);
    }
}

void buscaSequencial(ListaSeq* lista, ListaEnc* listaE)
{
    clock_t inicio_t, fim_t;
    double t;
    char nome[MAX_NOME];
    int RG, i = 0;
    int achouPosicao = 0;
    int C = 0, M = 0, N = -1;

    printf("Digite o RG para encontrar a posicao do elemento: ");
    scanf("%d", &RG);
    inicio_t = clock();
    while(i < lista->nElem && achouPosicao == 0)
    {
        if(RG == lista->A[i].RG)
        {
            achouPosicao = 1;
            N = i+1;
            strcpy(nome, lista->A[i].nome);
            M+=3;
            C++;
        }
        if(achouPosicao == 0)
        {
            i++;
            M++;
            C++;
        }
    }
    if(achouPosicao == 0)
        printf("Nao ha nome com o RG: %d\n", RG);
    C++;

    fim_t = clock();
    t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
    system("cls");
    printf("Informacoes sobre a lista sequencial:\n\n");
    imprimeApresentacao(nome, RG, t, C, M, N);
    buscaSequencialEnc(listaE, RG);
}

void salvarLista(ListaSeq* lista, char* nome)
{
    FILE *arquivo;
    int teste, i;
    char numero[10], linha[LINESIZE], nomeArquivo[TAM_NOME_ARQUIVO];

    sprintf(nomeArquivo, "%s.txt", nome);
    arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL)
    {
        printf("Erro ao tentar abrir o arquivo...\n");
        exit(1);
    }
    for(i=0; i<lista->nElem; i++)
    {
        sprintf(linha, "%s, %d\n", lista->A[i].nome, lista->A[i].RG);

        teste = fputs(linha, arquivo);

        if(teste == EOF)
            printf("Erro ao tentar gravar os dados...\n");
    }
    fclose(arquivo);
}

void imprimeApresentacao(char* nome, int RG, double tempo, int C, int M, int N)
{
    printf("O elemento com as seguintes caracteristicas foi selecionado:\n");
    printf("Nome: %s\n", nome);
    printf("RG: %d\n", RG);
    printf("Posicao (N): %d\n", N);
    printf("O tempo de execucao foi %f\n", tempo);
    printf("Houve %d comparacoes (C) e %d movimentacoes (M)\n", C, M);
    system("pause");
}

void inicializarListaEnc(ListaEnc* listaE)
{
    listaE->inicio = NULL;
}

int tamanhoListaEnc(ListaEnc* listaE)
{
    ElementoEnc* end;
    int tam = 0;

    end = listaE->inicio;
    while(end != NULL)
    {
        tam++;
        end = end->prox;
    }
    return tam;
}

void exibirListaEnc(ListaEnc* listaE)
{
    ElementoEnc* end;
    int tam;

    end = listaE->inicio;
    tam = tamanhoListaEnc(listaE);
    printf("Lista Encadeada (%d):\n", tam);
    while(end != NULL)
    {
        printf("%s, %d\n", end->B.nome, end->B.RG);
        end = end->prox;
    }
    printf("\n");
}

void lerArquivoEnc(ListaEnc* listaEnc, char* nome)
{
    clock_t inicio_t, fim_t;
    double t;
    FILE *arquivo;
    char linha[LINESIZE], *token, nomeArquivo[TAM_NOME_ARQUIVO];
    ElementoEnc* i;
    ElementoEnc* ant;
    int ehPrimeiro = 1;

    sprintf(nomeArquivo, "%s.txt", nome);

    arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo...");
        exit (1);
    }

    inicio_t = clock();
    while(fgets(linha, sizeof(linha), arquivo))
    {
        if(ehPrimeiro == 1)
        {
            ant = (ElementoEnc*) malloc (sizeof(ElementoEnc));
            token = strtok(linha, ",");
            strcpy(ant->B.nome, token);
            token = strtok(NULL, ",");
            ant->B.RG = atoi(token);
            ant->prox = listaEnc->inicio;
            listaEnc->inicio = ant;
            ehPrimeiro = 0;
        }
        else
        {
            i = (ElementoEnc*) malloc (sizeof(ElementoEnc));
            token = strtok(linha, ",");
            strcpy(i->B.nome, token);
            token = strtok(NULL, ",");
            i->B.RG = atoi(token);
            i->prox = ant->prox;
            ant->prox = i;
            ant = i;
        }
    }
    fclose(arquivo);
    fim_t = clock();
    t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
    printf("A abertura de arquivo para a lista encadeada levou: %f\n\n", t);
}

void buscaSequencialEnc(ListaEnc* listaE, int RG)
{
    clock_t inicio_t, fim_t;
    double t;
    char nome[MAX_NOME];
    int i = 0;
    int achouPosicao = 0;
    int C = 0, M = 0, N = -1;
    ElementoEnc* pos;

    inicio_t = clock();
    pos = listaE->inicio;
    M++;
    while(pos != NULL)
    {
        if(pos->B.RG == RG)
        {
            achouPosicao = 1;
            N = i+1;
            strcpy(nome, pos->B.nome);
            M+=3;
        }
        pos = pos->prox;
        M++;
        i++;
        C++;
    }
    fim_t = clock();
    t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
    system("cls");
    printf("Informacoes sobre a lista encadeada:\n\n");
    imprimeApresentacao(nome, RG, t, C, M, N);
}

void inserirNoInicioEnc(ListaEnc* listaEnc, char* nome, int RG)
{
    ElementoEnc* i;
    clock_t inicio_t, fim_t;
    double t;
    int C = 0, M = 0, N;

    inicio_t = clock();
    i = (ElementoEnc*) malloc(sizeof(ElementoEnc));
    strcpy(i->B.nome, nome);
    i->B.RG = RG;
    i->prox = listaEnc->inicio;
    listaEnc->inicio = i;
    N=1;
    M+=6;

    fim_t = clock();
    t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
    system("cls");
    printf("Informacoes sobre a lista encadeada:\n\n");
    imprimeApresentacao(nome, RG, t, C, M, N);
}

void funcaoAux(ListaEnc* listaEnc, ElementoEnc** ant, int* M, int* N)
{
    *ant = NULL;
    ElementoEnc* atual = listaEnc->inicio;
    (*M)+=2;
    while((atual!=NULL))
    {
        *ant = atual;
        atual = atual->prox;
        (*M)+=2;
        (*N)++;
    }
}

void funcaoAux2(ListaEnc* listaEnc, ElementoEnc** ant, int* M, int* N)
{
    *ant = NULL;
    int pos = 0;
    ElementoEnc* atual = listaEnc->inicio;
    (*M)+=3;
    while((atual!=NULL && pos < (*N)))
    {
        *ant = atual;
        atual = atual->prox;
        (*M)+=3;
        pos++;
    }
}

void funcaoAux3(ListaEnc* listaEnc, ElementoEnc** ant, ElementoEnc**atual, int* M, int* N)
{
    *ant = NULL;
    *atual = listaEnc->inicio;
    (*M)+=2;
    while(((*atual)->prox)!=NULL)
    {
        *ant = *atual;
        *atual = (*atual)->prox;
        (*M)+=3;
        (*N)++;
    }
}

void funcaoAux4(ListaEnc* listaEnc, ElementoEnc** ant, ElementoEnc**atual, int* M, int* N, int pos)
{
    int j;
    *ant = NULL;
    *atual = listaEnc->inicio;
    (*M)+=2;
    while(((*atual)->prox)!=NULL && pos!=j)
    {
        *ant = *atual;
        *atual = (*atual)->prox;
        (*M)+=3;
        j++;
    }
}

void inserirNoFimEnc(ListaEnc* listaEnc, char* nome, int RG)
{
    ElementoEnc* i;
    ElementoEnc* ant;

    clock_t inicio_t, fim_t;
    double t;
    int C = 0, M = 0, N = 1;

    inicio_t = clock();
    ant = (ElementoEnc*) malloc(sizeof(ElementoEnc));
    funcaoAux(listaEnc, &ant, &M, &N);
    i = (ElementoEnc*) malloc(sizeof(ElementoEnc));
    strcpy(i->B.nome, nome);
    i->B.RG = RG;
    i->prox = ant->prox;
    ant->prox = i;
    M+=6;

    fim_t = clock();
    t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
    system("cls");
    printf("Informacoes sobre a lista encadeada:\n\n");
    imprimeApresentacao(nome, RG, t, C, M, N);
}

void inserirNoPosicaoNEnc(ListaEnc* listaEnc, char* nome, int RG, int pos)
{
    ElementoEnc* i;
    ElementoEnc* ant;
    clock_t inicio_t, fim_t;
    double t;
    int C = 0, M = 0, N = pos+1;

    inicio_t = clock();
    ant = (ElementoEnc*) malloc(sizeof(ElementoEnc));
    funcaoAux2(listaEnc, &ant, &M, &pos);
    i = (ElementoEnc*) malloc(sizeof(ElementoEnc));
    strcpy(i->B.nome, nome);
    i->B.RG = RG;
    M+=2;
    if(ant == NULL)
    {
        i->prox = listaEnc->inicio;
        listaEnc->inicio = i;
        M+=2;
        C++;
    }
    else
    {
        i->prox = ant->prox;
        ant->prox = i;
        M+=2;
        C++;
    }

    fim_t = clock();
    t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
    system("cls");
    printf("Informacoes sobre a lista encadeada:\n\n");
    imprimeApresentacao(nome, RG, t, C, M, N);
}

int listaVazia(ListaEnc* listaEnc)
{
    if(listaEnc == NULL)
        return 1;
    return 0;
}

void excluirNoInicioEnc(ListaEnc* listaEnc)
{
    ElementoEnc* i;
    clock_t inicio_t, fim_t;
    double t;
    char nome[MAX_NOME];
    int RG, C = 0, M = 0, N = 1;

    inicio_t = clock();
    if(listaVazia(listaEnc) == 0)
    {
        i = (ElementoEnc*) malloc(sizeof(ElementoEnc));
        i = listaEnc->inicio;
        strcpy(nome, i->B.nome);
        RG = i->B.RG;
        listaEnc->inicio = i->prox;
        free(i);
        M+=4;
        C++;
    }
    fim_t = clock();
    t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
    system("cls");
    printf("Informacoes sobre a lista encadeada:\n\n");
    imprimeApresentacao(nome, RG, t, C, M, N);
}

void excluirNoFimEnc(ListaEnc* listaEnc)
{
    ElementoEnc* i;
    ElementoEnc* ant;
    clock_t inicio_t, fim_t;
    double t;
    char nome[MAX_NOME];
    int RG, C = 0, M = 0, N = 1;

    inicio_t = clock();
    if(listaVazia(listaEnc) == 0)
    {
        ant = (ElementoEnc*) malloc(sizeof(ElementoEnc));
        i = (ElementoEnc*) malloc(sizeof(ElementoEnc));
        funcaoAux3(listaEnc, &ant, &i, &M, &N);
        if(ant!=NULL)
        {
            strcpy(nome, i->B.nome);
            RG = i->B.RG;
            ant->prox = i->prox;
            free(i);
            M+=3;
            C++;
        }
        else
        {
            strcpy(nome, i->B.nome);
            RG = i->B.RG;
            listaEnc->inicio = i->prox;
            free(i);
            free(ant);
            M+=3;
            C++;
        }
    }
    C++;
    fim_t = clock();
    t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
    system("cls");
    printf("Informacoes sobre a lista encadeada:\n\n");
    imprimeApresentacao(nome, RG, t, C, M, N);
}

void excluirNoPosicaoNEnc(ListaEnc* listaEnc, int pos)
{
    ElementoEnc* i;
    ElementoEnc* ant;
    clock_t inicio_t, fim_t;
    double t;
    char nome[MAX_NOME];
    int RG, C = 0, M = 0, N = pos+1;

    inicio_t = clock();
    if(listaVazia(listaEnc) == 0)
    {
        ant = (ElementoEnc*) malloc(sizeof(ElementoEnc));
        i = (ElementoEnc*) malloc(sizeof(ElementoEnc));
        funcaoAux4(listaEnc, &ant, &i, &M, &N, pos);
        if(ant!=NULL)
        {
            strcpy(nome, i->B.nome);
            RG = i->B.RG;
            ant->prox = i->prox;
            free(i);
            M+=3;
            C++;
        }
        else
        {
            strcpy(nome, i->B.nome);
            RG = i->B.RG;
            listaEnc->inicio = i->prox;
            free(i);
            free(ant);
            M+=3;
            C++;
        }
    }
    C++;
    fim_t = clock();
    t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
    system("cls");
    printf("Informacoes sobre a lista encadeada:\n\n");
    imprimeApresentacao(nome, RG, t, C, M, N);
}

void salvarListaEnc(ListaEnc* listaEnc, char* nome)
{
    FILE *arquivo;
    int teste;
    char numero[10], linha[LINESIZE], nomeArquivo[TAM_NOME_ARQUIVO];
    ElementoEnc* end;

    sprintf(nomeArquivo, "%s.txt", nome);
    arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL)
    {
        printf("Erro ao tentar abrir o arquivo...\n");
        exit(1);
    }

    end = listaEnc->inicio;
    while(end != NULL)
    {
        sprintf(linha, "%s, %d\n", end->B.nome, end->B.RG);

        teste = fputs(linha, arquivo);

        if(teste == EOF)
            printf("Erro ao tentar gravar os dados...\n");

        end = end->prox;
    }
    fclose(arquivo);
}

void reinicializarListaEnc(ListaEnc* listaEnc)
{
    ElementoEnc* end;
    ElementoEnc* apagar;

    end = listaEnc->inicio;
    while(end != NULL)
    {
        apagar = end;
        end = end->prox;
        free(apagar);
    }
    listaEnc->inicio = NULL;
}
