/*

UFSCAR - PAA - Trabalho prático 03 - ENPE 2021.2

Aluno: Vitor de Almeida Recoaro.
RA: 790035.
Curso: BCC - Bacharelado em Ciência da Computação.

--------------------------RESUMO TRABALHO----------------------------
Esse problema não é sobre o Silvio Santos. Ele é sobre o Henrico e o Frederico,
que agora estão ricos. Acontece que eles foram para Praia Grande na baixada santista e,
cavando um buraco na areia, acharam um ba ́u do tesouro.

Esse ba ́u continha moedas de ouro, que valem mais que dinheiro, de pesos diferentes.
Quanto mais pesada uma moeda, maior o seu valor.

Não sabendo muito bem o que fazer com esse ouro todo, eles decidiram primeiro dividir
as moedas de forma justa e depois cada um decidia o que queria fazer com seu próprio
dinheiro. Porém, eles não sabem muito bem como fazer isso. O que eles querem é que,
dado o peso em gramas de todas as moedas encontradas, você os ajude a encontrar qual
e a menor diferença entre a quantidade de ouro para cada um deles após distribuir as moedas.
---------------------------------------------------------------------

*/

#include <stdio.h>
#include <stdlib.h>

// Funções para ordenação.
void mergeSort(int *, int, int);

void intercala(int *, int, int, int);

int menorDiff(int *, int);

int main()
{
    char nomeArquivo[100];

    scanf("%s", nomeArquivo);

    FILE *arq = fopen(nomeArquivo, "r");
    int numMoedas;

    // Loop para ler cada caso teste.
    fscanf(arq, "%d", &numMoedas);

    while (numMoedas != 0)
    {
        int i;
        int pesoMoeda[numMoedas];

        for (i = 0; i < numMoedas; i++)
        {
            fscanf(arq, " %d", &pesoMoeda[i]);
        }

        printf("%d\n", menorDiff(pesoMoeda, numMoedas));
        fscanf(arq, "%d", &numMoedas);
    }

    fclose(arq);
}

// Funções de ordenação.
void mergeSort(int *v, int inic, int fim)
{
    int meio = (fim + inic) / 2;
    if (inic < fim - 1)
    {
        mergeSort(v, inic, meio);
        mergeSort(v, meio, fim);
        intercala(v, inic, meio, fim);
    }
}

void intercala(int *v, int inic, int meio, int fim)
{
    // Vetor para auxiliar a ordenação.
    int *w = (int *)malloc((fim - inic) * sizeof(int));

    // "i" varrerá do início até o meio, e "j" do meio até o fim, aux será o auxiliar
    // para ajeitar os valores no vetor "w".
    int i = inic, j = meio, aux = 0;

    while (i < meio && j < fim)
    {
        if (v[i] > v[j])
            w[aux++] = v[i++];
        else
            w[aux++] = v[j++];
    }

    // Se o "j" já atingiu o fim, mas o "i" não varreu todo o seu espaço, percorra copiando.
    while (i < meio)
        w[aux++] = v[i++];

    // Se o "i" já atingiu o fim, mas o "j" não varreu todo o seu espaço, percorra copiando.
    while (j < fim)
        w[aux++] = v[j++];

    // Muda o vetor original, baseado no vetor auxiliar.
    for (aux = 0; aux < (fim - inic); aux++)
        v[inic + aux] = w[aux];
    free(w);
}

/*
A função se baseará em um vetor será formado da seguinte forma:

- Seu tamanho é o tamanho da soma total do peso das moedas / 2 + 1.
- Em cada índice terá um valor '0' ou '1', que significa que um sub conjunto
  de moedas pode atingir determinado valor do índice 'i'.

*/
int menorDiff(int *moedas, int tam)
{
    int menorDiff;
    long int somaTotal = 0, metadeSomaTotal;
    int i, j;

    // Para facilitar o algoritmo será feita a ordenação das moedas.
    mergeSort(moedas, 0, tam);

    for (i = 0; i < tam; i++)
        somaTotal += moedas[i];

    metadeSomaTotal = (int)(somaTotal / 2) + 1;
    int *vetorDecisao, *aux;

    vetorDecisao = malloc(metadeSomaTotal * sizeof(int));

    aux = malloc(metadeSomaTotal * sizeof(int));

    // Se a alocação de memória não foi feita com sucesso retorna -1.
    if (vetorDecisao == NULL || aux == NULL)
        return -1;

    // Inicializando os vetores
    for (i = 0; i < metadeSomaTotal; i++)
    {
        aux[i] = 0;
        vetorDecisao[i] = 0;
    }

    // Caso base em que todo subconjunto de 'i' moedas consegue somar
    // 0, apenas não usar nenhuma moeda.
    aux[0] = 1;

    // Preenchimento do vetor na forma de matriz, pois para cada valor
    // 'i' teremos novas somas totais que podem ser atingidas ao somar as
    //  'i's primeiras moedas.
    for (i = 0; i < tam; i++)
    {
        // Colocando no vetor auxiliar as novas somas que pode ser atingida com,
        // a 'i'ésima moeda nova.
        for (j = 0; j + moedas[i] < metadeSomaTotal; j++)
        {
            // Se o vetor decisão possui um subconjunto das 'i's primeiras moedas
            // que chega no valor 'j', então o valor 'j + moeda[i]' também pode ser alcançado.
            if (vetorDecisao[j])
                aux[j + moedas[i]] = 1;
        }
        // Atualizando o vetor principal e resetando o vetor auxiliar.
        for (j = 0; j < metadeSomaTotal; j++)
        {
            if (aux[j])
                vetorDecisao[j] = 1;
            aux[j] = 0;
        }
    }

    // Após preenchida a matriz, pode-se procurar o valor mais próximo da metade do valor
    // da soma total das moedas.
    j = (int)somaTotal / 2;
    while (j >= 0 && vetorDecisao[j] != 1)
        j--;

    menorDiff = somaTotal - (2 * j);
    return menorDiff;
}