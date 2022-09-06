#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    int valor;
    int indice;
    struct no *proximo;
    struct no *anterior;
}No;

typedef struct{
    No *inicio;
    No *fim;
    int tam;
}Lista;

void criar_lista(Lista *lista){
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam = 0;
}

void inserir(Lista *lista, int num, int indice) {
    No *aux, *novo = (No *) malloc(sizeof(No));

    if(novo){
        novo->valor = num;
        novo->indice = indice;
        novo->proximo = NULL;

        if(lista->inicio == NULL) {
        	novo->anterior = NULL;
        	lista->inicio = novo;
        	lista->fim = novo;
		}
        else{
        	novo->anterior = lista->fim;
            lista->fim->proximo = novo;
            lista->fim = novo;
        }
        lista->tam++;
    }
}

void remover(Lista *lista, No *endereco_para_remover) {
    No *para_remover = NULL;

    if(lista){
    	para_remover = endereco_para_remover;
        if(lista->inicio == para_remover) {
        	lista->inicio = para_remover->proximo;
			lista->inicio->anterior = NULL;
		}
		
		else if(lista->fim == para_remover) {
			para_remover->anterior->proximo = NULL;
			lista->fim = para_remover->anterior;
		}
		
        else {
        	para_remover->anterior->proximo = para_remover->proximo;
        	para_remover->proximo->anterior = para_remover->anterior;
        }
    }
}

int main(void) {
	
	Lista tempos;
	criar_lista(&tempos);
	
	int n, i, len_texto, fase = 1;
	char texto[100000];
	
	scanf("%i",&n);
	
	int reacao[n], escrita[n], colocacao[n];
	
	for(i = 0; i < n; i++)
		scanf("%i %i",&reacao[i], &escrita[i]);
	
	scanf(" %[^\n]",texto);
	
	len_texto = strlen(texto);
	
	for(i = 0; i < n; i++) {
		inserir(&tempos, (reacao[i] + (escrita[i] * len_texto)), i);
    	colocacao[i] = 0;
	}
	
	i = 0;
	int len_tempos = n;
	while (len_tempos > 2) {
		No *tempos_i = tempos.inicio;
		No *tempos_i_mais_um = tempos_i->proximo;
	    while (i < len_tempos) {
	        if(tempos_i->valor > tempos_i_mais_um->valor) {
	            colocacao[tempos_i->indice] = fase;
	            remover(&tempos, tempos_i);
	            free(tempos_i);
	            
				if(tempos_i_mais_um->proximo) {
					tempos_i = tempos_i_mais_um->proximo;
	            	tempos_i_mais_um = tempos_i->proximo;	
				}
	        }
	        else {
	            colocacao[tempos_i_mais_um->indice] = fase;
	            remover(&tempos, tempos_i_mais_um);
	            free(tempos_i_mais_um);
	            
	            if(tempos_i->proximo) {
	            	tempos_i = tempos_i->proximo;
	            	tempos_i_mais_um = tempos_i->proximo;	
				}
	        }
	        i++;
	        len_tempos--;
	    }
	    fase++;
	    i = 0;
	}
	
	No *tempos_i = tempos.inicio;
	
	if (len_tempos == 1) {
		colocacao[tempos_i->indice] = fase;
		free(tempos.inicio);
	}
	else {
		No *tempos_i_mais_um = tempos_i->proximo;
	    if(tempos_i->valor > tempos_i_mais_um->valor) {
	        colocacao[tempos_i->indice] = fase;
	        colocacao[tempos_i_mais_um->indice] = fase + 1;
	    }
	    else {
	        colocacao[tempos_i_mais_um->indice] = fase;
	        colocacao[tempos_i->indice] = fase + 1;
	    }
	    free(tempos.inicio);
	    free(tempos.fim);
	}
	
	for(i = 0; i < n - 1; i++)
		printf("%i ",colocacao[i]);
	printf("%i\n",colocacao[i]);
	
	return 0;
}
