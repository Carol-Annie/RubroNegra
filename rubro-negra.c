#include "rubro-negra.h"

No externo = NULL;

void teste(){
    int n_arvore = 0;
    int n_no = 0;
    int val_aleatorio = 0;
    No valor_encontrado = NULL;
    RubroNegra arvore = criarArvore();

    // criação de 1000 árvores
    while(n_arvore < 1000){
        printf("Árvore: %d \n", n_arvore+1);
        printf("\tInserção: \n");
        arvore = criarArvore();
        n_no = 0;
        
        while(n_no < TOTAL_NO){
            val_aleatorio = gerarAleatorio();
            if(buscar(arvore->raiz, val_aleatorio)->valor == 0){
                inserir(arvore, val_aleatorio);
                n_no++;
            }            
        }
        preOrdem(arvore);

        // remoção de 1000 nós
        printf("\tRemoção: \n");
        while(n_no > (TOTAL_NO - 1000)){
            remover(arvore, arvore->raiz->valor);
            n_no--;
        }
        preOrdem(arvore);
        
        n_arvore++;
        liberaMem(arvore);
        arvore->raiz = externo;
    }
}

RubroNegra criarArvore() {
    if (externo == NULL) {
        externo = (No) malloc(sizeof(struct no));
        externo->cor = 'N';
        externo->dir = externo;
        externo->esq = externo;
        externo->pai = externo;
        externo->valor = 0;
    }
    RubroNegra nova = (RubroNegra) malloc(sizeof(struct rubronegra));
    nova->raiz = externo;
    return nova;
}

No criarNo(int valor) {
    No novo = (No) malloc(sizeof(struct no));
    novo->valor = valor;
    novo->cor = 'R';
    novo->dir = externo;
    novo->esq = externo;
    novo->pai = externo;
    return novo;
}

No sucessor(No x) {
    No y = x;
    while (y->esq != externo)
        y = y->esq;
    return y;
}

void rotacaoEsquerda(RubroNegra arvore, No x) {
    No y;
    y = x->dir;
    x->dir = y->esq;
    if (y->esq != externo){
        y->esq->pai = x;
    } 

    y->pai = x->pai;
    if (x->pai == externo) {
        arvore->raiz = y;
    }else if (x == x->pai->esq) {
        x->pai->esq = y;
    }else{
        x->pai->dir = y;
    }
    y->esq = x;
    x->pai = y;
}

void rotacaoDireita(RubroNegra arvore, No x) {
    No y;
    y = x->esq;
    x->esq = y->dir;
    if (y->dir != externo){ 
        y->dir->pai = x;
    }

    y->pai = x->pai;
    if (x->pai == externo){ 
        arvore->raiz = y;
    }else if (x == x->pai->dir){
        x->pai->dir = y;
    }
    else{
        x->pai->esq = y;
    }
    y->dir = x;
    x->pai = y;
}

void consertaInsercao(RubroNegra arvore, No z) {
	No y;
    while (z->pai->cor == 'R') {
        if (z->pai == z->pai->pai->esq) {
        	y = z->pai->pai->dir;
	        if (y->cor == 'R') {
                z->pai->cor = 'N';
                y->cor = 'N';
                z->pai->pai->cor = 'R';
                z = z->pai->pai;
            } else {
            	if (z == z->pai->dir) {
                    z = z->pai;
                    rotacaoEsquerda(arvore, z);
                }
                z->pai->cor = 'N';
                z->pai->pai->cor = 'R';
                rotacaoDireita(arvore, z->pai->pai);
            }
        } else {
            y = z->pai->pai->esq;
            if (y->cor == 'R') {
                z->pai->cor = 'N';
                y->cor = 'N';
                z->pai->pai->cor = 'R';
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    rotacaoDireita(arvore, z);
                }
                z->pai->cor = 'N';
                z->pai->pai->cor = 'R';
            	rotacaoEsquerda(arvore, z->pai->pai);
            }	
        }
    }
    arvore->raiz->cor = 'N';
}

int inserir(RubroNegra arvore, int valor) {
    No y, x, z;
    z = criarNo(valor);

    y = externo;
    x = arvore->raiz;
    
    while (x != externo) {
        y = x;
        if (z->valor == x->valor){
            return 1;
        } 
        if (z->valor < x->valor) {
            x = x->esq;
        }
        else{
             x = x->dir;
        }
    }
    
    z->pai = y;
    if (y == externo){ 
        arvore->raiz = z;
    }
    else if (z->valor < y->valor){ 
        y->esq = z;
    }
    else {
        y->dir = z;
    }
    
    z->esq = externo;
    z->dir = externo;
    z->cor = 'R';

    consertaInsercao(arvore, z);
    return 0;
}

void moverPai(RubroNegra arvore, No u, No v){
    if(u->pai == externo){
        arvore->raiz = v;
    }else if(u==u->pai->esq){ 
        u->pai->esq = v;
    }else{
        u->pai->dir = v;
    }
    v->pai = u->pai;
}

No buscar(No x, int valor) {
    if (x == externo || x->valor == valor){
        return x;
    } 
    if (valor < x->valor) {
        buscar(x->esq, valor);
    }
    else {
        buscar(x->dir, valor);
    }
    return x;
}

void consertaRemocao(RubroNegra arvore, No x){
    No w;
    while(x != arvore->raiz && x->cor == 'N'){
        if(x == x->pai->esq){
            w = x->pai->dir; 
            if (w->cor == 'R'){
                w->cor = 'N';
                x->pai->cor = 'R';
                rotacaoEsquerda(arvore, x->pai);
                w = x->pai->dir;
            }
            if(w->esq->cor == 'N' && w->dir->cor=='N'){
                w->cor = 'R';
                x= x->pai;
            }else{
                if(w->dir->cor == 'N'){
                    w->esq->cor =  'N';
                    w->cor = 'R';
                    rotacaoDireita(arvore, w);
                    w = x->pai->dir;
                }
                w->cor = x->pai->cor;
                x->pai->cor = 'N';
                w->dir->cor = 'N';
                rotacaoEsquerda(arvore, x->pai);
                x = arvore->raiz;
            }
        }else{
            w = x->pai->esq;
            if (w->cor == 'R') {
                w->cor = 'N';
                x->pai->cor = 'R';
                rotacaoDireita(arvore, x->pai);
                w = x->pai->esq;
            }
            if (w->dir->cor == 'N' && w->esq->cor == 'N') {
                w->cor = 'R';
                x = x->pai;
            } else {
                if (w->esq->cor == 'N') {
                    w->dir->cor = 'N';
                    w->cor = 'R';
                    rotacaoEsquerda(arvore, w);
                    w = x->pai->esq;
                }
                w->cor = x->pai->cor;
                x->pai->cor = 'N';
                w->esq->cor = 'N';
                rotacaoDireita(arvore, x->pai);
                x = arvore->raiz;
            }
        }    
    }
    x->cor = 'N';

}

void removerAux(RubroNegra arvore, No z){
    No y = z;
    No x;
    char corOriginal = y->cor;
    if(z->esq == externo){
        x = z->dir;
        moverPai(arvore, z, z->dir);
    }else if(z->dir == externo){
        x = z->esq;
        moverPai(arvore, z, z->esq);
    }else{
        y = sucessor(z->dir);
        corOriginal = y->cor;
        x= y->dir;
        if(y->pai ==z){
            x->pai = y;
        }else{
            moverPai(arvore, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        moverPai(arvore, z, y);
        y->esq = z->esq;
        y->esq->pai = y;
    }
    if(corOriginal == 'N'){
        consertaRemocao(arvore, x);
    }

    arvore->raiz->cor = 'N';
}

int remover(RubroNegra arvore, int valor) {
    No z = buscar(arvore->raiz, valor);
    No aux = z;
    if (z == externo){
        return 1;
    } 
    else{
        removerAux(arvore, z);
    }        
    free(aux);
    return 0;
}

void imprimeArvore(No x) {
    printf("\tÉ rubro negra: %s\n", verificaRN(x) == TRUE ? "Sim": "Não");
    printf("\tQuantidade de nóś: %d\n", contaNos(x));
}

void preOrdem(RubroNegra arvore) {
    imprimeArvore(arvore->raiz);
    printf("\n");
}

int gerarAleatorio(){
  return (rand() % TOTAL_NO) + 1;
}

int contaNos(No raiz){
    if(raiz == externo){
        return 0;
    }

    return 1 + contaNos(raiz->esq) + contaNos(raiz->dir);
}

void liberaMem(RubroNegra pt){
  if(pt->raiz != externo){
    liberaNos(pt->raiz->dir);
    liberaNos(pt->raiz->esq);
    free(pt);
  }
}

void liberaNos(No no){
    if(no != externo){
        liberaNos(no->esq);
        liberaNos(no->dir);
        free(no);
    }
}

int verificaRN(No raiz){
    No aux = raiz;
    if(aux->cor == 'R'){
        return FALSE;
    }

    int esq = verificaNo(aux->esq);
    int dir = verificaNo(aux->dir);

    if(dir == FALSE || esq == FALSE){
        return FALSE;
    }else{
        return TRUE;
    }
}

int verificaNo(No pt){
    if(pt == externo){
        return TRUE;
    }

    if(pt->cor == 'R'){
        if(pt->dir->cor == 'N' && pt->esq->cor == 'N'){
            int esq = verificaNo(pt->esq);
            int dir = verificaNo(pt->dir);
            if(dir == FALSE || esq == FALSE){
                return FALSE;
            }else{
                return TRUE;
            }
        }else{
            return FALSE;
        }
    }else{
        int esq = verificaNo(pt->esq);
        int dir = verificaNo(pt->dir);
        if(dir == FALSE || esq == FALSE){
            return FALSE;
        }else{
            return TRUE;
        }
    }
}
