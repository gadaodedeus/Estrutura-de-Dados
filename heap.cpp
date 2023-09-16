#include<iostream>

using namespace std;

int Pai(int x)
{
	return x/2;	//  x/2 é a posicao do no pai do no atual
}

//Esta funçao compara o atual (ultimo colocado na primeira posiçao na 1ª chamada) com seu pai(x/2). Se o atual
//for maior as posiçoes sao trocadas. A recursao ocorre ate a heap se organizar completamente 
//( quando maior < Pai(maior) )
void heap_fica(int vet[], int i, int qnt)	
{
	int f_esq, f_dir, maior, aux;
	maior = i;
	
	for(int j=1; j<=qnt; j++)
		cout<<vet[j]<<" ";
	cout<<"\n";	
		
	if(2*i+1 <= qnt) //No com filhos a esquerda e direita
	{
		f_esq = 2*i+1; //Pode estar invertido ??
		f_dir = 2*i;
		if(vet[f_esq] >= vet[f_dir] && vet[f_esq] > vet[i])
			maior = 2*i+1;
		else if(vet[f_dir] > vet[f_esq] && vet[f_dir] > vet[i])
			maior = 2*i;
	}
	
	else if(2*i <= qnt) //No com filho apenas para a esquerda
	{
		f_dir = 2*i;
		if(vet[f_dir] > vet[i])
			maior = 2*i;
	}
	

	if(maior != i)
	{
		aux = vet[i];
		vet[i] = vet[maior];
		vet[maior] = aux;
		
		heap_fica(vet, maior, qnt);
	}
}

int main()
{
	int vet[11];
	int op = 1, tam = 0, ind, num;
	
	while(op)
	{
		cout<<"\n1- Insersao\n";
		cout<<"2- Remocao\n";
		cout<<"3- Consultar\n";
		cout<<"0- Sair\n";
		cin>>op;
		
		if(op == 1)	//Insersao
		{
			if(tam<10) //Verifica se ha espaço no vetor
			{
				tam++;
				cout<<"Digite o numa a ser inderido: ";
				cin>>num;
				ind = tam;
				while(ind > 1 && vet[Pai(ind)] < num)
				{
					vet[ind] = vet[Pai(ind)];
					ind = Pai(ind);
				}	
				vet[ind] = num;
				cout<<"\nNumero inserido\n";
			}	
		
			else
				cout<<"Lista lotada";
		}	
	
		if(op == 2)	//Remoçao
		{
			if(tam == 0)
				cout<<"Lista vazia";
			else
			{
				int maior_prior = vet[1];
				vet[1] = vet[tam];
				tam--;
				heap_fica(vet, 1, tam);
			}
		}
	
		if(op == 3)	//Consultar toda lista
		{
			if(tam == 0)
				cout<<"Lista vazia";
			else
			{
				for(int j=1; j<=tam; j++)
					cout<<vet[j]<<" ";
			}
		}
		
	}
	

	return 0;
}
