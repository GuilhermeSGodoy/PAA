// Nome: Guilherme Santos de Godoy
// Curso: Ciência da Computação
// RA: 758710

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Declaração dos protótipos das funções:
int contaInversoes(vector<int> vetor, int n); // Função principal que calculará a quantidade de inversões.
int buscaMaior(vector<int> vetor, int n); // Função que busca o maior valor de um vetor.
int contaMenores(int vetAux[], int k); // Efetua as somas necessárias para a obtenção do resultado.
void adicionaElemento(int vetAux[], int n, int k); // Atualiza os valores das somas do vetor auxiliar.

// Com o auxílio de outras funções, esta função calcula
// e retorna a quantidade de inversões necessárias para
// ordenar o vetor.
int contaInversoes(vector<int> vetor, int n)
{
    // Inicialização do contador que calculará
    // o resultado.
    int cont = 0;

    // Busca o maior elemento do vetor. Este valor
    // será usado para a criação de um vetor auxiliar,
    // cujo tamanho será o maior elemento adicionado de
    // um, para que, desta forma, os próprios elementos
    // possam ser usados como índices (isto será utilizado
    // futuramente para facilitar o cálculo do número
    // de inversões). São passados como parâmetros o
    // próprio vetor oringial e seu tamanho.
    int maior = buscaMaior(vetor, n);

    // Criação do vetor auxiliar com o tamanho do maior
    // elemento + 1.
    int vetAux[maior + 1];

    // Define todos os valores iniciais do vetor auxiliar
    // como 0. Isto é necessário pois eventualmente serão
    // efetuadas somas consecutivas com os valores de vetAux,
    // de modo que a inicialização com 0 deve ser feita, já
    // que é o elemento neutro da soma.
    for (int i = 0; i <= maior; i++)
        vetAux[i] = 0;

    // Percorre os valores do vetor de trás para frente, de
    // modo que serão encontradas e calculados os valores
    // que são maiores do que o elemento atual, para a
    // contabilização da quantidade de inversões necessárias
    // para que seja ordenado.
    for (int i = n - 1; i >= 0; i--)
    {
        // Chama a função que calculará, efetivamente, a quantidade
        // de elementos que são menores do que o atual, somando este
        // resultado no contador principal da função. São passados
        // como parâmetro o vetor auxiliar e o elemento atual.
        cont += contaMenores(vetAux, vetor[i]);

        // Adiciona o elemento atual ao vetAux, atualizando seus valores
        // e preparando o cálculo para a próxima iteração. São passados
        // como parâmetro o vetor auxiliar, o maior valor (obtido anteriormente
        // e referente ao tamanho do vetor auxiliar) e o valor atual, para
        // atualizar os valores do vetor auxiliar.
        adicionaElemento(vetAux, maior, vetor[i]);
    }

    // Retorna o resultado.
    return cont;
}

// Função auxiliar para encontrar o maior valor presente
// no vetor de entrada.
int buscaMaior(vector<int> vetor, int n)
{
    // Pega o valor inicial do vetor para ser
    // usado como parâmetro na comparação da
    // busca pelo maior elemento.
    int maior = vetor[0];

    // Busca e atribui o maior valor à variável
    // do resultado.
    for (int i = 0; i < n; i++)
        if (maior < vetor[i])
            maior = vetor[i];

    // Retorna o resultado.
    return maior;
}

// Esta função calcula a soma dos índices do vetor auxiliar,
// já que, a cada iteração, seus valores são atualizados em
// somas parciais e armazenados no próprio vetor auxiliar.
int contaMenores(int vetAux[], int k)
{
    // Inicializa a variável que calculará
    // o resultado.
    int valor = 0;

    // Percorre os valores de vetAux.
    while (k > 0)
    {
        // Soma o valor atual do vetor auxiliar à
        // variável valor, efetuando as somas consecutivas
        // que obterão o resultado.
        valor += vetAux[k];

        // Move o valor de k para o próximo. Isso é feito
        // a partir da manipulação dos endereços de cada
        // índice, a partir da utilização do operador &.
        // Esta operação foi utilizada desta maneira como
        // uma forma de simplificar o código e preservar
        // estes valores ao longo da execução do while.
        k -= k & (-k);
    }

    // Retorna o resultado.
    return valor;
}

// Esta função atualiza os valores de cada índice do vetor auxiliar
// em cada iteração, além de atualizar a posição de k para seguir
// com as devidas somas.
void adicionaElemento(int vetAux[], int n, int k)
{
    // Percorre o vetor auxiliar para atualizar os valores
    // referentes à cada índice.
    while (k <= n)
    {
        // Acrescenta 1 a cada iteração. Isso é feito pois, a cada
        // chamada da função e loop do while, é feita a comparação
        // com os outros valores presentes no vetor, de modo que é
        // calculada a quantidade de inversões que devem ser feitas
        // para ordenar o referido vetor, atualizando-os constantemente
        // para cada execução do laço.
        vetAux[k]++;

        // Utilizando o mesmo método da função anterior,
        // move o valor de k para o próximo. Isso é feito
        // a partir da manipulação dos endereços de cada
        // índice, a partir da utilização do operador &.
        // Esta operação foi utilizada desta maneira como
        // uma forma de simplificar o código e preservar
        // estes valores ao longo da execução do while.
        k += k & (-k);
    }
}

int main()
{
    // Abrindo o arquivo.
    ifstream arq;

    char nomeArquivo[5];
    cin >> nomeArquivo;

    arq.open(nomeArquivo);

    if (!arq)
        exit(1);

    // Variável que lê os valores do arquivo.
    int c;

    // Vetor usado para armazenar os valores lidos.
    vector<int> vetor;

    // Variável que será utilizada para armazenar a
    // quantidade de inversões.
    int cont;

    // Variável que será utilizada para armazenar o tamanho
    // de cada entrada.
    unsigned long int tamanho;

    // Flag que será utilizada para verificar se o primeiro
    // valor de cada entrada já foi lido.
    bool vazio = true;

    // Loop para percorrer o arquivo.
    while (!arq.eof())
    {
        // Lê um valor de cada vez.
        arq >> c;

        // Caso seja o primeiro valor, referente
        // ao tamanho, entra neste if para ler
        // o valor do tamanho e armazenar em uma
        // variável.
        if (vazio)
        {
            tamanho = c;

            // Impede o programa de entrar neste if
            // novamente, pois já armazenou o tamanho.
            vazio = false;

            // Lê o próximo valor.
            arq >> c;
        }

        // Coloca cada valor em um vetor.
        vetor.push_back(c);

        // Verifica se já leu todos os valores.
        if (tamanho == vetor.size())
        {
            // Chama a função que calcula a quantidade de
            // inversões necessárias para ordenar o vetor.
            cont = contaInversoes(vetor, vetor.size());

            // Verifica o vencedor de cada rodada.
            if (cont % 2 != 0)
                printf("Jake\n");
            else
                printf("Finn\n");

            // Desaloca e reinicializa o vetor.
            vetor.clear();

            // Define a flag como true, para que, na próxima
            // leitura, o valor do tamanho seja devidamente
            // armazenado.
            vazio = true;
        }
    }

    // Fecha o arquivo e encerra o programa
    arq.close();

    return 0;
}
