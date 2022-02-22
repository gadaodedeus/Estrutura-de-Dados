#include<stdio.h>
#include<stdlib.h>

typedef struct n{
	int ref;
	struct n *prox;
}Num;

void print_lista(Num*);

void add_num(Num**, Num*, Num**);

void remove_num(Num**, int, Num**);

int naoChegou(int, int);

int main(){
	Num *inicio=NULL, *fim, *nums, *elem_1, *elem_2, *elem_3, *elem_4, *elem_5;
	int i=0;
	elem_1=malloc(sizeof(Num));
	elem_2=malloc(sizeof(Num));
	elem_3=malloc(sizeof(Num));
	elem_4=malloc(sizeof(Num));
	elem_5=malloc(sizeof(Num));
	
	//elem_1->ref=12;
	scanf("%d", &elem_1->ref);
	elem_1->prox=elem_1;
	add_num(&inicio, elem_1, &fim);
	print_lista(inicio);
	
	scanf("%d", &elem_2->ref);
	elem_2->prox=elem_2;
	add_num(&inicio, elem_2, &fim);
	print_lista(inicio);
	
	scanf("%d", &elem_3->ref);
	elem_3->prox=elem_3;
	add_num(&inicio, elem_3, &fim);
	print_lista(inicio);
	
	scanf("%d", &elem_4->ref);
	elem_4->prox=elem_4;
	add_num(&inicio, elem_4, &fim);
	print_lista(inicio);
	
	scanf("%d", &elem_5->ref);
	elem_5->prox=elem_5;
	add_num(&inicio, elem_5, &fim);
	print_lista(inicio);
	
	remove_num(&inicio, elem_3->ref, &fim);
	print_lista(inicio);
	
	remove_num(&inicio, elem_5->ref, &fim);
	print_lista(inicio);
	
	remove_num(&inicio, elem_1->ref, &fim);
	print_lista(inicio);
	
	remove_num(&inicio, elem_4->ref, &fim);
	print_lista(inicio);
	
	remove_num(&inicio, elem_2->ref, &fim);
	print_lista(inicio);
}

void print_lista(Num* lista){
	Num* aux_print;
	aux_print=lista;
	printf("\n\n");
	
	if(!(lista)) printf("\n\n\tLista vazia!");
	
	do{
		printf("%d", aux_print->ref);
		aux_print=aux_print->prox;		
	}while(aux_print != lista);
}

void add_num(Num** inicio, Num* num, Num** fim){
	Num *aux, *ant;
	aux=*inicio; 
	ant=*inicio;
	
	if (!(aux)){
		*inicio=num;
		return;}
	
	if(aux==aux->prox){  //apenas um elem na lista
		num->prox=aux;
		aux->prox=num;
		if(num->ref<=aux->ref)
			*(inicio)=num;
		return;}
		
	
	while(naoChegou(aux->ref, num->ref) && ant->prox != *inicio){
		ant=aux;
		aux=aux->prox;}
		
	if (aux == (*inicio) && num->ref < aux->ref){ 
		ant = aux->prox;
		
		while (ant->prox != aux)    //ate ant apontar para o ultimo elem da lista
			ant = ant->prox;		//PODE SER SUBSTITUIDO POR UM PONTEIRO (final)
			
		ant->prox = num;
		num->prox = (*inicio);
		(*inicio) = num;
		return;}
		
	num->prox = aux; 
	ant->prox = num; 
	
	if (num->ref < (*inicio)->ref)
		(*inicio) = num;
		
	return;
}
	

void remove_num(Num** inicio, int num, Num** fim){
	Num *aux, *ant;
	aux=*inicio;
	ant=*inicio;
	
	if(!(aux)){printf("\n\n\tLista vazia!");return;}
	
	if((*inicio)->prox==*inicio && num==(*inicio)->ref){
		*inicio=NULL;
		free(aux);
		return;
	} 
		
	while(num != aux->ref && aux->prox != *inicio){
		ant=aux;
		aux=aux->prox;
	}
	
	if(num==aux->ref){
		if(aux != *inicio) ant->prox=aux->prox;
		
		else{
			while (ant->prox != (*inicio)) ant = ant->prox;
			ant->prox = aux->prox;	
			(*inicio) = aux->prox;
		}
		
		free(aux);
	}
	else puts("\n\n\tnot found");
	return;
}

int naoChegou(int aux, int ref){
	if(aux>=ref) 
		return 0;
	
	return 1;

}




