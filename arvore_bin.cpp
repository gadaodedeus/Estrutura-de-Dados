#include <iostream>
using namespace std;

typedef struct a{
	int num;
	struct a *esq, *dir;
}arvore;

arvore* inserir(arvore* aux, int num);
int consultar(arvore* aux, int num, int achou);
void mostrar_em_ordem(arvore *aux);
void mostrar_pre_ordem(arvore *aux);
void mostrar_pos_ordem(arvore *aux);
arvore* remover(arvore *aux, int num);
arvore* desalocar(arvore *aux);

int main()
{
	arvore* raiz = NULL;
	arvore* aux;
	int op, numero, achou;
	
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
			cout<<"Digite o numero a ser inserido\n";
			cin>>numero;
			raiz = inserir(raiz, numero);
		}
		
		if(op == 2)	//Consultar no da arvore
		{
			if(raiz == NULL)
				cout<<"Arvore vazia\n";
			else
			{
				cout<<"Digite o numero a ser consultado";
				cin>>numero;
				achou = 0;
				achou = consultar(raiz, numero, achou);
				if(!achou)
					cout<<"Numero nao encontrado\n";
				else
					cout<<"Numero encontrado\n";
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
				cin>>numero;
				achou = 0;
				achou = consultar(raiz, numero, achou);
				if(!achou)
					cout<<"Numero nao encontrado\n";
				else
				{
					raiz = remover(raiz, numero);
					cout<<"Numero removido com sucesso!\n";
				}
					
			}
		}
		
		if(op == 7)	//Desalocar
		{
			if(raiz == NULL)
				cout<<"Arvore vazia\n";
			else
				raiz = desalocar(raiz);
		}
			
		
	}while(op);
	return 0;
}


arvore* inserir(arvore* aux, int num)
{
	if(aux == NULL)
	{
		aux = new arvore();
		aux->num = num;
		aux->esq = NULL;
		aux->dir = NULL;
	}
	
	else if(num < aux->num)
		aux->esq = inserir(aux->esq, num);
	
	else
		aux->dir = inserir(aux->dir, num);
		
	return aux;
}

int consultar(arvore* aux, int num, int achou)
{
	if(aux != NULL && achou == 0)
	{
		if(aux->num == num)
			achou = 1;
		else if(num < aux->num)
			achou = consultar(aux->esq, num, achou); //esquerda
		else
			achou = consultar(aux->dir, num, achou); //direita
	}
	return achou;
}

void mostrar_em_ordem(arvore *aux)
{
	if(aux != NULL)
	{
		mostrar_em_ordem(aux->esq);
		cout<<aux->num<<" ";
		mostrar_em_ordem(aux->dir);
	}
}

void mostrar_pre_ordem(arvore *aux)
{
	if(aux != NULL)
	{
		cout<<aux->num<<" ";
		mostrar_pre_ordem(aux->esq);
		mostrar_pre_ordem(aux->dir);
	}
}

void mostrar_pos_ordem(arvore *aux)
{
	if(aux != NULL)
	{
		mostrar_pos_ordem(aux->esq);
		mostrar_pos_ordem(aux->dir);
		cout<<aux->num<<" ";
	}
}

arvore* remover(arvore* aux, int num)
{
	arvore *p, *p2;
	if(aux->num == num)
	{
		if(aux->esq == aux->dir)	//Elemento a ser removido nao tem filhos
		{
			delete(aux);
			return NULL;
		}
		else if(aux->esq == NULL)	//Elemento a ser removido nao tem filho a esquerda
		{
			p = aux->dir;
			delete(aux);
			return p;
		}
		else if(aux->dir == NULL)	//Elemento a ser removido nao tem filho a direita
		{
			p = aux->esq;
			delete(aux);
			return p;
		}
		else
		{
			p2 = aux->dir;
			p = aux->dir;
			while(p->esq != NULL)
				p = p->esq;
			p->esq = aux->esq;
			delete(aux);
			return p2;
		}
	}
	
	else if(aux->num < num)
		aux->dir = remover(aux->dir, num);
	else
		aux->esq = remover(aux->esq, num);
	return aux;
}

arvore* desalocar(arvore *aux)
{
	if(aux != NULL)
	{
		aux->esq = desalocar(aux->esq);
		aux->dir = desalocar(aux->dir);
		delete(aux);
	}
	return NULL;
}
