#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TAM 9

typedef struct{
  char nome[TAM];
  int tamanho;
} App;

App store_apps[TAM];  //aplicativos da loja
App my_apps[TAM];     //aplicativos instalados no dispositivo
App run_apps[TAM];    //aplicativos "rodando" no dispositivo
App matriz[TAM];      //aplicativos da matriz area de trabalho

int quant_apps = 0; //quantidade de aplicativos
int quant_apps_inst = 0; //quantidade de aplicativos instalados
int quant_apps_exe = 0; //quantidade de aplicativos em execucao
int contador = 0; //contador de passos
int elementos = 0; //elementos da matriz

void menu(); //funcao que "abre" o menu inicial mostrando as opçoes: Loja, Meus aplicativos, Executar, Sair
void menu2(); //abre o menu da "loja"
void busca(); //faz a busca nos meus aplicativos
void busca2(); //faz a busca nos aplicativos em execução
void busca3(); //faz a busca na area de trabalho, mostrando a matriz que a compoe
void start(); //inicia a aplicacao na funcao main
void leitura(); //faz a leitura do arquivo de texto com o nome dos aplicativos
void copmat(); //compara a matriz da area de trabalho com os my apps
void imprimemat(); //imprime a matriz da area de trabalho
void exclumat(); //exclui o elemento da matriz area de trabalho
void imprime(); //exibe o menu loja
void imprime2(); //exibe o menu meus apps
void imprime3(); //exibe o menu execucao
void instalar(); //faz a instalacao dos my_apps atraves do store_apps
void excluir(); //exclui aplicativos instalados no my_apps
void excluir2(); //para a execucao de um aplicativo, ou seja retira-o do run_apps
void executar(); //executa um aplicativo, ou seja adiciona-o no run_apps

void start()
{
  int i;
  char a[TAM] = "";
  for (i = 0; i < TAM; i++)
    {
    strcpy(store_apps[i].nome, a);
    store_apps[i].tamanho = -1;
    strcpy(my_apps[i].nome, a);
    my_apps[i].tamanho = -1;
    }
}

void leitura()
{
	FILE *p;
	int i = 0;
	p = fopen("entrada.txt", "r");
	if(p == NULL)
		perror("O arquivo nao pode ser lido corretamente.\n\n");
	while(fscanf(p, "%s %d", store_apps[i].nome, &store_apps[i].tamanho) != EOF)// problema na leitura fgets
		{
			quant_apps++	;
			i++;
		}
	fclose(p);
}

void copmat()
{
	int a, l = 0, k, i, j, flag = 0, p, fim;

	printf("Informe o indice do app:    ");
	scanf("%d", &a);

	for(i = 0; i < quant_apps_inst; i++)
		{
			if(i + 1 == a)
				{
					k = i;
					flag = 1;
					break;
				}
		}
	if(flag == 0)
		printf("\nO app nao existe ou nao foi instalado.\n\n");
	else
		{
			if(elementos <	TAM)
				{
					if(elementos == 0)
						{
							matriz[0] = my_apps[k];
							printf("\n----------------------------------------\n");
							printf("---> OPERACAO REALIZADA COM SUCESSO <---\n");
							printf("-----------------------------------------\n\n");
							contador++;
							elementos++;
						}
					else
						{
							//verifica se o app ja foi instalado anteriormente
							for(j = 0; j < elementos; j++)
								{
									if(strcmp(my_apps[k].nome , matriz[j].nome) == 0)
										{
											printf("\n----------------------------------------\n");
											printf("--->     O app JA FOI INSTALADO     <---\n");
											printf("----------------------------------------\n\n");
											menu();
										}
								}
							//verifica a posicao para o app ser instalado ordenado
							for(fim = 0; fim < elementos; fim++)
								{
									if(my_apps[k].tamanho > matriz[fim].tamanho)
										l++;
								}

							for(p = elementos - 1 ; p >= l ; p--)
								{
									matriz[p + 1] = matriz[p];
									contador++;
								}
							matriz[l] = my_apps[k];
							printf("\n----------------------------------------\n");
							printf("---> OPERACAO REALIZADA COM SUCESSO <---\n");
							printf("-----------------------------------------\n\n");
							contador++;
							elementos++;
							menu();

						}


				}
			else
				printf("\nQuantidade maxima de apps alcancada!!!!\n\n ");
		}
}

void imprimemat()
{
	int  j;
	if(elementos == 0)
		{
			printf("\n---> NENHUM APP NA AREA DE TRABALHO! <---\n\n\n");
			menu();
		}
	else
		{
			printf("................................................................\n");
			printf("\n                        AREA DE TRABALHO                           \n");
			printf("................................................................\n\n\n");

			for(j = 0; j < elementos; j++)
				{
					printf(".............................\n");
					printf(".                           .\n");
					printf(". %d - nome: %s            .\n", j + 1, matriz[j].nome);
					printf(". tamanho  %d kb(s)         .\n", matriz[j].tamanho);
					printf(".                           .\n");
					printf(".............................");
					printf("\n\n");
				}
		}
}

void exclumat()
{
	int i, s, k = 0, flag = 0;
	int resp;
	printf("Informe o indice do app :	");
	scanf("%d", &resp);
	for(i = 0; i < elementos; i++)
		{
			if((i + 1) == resp) //caso o indice do app existir
				{
					k = i;
					flag = 1;
					break;
				}
		}
	if(flag == 0 )
		printf("\nO aplicativo nao existe ! Tente novamente!\nInforme uma das opcoes abaixo.\n\n");
	else  //app existe
		{

			//excluir no inicio
			if(elementos == 1)  //apenas um app
				{
					elementos = 0;
					printf("\n----------------------------------------\n");
					printf("---> OPERACAO REALIZADA COM SUCESSO <---\n");
					printf("-----------------------------------------\n\n");
				}
			else
				{
					for(s = k; s < elementos; s++)
						{
							matriz[s] = matriz[s + 1];
							contador++;
						}
					elementos--;
					printf("\n----------------------------------------\n");
					printf("---> OPERACAO REALIZADA COM SUCESSO <---\n");
					printf("-----------------------------------------\n\n");
					menu();
				}
		}
}


void busca()
{
	int  a;
	printf("\n 1 - DESINSTALAR\n\n 2 - EXECUTAR\n\n 3 - FIXAR NA TELA\n\n 0 - SAIR\n\n");
	printf("Informe a opcao desejada:	");
	scanf("%d", &a);
	printf("\n");
	switch(a)
		{
		case 1:
			excluir();
			menu();
			break;
		case 2:
			executar();
			menu();
			break;
		case 3:
			copmat();
			menu();
			break;
		case 0:
			menu();
			break;
		default:
			printf("\nInforme uma opcao valida\n\n");

		}
}

void busca2()
{
	int a;
	printf("\n 1 - PARAR\n\n 0 - SAIR\n\n");
	printf("Informe a opcao desejada:	");
	scanf("%d", &a);
	printf("\n");
	switch(a)
		{
		case 1:
			excluir2();
			menu();
			break;
		case 0:
			menu();
			break;
		default:
			printf("\nInforme uma opcao valida\n\n");

		}
}

void busca3 ()
{
	int a;
	printf("\n 1 - REMOVER\n\n 0 - SAIR\n\n");
	printf("Informe a opcao desejada:	");
	scanf("%d", &a);
	printf("\n");
	switch(a)
		{
		case 1:
			exclumat();
			menu();
			break;
		case 0:
			menu();
			break;
		default:
			printf("\nInforme uma opcao valida\n\n");

		}

}

void imprime()
{
	int i;
	printf("................................................................\n");
	printf("\n                            LOJA                               \n");
	printf("................................................................\n\n\n");
	for(i = 0; i < quant_apps; i++)
		{

			printf(" %d - nome: %s \n tamanho  %dkb(s)\n\n\n", i + 1, store_apps[i].nome, store_apps[i].tamanho);
		}
}

void imprime2()
{
	int i;
	if(quant_apps_inst == 0)
		{
			printf("\n\nNENHUM APP NO BANCO DE DADOS\n\n ");
			menu();
		}
	else
		{
			printf("................................................................\n");
			printf("\n                          MEUS APPS                             \n");
			printf("................................................................\n\n\n");
			for(i = 0; i < quant_apps_inst; i++)
				{

					printf("---->  %d - Nome: %s \n	   Tamanho: %dkb(s)\n\n\n", i + 1, my_apps[i].nome, my_apps[i].tamanho);
				}
		}
}

void imprime3()
{

	int i;
	if(quant_apps_exe == 0)
		{
			printf("\n\nNENHUM APP EM EXECUCAO\n\n ");
			menu();
		}
	else
		{
			printf("................................................................\n");
			printf("\n                           EXECUTAR                              \n");
			printf("................................................................\n\n\n");
			for(i = 0; i < quant_apps_exe; i++)
				{

					printf("---->  %d - Nome: %s \n	   Tamanho: %dkb(s)\n\n\n", i + 1, run_apps[i].nome, run_apps[i].tamanho);
				}
		}
}

void menu2()
{
	int op = 1;
	printf("-------------->   Informe a opcao desejada:    \n");
	printf("\n1 - Instalar\n\n0 - Sair\n\n");
	while(op != 0)
		{
			scanf("%d", &op);
			switch(op)
				{
				case 0:
					system("cls");
					menu();
					break;
				case 1:
					instalar();
					menu();
					break;
				default:
					printf("OPCAO INVALIDA! TENTE NOVAMENTE!!\n\n");
					break;

				}
		}
}

void instalar()
{
	int i, a, p, k = 0, l = 0, fim, j;
	printf("Informe o indice do app:    ");
	scanf("%d", &a);

	//comparar
	for(i = 0; i < quant_apps; i++)
		{
			if(i + 1 == a)
				{
					k = i;//posicao
					break;
				}

		}
	//
	if(k == 0 && i != 0)
		printf("\nO aplicativo nao existe ! Tente novamente!\nInforme uma das opcoes abaixo.\n\n");
	//primeiro app instalado

	else
		{
			if(quant_apps_inst <	TAM)
				{
					if(quant_apps_inst == 0)
						{
							my_apps[0] = store_apps[k];
							printf("\n----------------------------------------\n");
							printf("---> OPERACAO REALIZADA COM SUCESSO <---\n");
							printf("-----------------------------------------\n\n");
							contador++;
							quant_apps_inst++;
						}
					else
						{
							//verifica se o app ja foi instalado anteriormente
							for(j = 0; j < quant_apps_inst; j++)
								{
									if(strcmp(my_apps[j].nome , store_apps[k].nome) == 0)
										{
											printf("\n----------------------------------------\n");
											printf("--->     O app JA FOI INSTALADO     <---\n");
											printf("----------------------------------------\n\n");
											menu();
										}
								}
							//verifica a posicao para o app ser instalado ordenado
							for(fim = 0; fim < quant_apps_inst; fim++)
								{
									if(store_apps[k].tamanho > my_apps[fim].tamanho)
										l++;
								}

							for(p = quant_apps_inst - 1 ; p >= l ; p--)
								{
									my_apps[p + 1] = my_apps[p];
									contador++;
								}
							my_apps[l] = store_apps[k];
							printf("\n----------------------------------------\n");
							printf("---> OPERACAO REALIZADA COM SUCESSO <---\n");
							printf("-----------------------------------------\n\n");
							quant_apps_inst++;
							contador++;
							menu();

						}


				}
			else
				printf("\nQuantidade maxima de apps alcancada!!!!\n\n ");
		}
}

void executar()
{
	int i, p, k = 0, l = 0, fim, j, flag = 0;
	int a;
	printf("Informe o indice do app:    ");
	scanf("%d", &a);

	for(i = 0; i < quant_apps_inst; i++)
		{
			if(i + 1 == a)
				{
					k = i;//posicao
					flag = 1;
					break;
				}

		}
	//
	if(flag == 0 )
		printf("\nO aplicativo nao existe ! Tente novamente!\nInforme uma das opcoes abaixo.\n\n");
	//primeiro app instalado

	else
		{
			if(quant_apps_exe == 0)
				{
					run_apps[0] = my_apps[k];
					printf("\n----------------------------------------\n");
					printf("---> OPERACAO REALIZADA COM SUCESSO <---\n");
					printf("-----------------------------------------\n\n");
					contador++;
					quant_apps_exe++;
				}
			else
				{
					for(j = 0; j < quant_apps_exe; j++)
						{
							if(strcmp(my_apps[k].nome , run_apps[j].nome) == 0)
								{
									printf("\n----------------------------------------\n");
									printf("--->      app  JA SENDO EXECUTADO     <---\n");
									printf("----------------------------------------\n\n");
									menu();
								}
						}
					for(fim = 0; fim < quant_apps_exe; fim++)
						{
							if(my_apps[k].tamanho > run_apps[fim].tamanho)
								l++;
						}
					for(p = quant_apps_exe - 1 ; p >= l ; p--)
						{
							run_apps[p + 1] = run_apps[p];
							contador++;
						}
					run_apps[l] = my_apps[k];
					printf("\n----------------------------------------\n");
					printf("---> OPERACAO REALIZADA COM SUCESSO <---\n");
					printf("-----------------------------------------\n\n");
					contador++;
					quant_apps_exe++;
					menu();
				}
		}
}

void excluir()
{
	int i, s, k = 0, flag = 0, j;
	int resp;
	printf("Informe o indice do app :	");
	scanf("%d", &resp);
	for(i = 0; i < quant_apps_inst; i++)
		{
			if((i + 1) == resp) //caso o indice do app existir
				{
					k = i;
					flag = 1;
					break;
				}
		}
	if(flag == 0 || (k == 0 && i != 0))
		printf("\nO aplicativo nao existe ! Tente novamente!\nInforme uma das opcoes abaixo.\n\n");
	else  //app existe
		{
			for(j = 0; j < quant_apps_exe; j++)
				{
					if(strcmp(run_apps[j].nome, my_apps[k].nome) == 0)
						{
							printf("\n\nAPP EXECUTANDO, E NECESSARIO PARA-LO PRIMEIRO\n\n");
							menu();
						}
				}
			//excluir no inicio
			if(quant_apps_inst == 1 && elementos == 1) //apenas um app
				{
					quant_apps_inst = 0;
					elementos = 0;
					printf("\n----------------------------------------\n");
					printf("---> OPERACAO REALIZADA COM SUCESSO <---\n");
					printf("-----------------------------------------\n\n");
					contador++;
				}
			else
				{
					for(s = k; s < quant_apps_inst; s++)
						{
							my_apps[s] = my_apps[s + 1];
							matriz[s] = matriz[s + 1];
							contador+=2;
						}
					quant_apps_inst--;
					elementos--;
					printf("\n----------------------------------------\n");
					printf("---> OPERACAO REALIZADA COM SUCESSO <---\n");
					printf("-----------------------------------------\n\n");
					menu();
				}
		}
}

void excluir2()
{
	int i, s, k = 0, flag = 0;
	int resp;
	printf("Informe o indice do app :	");
	scanf("%d", &resp);
	for(i = 0; i < quant_apps_exe; i++)
		{
			if((i + 1) == resp) //caso o indice do app existir
				{
					k = i;
					flag = 1;
					break;
				}
		}
	if(flag == 0)
		printf("\nO aplicativo nao existe ! Tente novamente!\nInforme uma das opcoes abaixo.\n\n");
	else  //app existe
		{
			//excluir no inicio
			if(quant_apps_exe == 1)  //apenas um app
				{
					quant_apps_exe = 0;
					printf("\n----------------------------------------\n");
					printf("---> OPERACAO REALIZADA COM SUCESSO <---\n");
					printf("-----------------------------------------\n\n");
					contador++;
				}
			else
				{
					for(s = k; s < quant_apps_exe; s++)
						{
							run_apps[s] = run_apps[s + 1];
							contador++;
						}
					quant_apps_exe--;
					printf("\n----------------------------------------\n");
					printf("---> OPERACAO REALIZADA COM SUCESSO <---\n");
					printf("-----------------------------------------\n\n");
					menu();
				}
		}
}


void menu()
{
	char op;
	printf("\n\n------------------------   MENU    ------------------------\n\n");
	printf("\n 1 - LOJA\n\n 2 - MEUS APLICATIVOS\n\n 3 - EXECUTAR\n\n 4 - AREA DE TRABALHO\n\n 0 - SAIR\n\n\nInforme uma das opcoes acima:    \n\n");

	while(op >= '1' || op <= '4')
		{
			scanf("%s", &op);
			system("cls\n\n");
			switch(op)
				{

				case '1':
					imprime();
					menu2();
					break;
				case '2':
					imprime2();
					busca();
					break;
				case '3':
					imprime3();
					busca2();
					break;
				case '4':
					imprimemat();
					busca3();
					break;
				case '0':
					printf("\n\nNumero de movimentacoes :  %d\n\n", contador);
					printf("\n==================");
					printf("-------------------------------> FIM DO PROGRAMA <------------------------------");
					printf("==================\n\n");
					exit(0);
					break;
				default:
					printf("OPCAO INVALIDA! TENTE NOVAMENTE!!\n\n");
					menu();
					break;
				}
		}
}

int main()
{
	start();
	leitura();
	menu();

	return 0;
}
