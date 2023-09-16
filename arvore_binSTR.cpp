#include <iostream>
#include <string.h>
using namespace std;

typedef struct a{
	char nome[20];
	struct a *esq, *dir;
}arvore;

arvore* inserir(arvore* aux, char nome[20]);
int consultar(arvore* aux, char nome[20], int achou);
void mostrar_em_ordem(arvore *aux);
void mostrar_pre_ordem(arvore *aux);
void mostrar_pos_ordem(arvore *aux);
arvore* remover(arvore *aux, char nome[20]);
arvore* desalocar(arvore *aux);
int compStr(char str1[], char str2[]);

int main()
{
	arvore* raiz = NULL;
	arvore* aux;
	int op, achou;
	char nome[20];
	
	do
	{
		cout<<"\n\t\tMENU DE OPCOES\n";
		cout<<"\t1- Inserir\n";
		cout<<"\t2- Consultar no da arvore\n";
		cout<<"\t3- Print em ordem\n";
		cout<<"\t4- Print pre ordem\n";
		cout<<"\t5- Print pos ordem\n";
		cout<<"\t6- Remover um numero\n";
		cout<<"\t0- Sair\n";
		cout<<"\nDigite a opcao\n";
		cin>>op;
		if(op<0 || op>7)
			cout<<"\nOpcao invalida!\n";
			
		if(op == 1)	//Inserçao
		{
			cout<<"Digite o nome a ser inserido\n";
			cin>>nome;
			raiz = inserir(raiz, nome);
		}
		
		if(op == 2)	//Consultar no da arvore
		{
			if(raiz == NULL)
				cout<<"Arvore vazia\n";
			else
			{
				cout<<"Digite o nome a ser consultado\n";
				cin>>nome;
				achou = 0;
				achou = consultar(raiz, nome, achou);
				if(!achou)
					cout<<"Nome nao encontrado\n";
				else
					cout<<"Nome encontrado\n";
			}
		}
		
		if(op == 3)	//Em ordem
		{
			if(raiz == NULL)
				cout<<"Arvore vazia\n";
			else
				mostrar_em_ordem(raiz);
		}
		if(op == 4)	//Pre ordem
		{
			if(raiz == NULL)
				cout<<"Arvore vazia\n";
			else
				mostrar_pre_ordem(raiz);
		}
		
		if(op == 5)	//Pos ordem
		{
			if(raiz == NULL)
				cout<<"Arvore vazia\n";
			else
				mostrar_pos_ordem(raiz);
		}
		
		if(op == 6)	//Remover
		{
			if(raiz == NULL)
				cout<<"Arvore vazia\n";
			else
			{
				cin>>nome;
				achou = 0;
				achou = consultar(raiz, nome, achou);
				if(!achou)
					cout<<"Numero nao encontrado\n";
				else
				{
					raiz = remover(raiz, nome);
					cout<<"Numero removido com sucesso!\n";
				}
					
			}
		}
		
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		/*if(op == 7)	//Desalocar
		{
			if(raiz == NULL)
				cout<<"Arvore vazia\n";
			else
				raiz = desalocar(raiz);
		}*/
			
		
	}while(op);
	return 0;
}

arvore* inserir(arvore* aux, char nome[20])
{
	if(aux == NULL)
	{
		aux = new arvore();
		aux->esq = NULL;
		aux->dir = NULL;
		strcpy(aux->nome, nome);
	}
	
	else if((int)aux->nome[0] < (int)nome[0])
		aux->dir = inserir(aux->dir, nome);
		
	else
		aux->esq = inserir(aux->esq, nome);
	
	return aux;
}

int consultar(arvore* aux, char nome[20], int achou)
{
	if(achou == 0 && aux != NULL)
	{
		if(compStr(aux->nome, nome))
			achou = 1;
		
		else if((int)aux->nome[0] < (int)nome[0])
			achou = consultar(aux->dir, nome, achou);
		
		else
			achou = consultar(aux->esq, nome, achou);
	}
	
	return achou;
}

void mostrar_em_ordem(arvore *aux)
{
	if(aux)
	{
		mostrar_em_ordem(aux->esq);
		cout<<aux->nome<<"\n";
		mostrar_em_ordem(aux->dir);
	}
}

void mostrar_pre_ordem(arvore *aux)
{
	if(aux)
	{
		cout<<aux->nome<<"\n";
		mostrar_pre_ordem(aux->esq);
		mostrar_pre_ordem(aux->dir);
	}
}

void mostrar_pos_ordem(arvore *aux)
{
	if(aux)
	{
		mostrar_pos_ordem(aux->esq);
		mostrar_pos_ordem(aux->dir);
		cout<<aux->nome<<"\n";
	}
}

arvore* remover(arvore* aux, char nome[20])
{
	arvore *p, *p2;
	if(compStr(aux->nome, nome))
	{
		if(aux->dir == aux->esq)
		{
			delete(aux);
			return NULL;
		}
		
		else if(!aux->dir)
		{
			p = aux->esq;
			delete(aux);
			return p;
		}
		
		else if(!aux->esq)
		{
			p = aux->dir;
			delete(aux);
			return p;
		}
		
		else
		{
			p = aux->dir;
			p2 = aux->dir;
			while(p->esq)
				p = p->esq;
			p->esq = aux->esq;
			delete(aux);
			return p2;
		}
	}
	
	else if((int)aux->nome[0] < (int)nome[0])
		aux->dir = remover(aux->dir, nome);
	else
		aux->esq = remover(aux->esq, nome);
	return aux;
}

int compStr(char str1[], char str2[])
{
	int i=0;
	//cout<<str1<<str2;
	while(str1[i] != '\0' && str2[i] != '\0')
	{
		if(str1[i] != str2[i])
			return 0;
		i++;
	}
	if((str1[i] == '\0' && str2[i] != '\0') || (str2[i] == '\0' && str1[i] != '\0'))
		return 0;
	//cout<<"\n\nIguais\n\n";
	return 1;
}





