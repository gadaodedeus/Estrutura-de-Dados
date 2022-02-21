#include<stdio.h>
#include<stdlib.h>

typedef struct n{
	int senha;
	struct n *prox;
}Num;

void print_lista(Num*);

void add_num(Num**, Num*, Num**);

Num* remove_num(Num*);

int main(){
	Num *topo=NULL, *nums, *ultimo;
	int aloc=10, i=0, op;

	//printf("\n\n\t\tInorme o numero max de senhas: ");
	//scanf("%d", &aloc);
	nums=malloc(aloc*sizeof(Num));
	
	for(i=0;i<aloc;i++){
		(nums+i)->senha=i+1;
		(nums+i)->prox=NULL;}
	i=0;
	
	do{
		printf("\n\n\t\t\t\t----------------------------------------------");
		printf("\n\n\t\t\t\t\t\t\tEscolha uma opcao:\n\n");
		printf("\n\n\t\t\t\t\tAdicionar a FILA...................1");
		printf("\n\n\t\t\t\t\tChamar proximo.....................2");
		printf("\n\n\t\t\t\t\tMostrar FILA.......................3");
		printf("\n\n\t\t\t\t\tSair...............................0");
		printf("\n\n\t\t\t\t----------------------------------------------\n\n\n\n\n");
		scanf("%d", &op);
		
		if(op==1){
			add_num(&topo, nums+i, &ultimo);
			i++;
		}
		
		if(op==2){
			topo=remove_num(topo);
			if(!(topo)) ultimo=NULL;
		}
		
		if(op==3) print_lista(topo);
	
	}while(op && i-1!=aloc);
	
	return 0;
}






void print_lista(Num* lista){
	Num* aux;
	int qnt=0;
	aux=lista;
	printf("\n\n");
	
	if(!(lista)){
	printf("\tLista vazia!");
	return;}
	
	do{
		printf("\t%d", aux->senha);
		aux=aux->prox;	
		qnt++;	
	}while(aux);
	
	printf("\n\n\tqnt: %d", qnt);
	return;
}






void add_num(Num** topo, Num* num, Num** ultimo){	
	if (!(*ultimo)){
		*(topo)=num; 
		*(ultimo)=num;
		return;}
	Num* aux=*(topo);
	num->prox=aux;
	*(topo)=num;
	return;
	
}






Num* remove_num(Num* topo){
	
	if (!(topo)){
		printf("\n\n\t\tLista Vazia!!!");
		return topo;}
	
	else {
	Num* aux=topo->prox;
	return (aux);}
	
}





