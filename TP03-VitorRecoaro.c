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

/*
A função se baseará em um vetor será formado da seguinte forma:

- Seu tamanho é o tamanho da soma total do peso das moedas / 2 + 1.
- Em cada índice terá um valor '0' ou '1', que significa que um sub conjunto
  de moedas pode atingir determinado valor do índice 'i'.

*/
int menorDiff(int *moedas, int tam)
{
    int menorDiff;
    long int somaTotal = 0;
    int i, j;

    for (i = 0; i < tam; i++)
        somaTotal += moedas[i];

    int vetorDecisao[(somaTotal / 2) + 1], aux[(somaTotal / 2) + 1];

    // Inicializando os vetores
    for (i = 0; i < (somaTotal / 2) + 1; i++)
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
    for (i = 0; i <= tam; i++)
    {
        // Colocando no vetor auxiliar as novas somas que pode ser atingida com,
        // a 'i'ésima moeda nova.
        for (j = 0; j + moedas[i] < (somaTotal / 2) + 1; j++)
        {
            // Se o vetor decisão possui um subconjunto das 'i's primeiras moedas
            // que chega no valor 'j', então o valor 'j + moeda[i]' também pode ser alcançado.
            if (vetorDecisao[j])
                aux[j + moedas[i]] = 1;
        }
        // Atualizando o vetor principal e resetando o vetor auxiliar.
        for (j = 0; j < (somaTotal / 2) + 1; j++)
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