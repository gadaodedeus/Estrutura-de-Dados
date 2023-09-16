#include <iostream>
using namespace std;

typedef struct a{
	int num, altd, alte;
	struct a *esq, *dir;
}arvore;

arvore* inserir(arvore* aux, int num);
arvore* balanceamento(arvore* aux);
arvore* rotacao_esq(arvore* aux);
arvore* rotacao_dir(arvore* aux);
int consultar(arvore* aux, int num, int achou);
void mostrar_em_ordem(arvore *aux);
void mostrar_pre_ordem(arvore *aux);
void mostrar_pos_ordem(arvore *aux);
arvore* remover(arvore *aux, int num);
arvore* atualiza(arvore* aux);
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
				cout<<"Digite o numero a ser removido\n";
				cin>>numero;
				achou = 0;
				achou = consultar(raiz, numero, achou);
				if(!achou)
					cout<<"Numero nao encontrado\n";
				else
				{
					raiz = remover(raiz, numero);
					raiz = atualiza(raiz);
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
	arvore* novo;
	
	if(aux == NULL)
	{
		novo = new arvore();
		novo->num = num;
		novo->altd=0;
		novo->alte=0;
		novo->esq = NULL;
		novo->dir = NULL;
		aux = novo;
	}
	
	else if(num < aux->num)	//Esq
	{
		aux->esq = inserir(aux->esq, num);
		if(aux->esq->altd > aux->esq->alte)
			aux->alte = aux->esq->altd + 1;
		else
			aux->alte = aux->esq->alte + 1;
		aux = balanceamento(aux);
	}
	
	else //Dir
	{
		aux->dir = inserir(aux->dir, num);
		if(aux->dir->altd > aux->dir->alte)
			aux->altd = aux->dir->altd + 1;
		else
			aux->altd = aux->dir->alte + 1;
		aux = balanceamento(aux);
	}
		
	return aux;
}

arvore* balanceamento(arvore* aux)
{
	int d, df;
	d = (aux->altd) - (aux->alte);
	if(d == 2)
	{
		df = (aux->dir->altd) - (aux->dir->alte);
		if(df >= 0)
			aux = rotacao_esq(aux);
		else
		{
			aux->dir = rotacao_dir(aux->dir);
			aux = rotacao_esq(aux);
		}	
	}
	else if(d == -2)
	{
		df = (aux->esq->altd) - (aux->esq->alte);
		if(df <= 0)
			aux = rotacao_dir(aux);
		else
		{
			aux->esq = rotacao_esq(aux->esq);
			aux = rotacao_dir(aux);
		}
	}
	return aux;
}

arvore* rotacao_esq(arvore* aux)
{
	arvore *aux1, *aux2;
	
	aux1 = aux->dir;
	aux2 = aux1->esq;
	aux->dir = aux2;
	aux1->esq = aux;
	
	
	if(aux->dir == NULL)
		aux->altd = 0;
	else if(aux->dir->alte > aux->dir->altd)
		aux->altd = aux->dir->alte + 1;
	else
		aux->altd = aux->dir->altd + 1;
		
	if(aux1->esq->alte > aux1->esq->altd)
		aux1->alte = aux1->esq->alte + 1;
	else
		aux1->alte = aux1->esq->altd + 1;
	
	return aux1;
}

arvore* rotacao_dir(arvore* aux)
{
	arvore *aux1, *aux2;
	
	aux1 = aux->esq;
	aux2 = aux1->dir;
	aux->esq = aux2;
	aux1->dir = aux;
	
	if(aux->esq == NULL)
		aux->alte = 0;
	else if(aux->esq->alte > aux->esq->altd)
		aux->alte = aux->esq->alte + 1;
	else
		aux->alte = aux->esq->altd + 1;
	if(aux1->dir->alte > aux1->dir->altd)
		aux1->altd = aux1->dir->alte + 1;
	else
		aux1->altd = aux1->dir->altd + 1;
	return aux1;
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

arvore* atualiza(arvore* aux)
{
	if(aux)
	{
		aux->esq = atualiza(aux->esq);
		if(aux->esq == NULL)
			aux->alte = 0;
		else if(aux->esq->alte > aux->esq->altd)
			aux->alte = aux->esq->alte + 1;
		else
			aux->alte = aux->esq->altd + 1;
		aux->dir = atualiza(aux->dir);
		if(aux->dir == NULL)
			aux->altd = 0;
		else if(aux->dir->alte > aux->dir->altd)
			aux->altd = aux->dir->alte + 1;
		else
			aux->altd = aux->dir->altd + 1;
		aux = balanceamento(aux);
	}
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
