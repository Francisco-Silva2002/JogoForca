#include <stdio.h>
#include <stdlib.h>

typedef struct word S;

int c;
char linha[25];
char* pontC;

char palavra[25];
char dica[25];

typedef struct word{
    char chave[25];
    char dica[25];
    int usada;
    S* proximo;
};

S* cria(){
    return NULL;
}

S* inserePalavra(S* l, char chave[25], char dica[25]){
    S* novo;
    novo = (S*) malloc(sizeof(S));
    strcpy(novo->chave, chave);
    strcpy(novo->dica, dica);
    novo->usada = 0;
    novo->proximo = l;
    l = novo;
    return l;
}

void escreve(S* l){
    S* p;
    for(p = l;p!=NULL;p=p->proximo){
        printf("%i) %s - %s\n", p->usada,p->chave,p->dica);
    }
}

int estaVazia(S* l){
    int cont = 0;
    for(S* k=l;k!=NULL;k=k->proximo){
        if(k->usada == 0){
            cont++;
        }
    }
    return cont;
}

void libera (S* l)
{
    S* p = l;
    while (p != NULL) {
        S* t = p->proximo;
        free(p);
        p = t;
    }
}

S* carregaJogo(FILE * arquivo, S* lista){
    while((c = fgetc(arquivo)) != EOF){
        pontC = &palavra;
        int p = 0;
        fscanf(arquivo, "%s", &linha);
        for(int k=0;k<strlen(linha); k++){
            if(linha[k] == '\n'){
                pontC[p] = '\0';
                continue;
            }

            if(linha[k] == ';'){
                pontC[p] = '\0';
                pontC = &dica;
                p=0;
                continue;
            }
            else{
                pontC[p] = linha[k];
            }

            p++;
        }
        lista = inserePalavra(lista, palavra, dica);
    }
    return lista;
}

S* encontra(S* lista, char word[25]){
    for(S* p=lista; p!=NULL;p=p->proximo){
        if(strcmp(p->chave,word) == 0){
            p->usada = 1;
        }
    }

    if(estaVazia(lista) == 0){
        libera(lista);
        lista = NULL;
    }

    return lista;
}

int main(int argc, char* args[])
{
    int op = 1;
    char palpite[25];
    FILE* arquivo;
    S* listaPalavras;

    char nomeArquivo[255];
    if(argc>1){
        strcpy(nomeArquivo, args[1]);
    }
    else{
        strcpy(nomeArquivo, "palavras.csv");
    }
    arquivo = fopen(nomeArquivo, "rt");

    listaPalavras = cria();
    listaPalavras = carregaJogo(arquivo, listaPalavras);
    do{
        system("cls");
        escreve(listaPalavras);
        scanf("%s", &palpite);
        if(strcmp(palpite, "f") == 0)
            break;
        listaPalavras = encontra(listaPalavras, palpite);
        if(listaPalavras == NULL){
            printf("Nao ha mais palavras!");
            break;
        }
    }while(op);

    return 0;
}
