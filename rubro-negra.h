#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define TOTAL_NO 10000 // número máximo de nós
#define VALOR_NO 100000 // valor máximo de nós
#define TRUE 1
#define FALSE 0

typedef struct no *No;

typedef struct no{
	int valor;
	char cor;
	No dir, esq, pai;
}no;

struct rubronegra{
	no *raiz;
};

typedef struct rubronegra *RubroNegra;

RubroNegra criarArvore();
No criarNo(int valor);
No sucessor(No x);
No buscar(No x, int valor);
void teste();
void rotacaoEsquerda(RubroNegra arvore, No x);
void rotacaoDireita(RubroNegra arvore, No x);
void consertaInsercao(RubroNegra arvore, No z);
void moverPai(RubroNegra arvore, No u, No v);
void consertaRemocao(RubroNegra arvore, No x);
void removerAux(RubroNegra arvore, No z);
void imprimeArvore(No x);
void preOrdem(RubroNegra arvore);
void liberaMem(RubroNegra pt);
void liberaNos(No no);
int inserir(RubroNegra arvore, int valor);
int remover(RubroNegra arvore, int valor);
int gerarAleatorio();
int contaNos(No raiz);
int verificaRN(No raiz);
int verificaNo(No pt);

