#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int menuTipo()
{
	int cont = 1;

	do
	{
		printf("\n\tAlgoritmo:\n\n");
		printf("[1] Insertion Sort\n");

		scanf("%d", &cont);
		system("cls || clear");

		switch (cont)
		{
		case 1:
			return 1;
			break;

		case 0:
			return 0;
			break;

		default:
			printf("Digite uma opcao valida\n");
		}
	} while (cont);
	return 0;
}

int menuOrdem()
{
	int cont = 1;

	do
	{
		printf("\n\tEscolha a ordem:\n\n");
		printf("[1] Crescente\n");
		printf("[2] Decrescente\n");
		printf("[3] Randomica\n");

		printf("[0] Sair\n");

		scanf("%d", &cont);
		system("cls || clear");

		switch (cont)
		{
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		case 3:
			return 3;
			break;

		case 0:
			return 0;
			break;

		default:
			printf("Digite uma opcao valida\n");
		}
	} while (cont);
	return 0;
}

int menuTamanho()
{
	int cont = 1;

	do
	{
		printf("\n\tEscolha o tamanho:\n\n");
		printf("[1] 10\n");
		printf("[2] 100\n");
		printf("[3] 1000\n");
		printf("[4] 10000\n");
		printf("[5] 100000\n");
		printf("[6] 1000000\n\n");

		printf("[0] Sair\n");

		scanf("%d", &cont);
		system("cls || clear");

		switch (cont)
		{
		case 1:
			return 10;
			break;
		case 2:
			return 100;
			break;
		case 3:
			return 1000;
			break;
		case 4:
			return 10000;
			break;
		case 5:
			return 100000;
			break;
		case 6:
			return 1000000;
			break;
		case 0:
			return 0;
			break;

		default:
			printf("Digite uma opcao valida\n");
		}
	} while (cont);
	return 0;
}

void gravarArquivoSaida(int *vetor, int tamanho)
{
	int i = 0;
	FILE *pont_arq;

	// Abra o arquivo para escrita
	pont_arq = fopen("/home/alexandre-bertulino/InsertionSort/ArquivosdeSaida/saidaordenada.txt", "w");
	if (pont_arq == NULL)
	{
		printf("Erro ao abrir o arquivo de saída.\n");
		return;
	}

	// Escreva o tamanho do vetor no arquivo
	fprintf(pont_arq, "%d\n", tamanho);

	// Escreva os elementos do vetor no arquivo
	for (i = 0; i < tamanho; i++)
	{
		fprintf(pont_arq, "%d\n", vetor[i]);
	}

	// Feche o arquivo
	fclose(pont_arq);
}


void gravarTempo(float time_spent)
{
	FILE *pont_arq;
	pont_arq = fopen("/home/alexandre-bertulino/InsertionSort/ArquivosdeTempo/tempogasto.txt", "w");
	fprintf(pont_arq, "%f segundos.", time_spent);
	printf("Sucesso!!!\nTempo gasto em segundos: %f \n", time_spent);
	fclose(pont_arq);

}
void insertionSort(int vetor[], int tamanho)
{
	int i, key, j;

	double time_spent = 0.0;

	clock_t begin = clock();

	for (i = 1; i < tamanho; i++)
	{
		key = vetor[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		  greater than key, to one position ahead
		  of their current position */
		while (j >= 0 && vetor[j] > key)
		{
			vetor[j + 1] = vetor[j];
			j = j - 1;
		}
		vetor[j + 1] = key;
	}

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	gravarArquivoSaida(&vetor[0], tamanho);
	gravarTempo(time_spent);
}

void gravarArquivoEntrada(int *vetor, int tamanho, char *caminho)
{
	int i = 0;
	FILE *pont_arq;

	// Classifique o vetor antes de gravar
	insertionSort(vetor, tamanho);

	pont_arq = fopen(caminho, "w");
	if (pont_arq == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		return;
	}

	fprintf(pont_arq, "%d\n", tamanho);
	for (i = 0; i < tamanho; i++)
	{
		fprintf(pont_arq, "%d\n", vetor[i]);
	}
	fclose(pont_arq);
}


void criarEntradaCrescente(char *caminho, int tamanho)
{
	int i;

	int vetor[tamanho];

	for (i = 0; i < tamanho; i++)
	{
		vetor[i] = i + 1;
	}

	printf("Colocando em ordem, aguarde...\n");

	gravarArquivoEntrada(&vetor[0], tamanho, &caminho[0]);
}

void criarEntradaDecrescente(char *caminho, int tamanho)
{
	int i, j;
	j = 0;

	int vetor[tamanho];

	for (i = 0; i < tamanho; i++)
	{
		vetor[j] = i - 1;
	}

	printf("Colocando em ordem, aguarde...\n");

	gravarArquivoEntrada(&vetor[0], tamanho, &caminho[0]);
}

void criarEntradaRandomica(char *caminho, int tamanho)
{
	int i;
	int vetor[tamanho];

	srand(time(NULL));

	for (i = 0; i < tamanho; i++)
	{
		vetor[i] = rand();
	}

	printf("Colocando em ordem, aguarde...\n");

	gravarArquivoEntrada(&vetor[0], tamanho, &caminho[0]);
}

void escolherEntrada(int tipo, int ordem, int tamanho)
{
	char caminho[80];

	if (ordem == 1 && tipo == 1)
	{
		sprintf(caminho, "/home/alexandre-bertulino/InsertionSort/ArquivosdeEntrada/Crescente/entradacrescente%d.txt", tamanho);
		criarEntradaCrescente(&caminho[0], tamanho);
	}

	if (ordem == 2 && tipo == 1)
	{
		sprintf(caminho, "/home/alexandre-bertulino/InsertionSort/ArquivosdeEntrada/Decrescente/entradadecrescente%d.txt", tamanho);
		criarEntradaDecrescente(&caminho[0], tamanho);
	}

	if (ordem == 3 && tipo == 1)
	{
		sprintf(caminho, "/home/alexandre-bertulino/InsertionSort/ArquivosdeEntrada/Random/entradarandomica%d.txt", tamanho);
		criarEntradaRandomica(&caminho[0], tamanho);
	}
}

int main(void)
{
	int tipo, ordem, tamanho;

	tipo = menuTipo();

	if (tipo == 0)
	{
		printf("FIM!");
		return 0;
	}

	ordem = menuOrdem();

	if (ordem == 0)
	{
		printf("FIM!");
		return 0;
	}

	tamanho = menuTamanho();
	if (tamanho == 0)
	{
		printf("FIM!");
		return 0;
	}

	escolherEntrada(tipo, ordem, tamanho);
	
	return 0;
}