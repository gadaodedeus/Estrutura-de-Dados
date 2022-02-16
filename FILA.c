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
	Num *primeiro=NULL, *nums, *ultimo;
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
			add_num(&primeiro, nums+i, &ultimo);
			i++;
		}
		
		if(op==2){
			primeiro=remove_num(primeiro);
			if(!(primeiro)) ultimo=NULL;
		}
		
		if(op==3) print_lista(primeiro);
	
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






void add_num(Num** primeiro, Num* num, Num** ultimo){
	
	if (!(*primeiro)){
		*(primeiro)=num; 
		*(ultimo)=num;
		return;}
	Num* aux=*(ultimo);
	aux->prox=num;
	*(ultimo)=num;
	return;
	
}






Num* remove_num(Num* primeiro){
	
	if (!(primeiro)){
		printf("\n\n\t\tLista Vazia!!!");
		return primeiro;}
	
	else return (primeiro->prox);
	
}





