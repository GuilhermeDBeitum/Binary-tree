#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int conteudo;
    struct no *esquerda, *direita;
} No;

typedef struct
{
    No *raiz;
    int tam;
} ArvB;

void inserirDireita(No *no, int valor);

void inserirEsquerda(No *no, int valor)
{
    if (no->esquerda == NULL)
    {
        No *novo = (No *)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->esquerda = novo;
    }
    else
    {
        if (valor < no->esquerda->conteudo)
            inserirEsquerda(no->esquerda, valor);
        if (valor > no->esquerda->conteudo)
            inserirDireita(no->esquerda, valor);
    }
}

void inserirDireita(No *no, int valor)
{
    if (no->direita == NULL)
    {
        No *novo = (No *)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->direita = novo;
    }
    else
    {
        if (valor > no->direita->conteudo)
            inserirDireita(no->direita, valor);
        if (valor < no->direita->conteudo)
            inserirEsquerda(no->direita, valor);
    }
}

void inserir(ArvB *arv, int valor)
{
    if (arv->raiz == NULL)
    {
        No *novo = (No *)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        arv->raiz = novo;
    }
    else
    {
        if (valor < arv->raiz->conteudo)
            inserirEsquerda(arv->raiz, valor);
        if (valor > arv->raiz->conteudo)
            inserirDireita(arv->raiz, valor);
    }
}

No *inserirNovaVersao(No *raiz, int valor)
{
    if (raiz == NULL)
    {
        No *novo = (No *)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    else
    {
        if (valor < raiz->conteudo)
            raiz->esquerda = inserirNovaVersao(raiz->esquerda, valor);
        if (valor > raiz->conteudo)
            raiz->direita = inserirNovaVersao(raiz->direita, valor);
        return raiz;
    }
}

void imprimir(No *raiz)
{
    if (raiz != NULL)
    {
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
}

No *remover(No *raiz, int chave)
{
    if (raiz == NULL)
    {
        printf("Valor nao encontrado!\n");
        return NULL;
    }
    else
    {
        if (raiz->conteudo == chave)
        {
            // remove nós folhas (nós sem filhos)
            if (raiz->esquerda == NULL && raiz->direita == NULL)
            {
                free(raiz);
                return NULL;
            }
            else
            {
                // remover nós que possuem apenas 1 filho
                if (raiz->esquerda == NULL || raiz->direita == NULL)
                {
                    No *aux;
                    if (raiz->esquerda != NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;
                    free(raiz);
                    return aux;
                }
                else
                {
                    No *aux = raiz->esquerda;
                    while (aux->direita != NULL)
                        aux = aux->direita;
                    raiz->conteudo = aux->conteudo;
                    aux->conteudo = chave;
                    raiz->esquerda = remover(raiz->esquerda, chave);
                    return raiz;
                }
            }
        }
        else
        {
            if (chave < raiz->conteudo)
                raiz->esquerda = remover(raiz->esquerda, chave);
            else
                raiz->direita = remover(raiz->direita, chave);
            return raiz;
        }
    }
}

int main()
{
    int op, valor;
    ArvB arv;
    arv.raiz = NULL;

    No *raiz = NULL;

    do
    {
        printf("\n1 - inserir\n2 - imprimir\n3 - Remover\n");
        scanf("%d", &op);

        switch (op)
        {

        case 1:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            raiz = inserirNovaVersao(raiz, valor);  
            break;
        case 2:
            printf("\nImpressao da arvore binaria:\n");
            imprimir(raiz);
            printf("\n");
            break;
        case 3:
            printf("Digite um valor a ser removido: ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;

        default:
            printf("\nOpcao invalida...\n");
        }
    } while (op != 0);
}