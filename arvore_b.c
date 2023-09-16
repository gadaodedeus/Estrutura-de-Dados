/* O print requerido na avaliacao é a funcao print_pre*/


#include <stdio.h>
#include <stdlib.h>
#define MAX 3
#define MIN 2

typedef struct No {
    int item[MAX+1], count, ordem;
    struct No *link[MAX + 1];
} No;
No *raiz;

int setNo(int item, int *pval, No *no, No **filho);
void inserir(int item);
void InserirValor(int item, int pos, No *no,No *filho);
No *criarNo(int item, No *filho);
void divideNo(int item, int *pval, int pos, No *no, No *filho, No **novoNo);
void procura( No *noSelecionado);
int busca_no(No* root, int chave, int* pos);
int RemoveArvB(No **arvore, int chave);
int RemoveArvBRec(No **no, int chave, int *underflow);
void TrocaChaveComAntecessora(No *no, int pos);
void TrataNoComMenosChavesQuePermitido(No **no, int pos);
void RemoveChaveEmNo(No *no, int pos);
int NoComMaisChavesQuePossivel(No *no);
int NoComMenosChavesQuePermitido(No *no);
void print_pre( No *root, int h, int index_link);


int main() {
    int op=1;

    while(op)
    {
        printf("\n\n\n\n\t\t----------MENU----------\n\n\t1- Inserir\n\n\t2- Print Arvore\n\n\t3- Buscar Numero\n\n\t4- Print Pre Ordem\n\n\t0- Sair");
        do{
            printf("\n\nInforme uma opcao valida!");
            scanf("%d", &op); 
        }while(op<0 || op>4);
        
        if(op == 1)
        {
            int num;
            printf("\nInforme o numero a ser inserido");
            scanf("%d", &num);
            inserir(num);
        }

        if(op == 2) procura(raiz);

        if(op == 3)
        {
            int chave, achou;
            printf("\nInforme o numero que sera buscado");
            scanf("%d", &chave);
            if(busca_no(raiz, chave, &achou))
                printf("\n\n\t\tChave encontrada!");
            else
                printf("\n\n\t\tChave nao encontrada!!!");
        }
        
        if(op == 4) print_pre(raiz, 0, 0);
    }
}

int setNo(int item, int *pval, No *no, No **filho)
{
    int pos;
    if (!no) {
        *pval = item;
        *filho = NULL;
        return 1;
    }
    if (item < no->item[1]) {
        pos = 0;
    } else {
        for (pos=no->count; (item < no->item[pos] && pos > 1);pos--);
        if (item == no->item[pos])
        {
            printf("Não permite valor duplicado\n");
            return 0;
        }
    }
    if (setNo(item, pval, no->link[pos], filho)) {
        if (no->count < MAX) {
            InserirValor(*pval, pos, no, *filho);
        } else {
            divideNo(*pval, pval, pos, no, *filho, filho);
            return 1;
        }
    }
    return 0;
}

void inserir(int item) {
    int flag, i;
    No *filho;
    flag = setNo(item, &i, raiz, &filho);
    if (flag)
        raiz = criarNo(i, filho);
}

void InserirValor(int item, int pos, No *no,No *filho) {
    int j = no->count;
    while (j > pos) {
        no->item[j + 1] = no->item[j];
        no->link[j + 1] = no->link[j];
        j--;
    }
    no->item[j + 1] = item;
    no->link[j + 1] = filho;
    no->count++;
}

No *criarNo(int item, No *filho) {
    No *novoNo;
    novoNo = (No*)malloc(sizeof(No));
    novoNo->item[1] = item;
    novoNo->count = 1;
    novoNo->link[0] = raiz;
    novoNo->link[1] = filho;
    novoNo->ordem = MAX+1;
    return novoNo;
}

void divideNo(int item, int *pval, int pos, No *no, No *filho, No **novoNo) {
    int mediana, j;
    if (pos > MIN)
        mediana = MIN + 1;
    else
        mediana = MIN;
    *novoNo = ( No *)malloc(sizeof( No));
    j = mediana + 1;
    while (j <= MAX) {
        (*novoNo)->item[j - mediana] = no->item[j];
        (*novoNo)->link[j - mediana] = no->link[j];
        j++;
    }
    no->count = mediana;
    (*novoNo)->count = MAX - mediana;
    if (pos <= MIN)
    {
        InserirValor(item, pos, no, filho);
    } else {
        InserirValor(item, pos - mediana, *novoNo, filho);
    }
    *pval = no->item[no->count];
    (*novoNo)->link[0] = no->link[no->count];
    no->count--;
}

void procura( No *noSelecionado) {
    int i;
    if (noSelecionado) {
        for (i = 0; i < noSelecionado->count; i++) {
            procura(noSelecionado->link[i]);
            printf("%d ", noSelecionado->item[i+1]);
        }
        procura(noSelecionado->link[i]);
    }
}

int busca_no(No* root, int chave, int* pos)
{
    int i, flag=0;
    if(root)
    {
        for (i = 0; i < root->count; i++) {
            if(root->item[i+1] == chave)
            {
            	*pos = i+1;
            	return 1;
            }
                

            else if(root->item[i+1] > chave)
                flag = busca_no(root->link[i], chave, pos);
        }
        if(flag) return flag;
        flag = busca_no(root->link[i], chave, pos);
        if(flag) return flag;
        
    }
    return 0;
}

int RemoveArvB(No **arvore, int chave)
{
  if ((*arvore) == NULL){
    printf("Erro em RemoveArvB: Árvore inexistente\n");
    exit(1);
  }
  int underflow=0;
  
  if(RemoveArvBRec(arvore, chave, &underflow)){ /* A chave foi removida */

    /* Se o underflow chegou até a raiz da arvore, entao a raiz antiga
       deve ser eliminada e a nova será a sua única filha, reduzindo
       assim a altura da arvore em 1.
    */
    
    if(underflow) {
      No *no = *arvore;
      *arvore = (*arvore)->link[0];
      free(no);
    }
    return(1);
  }
  return(0);
}

int RemoveArvBRec(No **no, int chave, int *underflow)
{
  int pos;
  
  /* Verifica se a chave está no nó atual. Se tiver e esse nó for uma
  folha, realiza a remoção. Caso contrário, troca a chave pela
  antecessora e continua o procedimento recursivo para remoção. */

  if (busca_no(*no, chave, &pos)) {     /* a chave está no nó deste nível */
     if ((*no)->link[pos]!=NULL) {    
            /* O nó atual não é uma folha,
			 		  então a chave precisa ser trocada pela antecessora, reduzindo ao caso de remoção na folha. */

          TrocaChaveComAntecessora(*no, pos);   /* troca a chave pela sua antecessora -- i.e., a
					       chave mais à direita na árvore à esquerda. continua o procedimento recursivo para
                 reencontrar e remover a chave do nó folha */

          RemoveArvBRec(&((*no)->link[pos]), chave, underflow);
          /* trata underflow, se for o caso, após a remoção da chave */
          if (*underflow) 
             TrataNoComMenosChavesQuePermitido(no, pos); 

     } else { /* achou a chave no nó folha, então ela pode ser removida. */
        RemoveChaveEmNo(*no, pos);
     }
     /* verifica se a folha ficou em underflow */

     (*underflow) = NoComMenosChavesQuePermitido(*no); 
     return(1);   /* remoção bem sucedida */
  } else { /* procura a chave nos nós abaixo */
     if ((*no)->link[pos] != NULL) {
        if (RemoveArvBRec(&((*no)->link[pos]), chave, underflow)) {
	            /* a chave foi encontrada e removida da folha (raiz da árvore
	            filha). Trata um possível underflow e verifica novamente se
	            ele será propagado para cima (volta da recursão). */
	          if (*underflow)
               TrataNoComMenosChavesQuePermitido(no, pos);
	          (*underflow) = NoComMenosChavesQuePermitido(*no);
	          return(1);
        } else {
	          return(0); /* chego na folha e não achou a chave */
        }
     } else {  /* estamos na raiz e a chave não está neste nível, logo ela não existe. */
        (*underflow) = 0;
         return(0);
     }
  }
}


void TrocaChaveComAntecessora(No *no, int pos)
{
  No *no_aux;
  int   chave_aux;
  
  no_aux = no->link[pos]; /* árvore filha à esquerda da chave na posição "pos" */
  while(no_aux->link[no_aux->count]!=NULL) /* busca a chave mais à direira na àrvore esquerda (i.e., a antecessora da chave que está em "no" na posição "pos") */
      no_aux = no_aux->link[no_aux->count];

  /* troca a chave por sua antecessora na árvore B */
  chave_aux  = no->item[pos];
  no->item[pos] = no_aux->item[no_aux->count-1];
  no_aux->item[no_aux->count-1] = chave_aux;
}

void TrataNoComMenosChavesQuePermitido(No **no, int pos)
{
  int chave,i,j;
  No *irma_esq=NULL, *filha=NULL, *irma_dir=NULL;

  filha = (*no)->link[pos];
  
  if (pos > 0) { /* existe irmã à esquerda da filha */ 
     irma_esq = (*no)->link[pos-1];
     if(irma_esq->count > (((*no)->ordem)/2)) { /* A irmã à esquerda tem chaves para emprestar. A sua última chave sobe
						  para o nó pai e a chave do nó pai  desce para a filha na posição mais à esquerda. A filha à direira da chave que
						  subiu passa a ser filha à esquerda daquela que desceu.*/
         chave = (*no)->item[pos-1]; 
         (*no)->item[pos-1]=irma_esq->item[irma_esq->count-1]; 
         No *filha_esq          = irma_esq->link[irma_esq->count]; 
         RemoveChaveEmNo((*no)->link[pos-1],(*no)->link[pos-1]->count);
         filha->count++;
         filha->link[0] = filha_esq;
         filha->item[0] = chave;
         return;
     }
  }
  
  if (pos < (*no)->count) { /* existe irmã à direita */ 
    irma_dir = (*no)->link[pos+1];
    if (irma_dir->count > (((*no)->ordem)/2)) { /* A irmã à direita tem chaves para
						  emprestar. A sua primeira chave sobe para o nó pai e a chave do nó pai desce para a filha na posição mais à
						  direita. A filha à esquerda da chave que subiu passa a ser filha à direita daquela que desceu. */
        chave   = (*no)->item[pos];
        (*no)->item[pos] = irma_dir->item[0];
        No *filha_dir = irma_dir->link[0];
        RemoveChaveEmNo((*no)->link[pos+1],0);
        filha->count++;
        filha->link[filha->count]   = filha_dir;
        filha->item[filha->count-1] = chave;
        return;
    }    
  }
}


void RemoveChaveEmNo(No *no, int pos)
{
  int i;
  /* desloca as chaves e filhas para trás */
  for(i=pos; i < no->count; i++)
  {
      no->item[i] = no->item[i+1];
      no->link[i] = no->link[i+1];
  }
  /* completa o deslocamento para a filha à direita da última chave */ 
  no->link[i]   = no->link[i+1];
  no->link[i+1] = NULL;
  /* ajusta o número de registros */
  no->count--;
}

int NoComMaisChavesQuePossivel(No *no)
{
  return(no->count > no->ordem);
}

int NoComMenosChavesQuePermitido(No *no)
{
  return(no->count < (no->ordem/2));
}

void print_pre( No *root, int h, int index_link) {
    int i;
    if (root) {
    	printf("\n");
    	for(i=0;i<h;i++)
    		printf("\t");
    	printf("%d)[", index_link);
        for (i = 0; i < root->count; i++) {
            printf(" %d ", root->item[i + 1]);
        }
        printf("]\n");
        h++;
        for (i = 0; i <= root->count; i++) 
	        print_pre(root->link[i], h,i);
    }
}

