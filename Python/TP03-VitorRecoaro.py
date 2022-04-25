"""

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

"""

# A função se baseará em um vetor será formado da seguinte forma:

# - Seu tamanho é o tamanho da soma total do peso das moedas / 2 + 1.
# - Em cada índice terá um valor '0' ou '1', que significa que um sub conjunto
#   de moedas pode atingir determinado valor do índice 'i'.


from audioop import reverse


def menorDiff(moedas, tam):

    # Para facilitar o algoritmo, irá ser feito a ordenação.
    moedas.sort(reverse=True)

    somaTotal = sum(moedas)
    metadeSomaTotal = int(somaTotal / 2)

    # Declaração de vetores auxiliares.
    vetorDecisao = [False for i in range(metadeSomaTotal + 1)]
    aux = [False for i in range(metadeSomaTotal + 1)]

    # Caso base em que todo subconjunto de 'i' moedas consegue somar
    # 0, apenas não usar nenhuma moeda.
    aux[0] = True

    # Preenchimento do vetor na forma de matriz, pois para cada valor
    # 'i' teremos novas somas totais que podem ser atingidas ao somar as
    # 'i's primeiras moedas.

    for i in range(tam):

        # Colocando no vetor auxiliar as novas somas que pode ser atingida com,
        # a 'i'ésima moeda nova.
        j = 0
        while j + moedas[i] < metadeSomaTotal + 1:

            # Se o vetor decisão possui um subconjunto das 'i's primeiras moedas
            # que chega no valor 'j', então o valor 'j + moeda[i]' também pode ser alcançado.
            if vetorDecisao[j]:
                aux[j + moedas[i]] = True
            j += 1

        # Atualizando o vetor principal e resetando o vetor auxiliar.
        for j in range(metadeSomaTotal + 1):
            if aux[j]:
                vetorDecisao[j] = True
            aux[j] = False

    # Após preenchida a matriz, pode-se procurar o valor mais próximo da metade do valor
    # da soma total das moedas.
    j = metadeSomaTotal

    while j >= 0 and vetorDecisao[j] == False:
        j -= 1

    return somaTotal - (2 * j)


# Recebimento do arquivo de entrada.
file = open(input(), "r")

for linha in file.readlines():

    # Manipulando os dados de entrada.
    aux = list(map(int, linha.split()))
    tam = aux[0]

    # Critério de parada do algoritmo.
    if tam == 0:
        break

    moedas = aux[1:]

    print(menorDiff(moedas, tam))
