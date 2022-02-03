#include<stdio.h>
#include<stdlib.h>

typedef struct n{
	int ref;
	struct n *prox;
}Num;

void print_lista(Num*);

Num* add_num(Num*, Num*);

int main(){
	Num *inicio=NULL, Num_1, Num_2, Num_3, Num_4;
	
	scanf("%d", &Num_1.ref);
	inicio=add_num(inicio, &Num_1);
	print_lista(inicio);
	
	scanf("%d", &Num_2.ref);
	inicio=add_num(inicio, &Num_2);
	print_lista(inicio);
	
	scanf("%d", &Num_3.ref);
	inicio=add_num(inicio, &Num_3);
	print_lista(inicio);
	
	scanf("%d", &Num_4.ref);
	inicio=add_num(inicio, &Num_4);
	print_lista(inicio);
}

void print_lista(Num* lista){
	Num* aux_print;
	aux_print=lista;
	do{
		printf("%d", aux_print->ref);
		aux_print=aux_print->prox;		
	}while(aux_print);
}

Num* add_num(Num* lista, Num* num){
	Num* aux;
	int flag=0;
	aux=lista;
	
	if (!(aux)){
		aux=num; 
		aux->prox=NULL;
		return aux;}
	
	if(num->ref <= aux->ref){
		num->prox=aux;
		aux=num;
		return aux;}

	while(aux->prox && aux->prox->ref < num->ref){
		aux=aux->prox;
		if(!(aux->prox)){
			 flag=1;
			 break;}
	}
	if(flag) num->prox=NULL;
	
	else num->prox=aux->prox;
	aux->prox=num;
	
	return lista;
	
}






