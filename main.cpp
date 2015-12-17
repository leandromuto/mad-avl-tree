
//
//folha *criaFolha(folha *ini, int num, folha *esq, folha *dir) { // esquerda e direita podem ser null
//	folha *nova = (folha *) malloc(sizeof(folha));
//	
//	if(!nova) {
//		printf("Falta de memória ao criar índice.\n");
//		exit(0);
//	}
//	
//	nova->num = num;
//	nova->esq = esq;
//	nova->dir = dir;
//	nova->balanceamento = altura(esq) - altura(dir);
//	
//	nova->tupla = (tupla *) malloc(sizeof(cel));
//	nova->tupla->prox = nullptr;
//	
//	printf("\n\n\nÍndice %d inserido com sucesso!\n", num);
//	
//	return nova;
//} // OK
//
//
//



































/*
 *  Árvore AVL
 *
 *  Fator de balanceamento = hdir - hesq
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <term.h>

typedef struct cel {
	char nome[100];
	struct cel *prox;
} tupla; // OK

typedef struct no {
	int num;
	int balanceamento;   /* balanceamento = hdir - hesq */
	int altura;
	int countNomes = 0;
	struct no *esq = nullptr;
	struct no *dir = nullptr;
	tupla *tupla;
} folha; // OK

folha *buscaFolha(folha *ini, int numFolha) {
	folha *aux = ini;
	
	if(ini == nullptr) {
		printf("\n\n\nRaiz não encontrada.\n\n\n");
		return nullptr;
	}
	
	while(aux != nullptr) {
		if(numFolha == aux->num) {
			return aux;
		}
		else if(numFolha < aux->num) {
			aux = aux->esq;
		}
		else if(numFolha > aux->num) {
			aux = aux->dir;
		}
	}
	
	printf("Índice %d não encontrada.\n", numFolha);
	
	return aux;
} // OK

void imprimeNomes(folha *ini, int numFolha) {
	folha *aux = ini;
	folha *f = buscaFolha(aux, numFolha);
	tupla *auxTu = f->tupla;
	
	if(auxTu->prox == nullptr) {
		printf("Nenhum nome na lista da folha %d.\n", numFolha);
		return;
	}
	
	printf("\n\n|---Índice %d---|\n", numFolha);
	
	auxTu = auxTu->prox;
	
	while(auxTu != nullptr) {
		printf("| Nome: %s\n", auxTu->nome);
		auxTu = auxTu->prox;
	}
	
	printf("|---Total---%d -|\n\n", f->countNomes);
} // OK

void ordenaNome(tupla *t) {
	tupla *aux;
	
	if(t->prox == nullptr) {
		printf("Lista vazia.");
		return;
	}
	
	aux = t->prox;
	while(aux->prox != nullptr) {
		int cmp = strcmp(aux->nome, aux->prox->nome);
		
		if(cmp > 0) {
			char cp[100];
			strcpy(cp, aux->nome);
			strcpy(aux->nome, aux->prox->nome);
			strcpy(aux->prox->nome, cp);
			
			aux = t->prox;
		}
		
		aux = aux->prox;
	}
} // OK

tupla *insereLista(folha *ini, int numFolha, char nome[]) { // insere nome na lista encadeada da folha que inserir como parametro
	
	folha *folhaExiste = buscaFolha(ini, numFolha);
	
	if(folhaExiste == nullptr) { // verificando se a folha existe, se não sai fora
		return nullptr;
	}
	
	tupla *t, *aux;
	t = (tupla *) malloc(sizeof(tupla)); // criando nova tupla
	strcpy(t->nome, nome); // copia nome do parâmetro pra tupla->nome
	
	aux = folhaExiste->tupla; // aux recebe cabeça das tuplas da struct folha
	
	t->prox = folhaExiste->tupla->prox; // aponta pra qual a cabeça tava apontando
	aux->prox = t; // cabeça aponta pra nova
	printf("Nome \"%s\" inserido no índice %d.\n\n", nome, numFolha);
	
	folhaExiste->countNomes++;
	
	ordenaNome(folhaExiste->tupla);
	
	return t;
} // OK

folha *novoNo(int num) {
	folha *novo = (folha*) malloc(sizeof(folha));
	novo->num = num;
	novo->esq = nullptr;
	novo->dir = nullptr;
	novo->altura = 1;
	novo->tupla = (tupla *) malloc(sizeof(tupla));
	novo->tupla->prox = nullptr;
	
	printf("Nó inserido com sucesso!\n\n\n");
	return novo;
} // OK

int altura(folha *n) {
	if (n == NULL) {
		return 0;
	}
	return n->altura;
} // OK

folha *rotacionarDireita(folha *y) {
	folha *x = y->esq;
	folha *T2 = x->dir;
 
	// faz rotação
	x->dir = y;
	y->esq = T2;
 
	// atualiza altura
	y->altura = std::max(altura(y->esq), altura(y->dir))+1;
	x->altura = std::max(altura(x->esq), altura(x->dir))+1;
 
	// retorna nova raiz
	return x;
} // OK

folha *rotacionarEsquerda(folha *x) {
	folha *y = x->dir;
	folha *T2 = y->esq;
 
	// faz rotação
	y->esq = x;
	x->dir = T2;
 
	// altualiza altura
	x->altura = std::max(altura(x->esq), altura(x->dir))+1;
	y->altura = std::max(altura(y->esq), altura(y->dir))+1;
 
	// retorna nova raiz
	return y;
} // OK

// balanceamento do nó n
int balanceamento(folha *n) {
	if (n == NULL)
		return 0;
	return altura(n->esq) - altura(n->dir);
} // OK

folha *insereNo(folha *fol, int num) {
	if(fol == nullptr) {
		return novoNo(num);
	}
	
	if(num < fol->num) {
		fol->esq = insereNo(fol->esq, num);
	}
	else {
		fol->dir = insereNo(fol->dir, num);
	}
	
	fol->altura = std::max(altura(fol->esq), altura(fol->dir)) + 1; // atualiza a altura do anterior
	
	int bal = balanceamento(fol); // pega o valor do balanceamento do anterior para ver para qual lado rotacionar
	
	// Rotação dupla a esquerda
	if (bal > 1 && num < fol->esq->num) {
		printf("Rotação dupla a esquerda.\n");
		return rotacionarDireita(fol);
	}
 
	// Rptação dupla a direita
	if (bal < -1 && num > fol->dir->num) {
		printf("Rotação dupla a direita.\n");
		return rotacionarEsquerda(fol);
	}
 
	// Rotação a esquerda e depois direita
	if (bal > 1 && num > fol->esq->num)
	{
		fol->esq = rotacionarEsquerda(fol->esq);
		printf("Rotação a esquerda e depois a direita.\n");
		return rotacionarDireita(fol);
	}
 
	// Rotação a esquerda e depois a direita
	if (bal < -1 && num < fol->dir->num)
	{
		fol->dir = rotacionarDireita(fol->dir);
		printf("Rotação a direita e depois a esquerda.\n");
		return rotacionarEsquerda(fol);
	}
	
	return fol;
} // OK

// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
void ordemArvore(folha *root) {
	if(root != nullptr) {
		printf("%d ", root->num);
		ordemArvore(root->esq);
		ordemArvore(root->dir);
	}
}

int main() {
	
	int opc = 9;
	folha *root = nullptr;
	
	while(opc != 0) {
		printf("\n----------- Menu -------------------\n");
		printf("| 1 - Inserir nó ------------------|\n");
		printf("| 2 - Inserir nome ----------------|\n");
		printf("| 3 - Exibir nomes ----------------|\n");
		printf("| 4 - Exibir árvore em ordem ------|\n");
		printf("| 0 - Sair ------------------------|\n");
		printf("------------------------------------\n");
		
		printf("Escolha uma opção: ");
		scanf("%d", &opc);
		
		switch (opc) {
			case 1: {
				int ind;
				printf("Índice do nó a ser inserido: ");
				scanf("%d", &ind);
				
				root = insereNo(root, ind);
				
				break;
			}
			case 2: {
				int ind;
				char nome[30];
				printf("Você escolheu inserir um nome em um índice.\n");
				printf("Em qual índice deseja colocar o nome?\n");
				printf("Índice: ");
				scanf("%d", &ind);
				
				folha *aux = buscaFolha(root, ind);
				
				while(aux == nullptr) {
					printf("\n\n\nTente novamente.\n");
					printf("Em qual índice deseja colocar o nome?\n");
					printf("Índice: ");
					scanf("%d", &ind);
					
					aux = buscaFolha(root, ind);
				}
				
				printf("Nome que deseja colocar: ");
				scanf("%s", &nome);
				
				insereLista(root, ind, nome);
				imprimeNomes(root, ind);
				
				break;
			}
			case 3: {
				int ind;
				printf("\n\n\nVocê escolheu imprimir os nomes de um índice.\n");
				printf("De qual índice deseja imprimir?\n");
				printf("Índice: ");
				scanf("%d", &ind);
				
				folha *f = buscaFolha(root, ind);
				
				if(f == nullptr) {
					//					printf("\n\n\nVocê escolheu imprimir os nomes de um índice.\n");
					//					printf("De qual índice deseja imprimir?\n");
					//					printf("Índice: ");
					//					scanf("%d", &ind);
					//
					//					f = buscaFolha(root, ind);
					return 0;
				}
				
				imprimeNomes(root, ind);
				break;
			}
			case 4: {
				ordemArvore(root);
				break;
			}
			case 5: {
				break;
			}
			case 0: {
				exit(0);
				break;
			}
			default: {
				printf("Opção inválida. Tente novamente.\n\n\n");
			}
		}
	}
	
}














