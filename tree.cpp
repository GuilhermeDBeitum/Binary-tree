#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int content;
    struct no *left, *right;
} No;

typedef struct
{
    No *source;
    int length;
} ArvB;

void insertRight(No *no, int value);

void insertRight(No *no, int value)
{
    if (no->left == NULL)
    {
        No *_new = (No *)malloc(sizeof(No));
        _new->content = value;
        _new->left = NULL;
        _new->right = NULL;
        no->left = _new;
    }
    else
    {
        if (value < no->left->content)
            insertLeft(no->left, value);
        if (value > no->left->content)
            insertRight(no->left, value);
    }
}

void insertRight(No *no, int value)
{
    if (no->right == NULL)
    {
        No *_new = (No *)malloc(sizeof(No));
        _new->content = value;
        _new->left = NULL;
        _new->right = NULL;
        no->right = _new;
    }
    else
    {
        if (value > no->right->content)
            insertRight(no->right, value);
        if (value < no->right->content)
            insertLeft(no->right, value);
    }
}

void inserir(ArvB *arv, int value)
{
    if (arv->source == NULL)
    {
        No *_new = (No *)malloc(sizeof(No));
        _new->content = value;
        _new->left = NULL;
        _new->right = NULL;
        arv->source = _new;
    }
    else
    {
        if (value < arv->source->content)
            insertLeft(arv->source, value);
        if (value > arv->source->content)
            insertRight(arv->source, value);
    }
}

No *inserirNovaVersao(No *source, int value)
{
    if (source == NULL)
    {
        No *_new = (No *)malloc(sizeof(No));
        _new->content = value;
        _new->left = NULL;
        _new->right = NULL;
        return _new;
    }
    else
    {
        if (value < source->content)
            source->left = inserirNovaVersao(source->left, value);
        if (value > source->content)
            source->right = inserirNovaVersao(source->right, value);
        return source;
    }
}

void printView(No *source)
{
    if (source != NULL)
    {
        printView(source->left);
        printf("%d ", source->content);
        printView(source->right);
    }
}

No *remover(No *source, int key)
{
    if (source == NULL)
    {
        printf("Valor nao encontrado!\n");
        return NULL;
    }
    else
    {
        if (source->content == key)
        {
            // remove nós folhas (nós sem filhos)
            if (source->left == NULL && source->right == NULL)
            {
                free(source);
                return NULL;
            }
            else
            {
                // remover nós que possuem apenas 1 filho
                if (source->left == NULL || source->right == NULL)
                {
                    No *aux;
                    if (source->left != NULL)
                        aux = source->left;
                    else
                        aux = source->right;
                    free(source);
                    return aux;
                }
                else
                {
                    No *aux = source->left;
                    while (aux->right != NULL)
                        aux = aux->right;
                    source->content = aux->content;
                    aux->content = key;
                    source->left = remover(source->left, key);
                    return source;
                }
            }
        }
        else
        {
            if (key < source->content)
                source->left = remover(source->left, key);
            else
                source->right = remover(source->right, key);
            return source;
        }
    }
}

int main()
{
    int op, value;
    ArvB arv;
    arv.source = NULL;

    No *source = NULL;

    do
    {
        printf("\n1 - inserir\n2 - printView\n3 - Remover\n");
        scanf("%d", &op);

        switch (op)
        {

        case 1:
            printf("Digite um valor: ");
            scanf("%d", &value);
            source = inserirNovaVersao(source, value);  
            break;
        case 2:
            printf("\nImpressao da arvore binaria:\n");
            printView(source);
            printf("\n");
            break;
        case 3:
            printf("Digite um value a ser removido: ");
            scanf("%d", &value);
            source = remover(source, value);
            break;

        default:
            printf("\nOpção invalida...\n");
        }
    } while (op != 0);
}