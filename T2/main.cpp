// Nome: Guilherme Santos de Godoy
// Curso: Ci�ncia da Computa��o
// RA: 758710

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
    // Abrindo o arquivo.
    ifstream arq;

    char nomeArquivo[5];
    cin >> nomeArquivo;

    arq.open(nomeArquivo);

    if (!arq)
        exit(1);

    // Vari�vel que l� os valores do arquivo.
    int c;

    // Vetor usado para armazenar os valores lidos.
    vector<int> vetor;

    // Contador auxiliar para calcular a
    // quantidade de entradas.
    unsigned long int contAux = 0;

    // Var�avel usada para ler a quantidade
    // de entradas do arquivo.
    unsigned long int tamanho = 0;

    // Flag usada para verificar se o primeiro valor
    // do arquivo, o tamanho, j� foi lido.
    bool vazio = true;

    // Valor do desconto.
    unsigned long int valor = 0;

    // Loop para percorrer o arquivo.
    while (!arq.eof())
    {
        // L� um valor de cada vez.
        arq >> c;

        // Caso seja o primeiro valor, referente
        // ao tamanho, entra neste if para ler
        // o valor do tamanho e armazenar em uma
        // var�avel.
        if (vazio)
        {
            tamanho = c;

            // Impede o programa de entrar neste if
            // novamente, pois j� armazenou o tamanho.
            vazio = false;

            // L� o pr�ximo valor.
            arq >> c;
        }

        // Coloca cada valor em um vetor.
        vetor.push_back(c);

        // Incrementa o contador auxiliar.
        contAux++;

        // Verifica se j� leu todos os valores.
        if (contAux == tamanho)
        {
            // Ordena o vetor em ordem decrescente.
            std::sort(std::begin(vetor), std::end(vetor), std::greater<>());

            // Percorre o vetor para localizar os valores
            // referentes aos descontos.
            for (unsigned long int i = 0; i < tamanho; i++)
            {
                // Sempre que encontrar um m�ltiplo de tr�s,
                // j� que os produtos s�o comprados em grupos de
                // tr�s, incrementa o valor referente � soma do
                // desconto. Esta l�gica funciona pois os valores
                // est�o em ordem decrescente, de modo que ser�
                // poss�vel obter os maiores valores de desconto a
                // cada compra.
                if ((i + 1) % 3 == 0)
                    valor += vetor[i];
            }

            // Exibe o valor do desconto.
            printf("%lu\n", valor);
        }

    }

    // Fecha o arquivo e encerra o programa.
    arq.close();

    return 0;
}
