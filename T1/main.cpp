// Nome: Guilherme Santos de Godoy
// Curso: Ci�ncia da Computa��o
// RA: 758710

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Declara��o dos prot�tipos das fun��es:
int contaInversoes(vector<int> vetor, int n); // Fun��o principal que calcular� a quantidade de invers�es.
int buscaMaior(vector<int> vetor, int n); // Fun��o que busca o maior valor de um vetor.
int contaMenores(int vetAux[], int k); // Efetua as somas necess�rias para a obten��o do resultado.
void adicionaElemento(int vetAux[], int n, int k); // Atualiza os valores das somas do vetor auxiliar.

// Com o aux�lio de outras fun��es, esta fun��o calcula
// e retorna a quantidade de invers�es necess�rias para
// ordenar o vetor.
int contaInversoes(vector<int> vetor, int n)
{
    // Inicializa��o do contador que calcular�
    // o resultado.
    int cont = 0;

    // Busca o maior elemento do vetor. Este valor
    // ser� usado para a cria��o de um vetor auxiliar,
    // cujo tamanho ser� o maior elemento adicionado de
    // um, para que, desta forma, os pr�prios elementos
    // possam ser usados como �ndices (isto ser� utilizado
    // futuramente para facilitar o c�lculo do n�mero
    // de invers�es). S�o passados como par�metros o
    // pr�prio vetor oringial e seu tamanho.
    int maior = buscaMaior(vetor, n);

    // Cria��o do vetor auxiliar com o tamanho do maior
    // elemento + 1.
    int vetAux[maior + 1];

    // Define todos os valores iniciais do vetor auxiliar
    // como 0. Isto � necess�rio pois eventualmente ser�o
    // efetuadas somas consecutivas com os valores de vetAux,
    // de modo que a inicializa��o com 0 deve ser feita, j�
    // que � o elemento neutro da soma.
    for (int i = 0; i <= maior; i++)
        vetAux[i] = 0;

    // Percorre os valores do vetor de tr�s para frente, de
    // modo que ser�o encontradas e calculados os valores
    // que s�o maiores do que o elemento atual, para a
    // contabiliza��o da quantidade de invers�es necess�rias
    // para que seja ordenado.
    for (int i = n - 1; i >= 0; i--)
    {
        // Chama a fun��o que calcular�, efetivamente, a quantidade
        // de elementos que s�o menores do que o atual, somando este
        // resultado no contador principal da fun��o. S�o passados
        // como par�metro o vetor auxiliar e o elemento atual.
        cont += contaMenores(vetAux, vetor[i]);

        // Adiciona o elemento atual ao vetAux, atualizando seus valores
        // e preparando o c�lculo para a pr�xima itera��o. S�o passados
        // como par�metro o vetor auxiliar, o maior valor (obtido anteriormente
        // e referente ao tamanho do vetor auxiliar) e o valor atual, para
        // atualizar os valores do vetor auxiliar.
        adicionaElemento(vetAux, maior, vetor[i]);
    }

    // Retorna o resultado.
    return cont;
}

// Fun��o auxiliar para encontrar o maior valor presente
// no vetor de entrada.
int buscaMaior(vector<int> vetor, int n)
{
    // Pega o valor inicial do vetor para ser
    // usado como par�metro na compara��o da
    // busca pelo maior elemento.
    int maior = vetor[0];

    // Busca e atribui o maior valor � vari�vel
    // do resultado.
    for (int i = 0; i < n; i++)
        if (maior < vetor[i])
            maior = vetor[i];

    // Retorna o resultado.
    return maior;
}

// Esta fun��o calcula a soma dos �ndices do vetor auxiliar,
// j� que, a cada itera��o, seus valores s�o atualizados em
// somas parciais e armazenados no pr�prio vetor auxiliar.
int contaMenores(int vetAux[], int k)
{
    // Inicializa a vari�vel que calcular�
    // o resultado.
    int valor = 0;

    // Percorre os valores de vetAux.
    while (k > 0)
    {
        // Soma o valor atual do vetor auxiliar �
        // vari�vel valor, efetuando as somas consecutivas
        // que obter�o o resultado.
        valor += vetAux[k];

        // Move o valor de k para o pr�ximo. Isso � feito
        // a partir da manipula��o dos endere�os de cada
        // �ndice, a partir da utiliza��o do operador &.
        // Esta opera��o foi utilizada desta maneira como
        // uma forma de simplificar o c�digo e preservar
        // estes valores ao longo da execu��o do while.
        k -= k & (-k);
    }

    // Retorna o resultado.
    return valor;
}

// Esta fun��o atualiza os valores de cada �ndice do vetor auxiliar
// em cada itera��o, al�m de atualizar a posi��o de k para seguir
// com as devidas somas.
void adicionaElemento(int vetAux[], int n, int k)
{
    // Percorre o vetor auxiliar para atualizar os valores
    // referentes � cada �ndice.
    while (k <= n)
    {
        // Acrescenta 1 a cada itera��o. Isso � feito pois, a cada
        // chamada da fun��o e loop do while, � feita a compara��o
        // com os outros valores presentes no vetor, de modo que �
        // calculada a quantidade de invers�es que devem ser feitas
        // para ordenar o referido vetor, atualizando-os constantemente
        // para cada execu��o do la�o.
        vetAux[k]++;

        // Utilizando o mesmo m�todo da fun��o anterior,
        // move o valor de k para o pr�ximo. Isso � feito
        // a partir da manipula��o dos endere�os de cada
        // �ndice, a partir da utiliza��o do operador &.
        // Esta opera��o foi utilizada desta maneira como
        // uma forma de simplificar o c�digo e preservar
        // estes valores ao longo da execu��o do while.
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

    // Vari�vel que l� os valores do arquivo.
    int c;

    // Vetor usado para armazenar os valores lidos.
    vector<int> vetor;

    // Vari�vel que ser� utilizada para armazenar a
    // quantidade de invers�es.
    int cont;

    // Vari�vel que ser� utilizada para armazenar o tamanho
    // de cada entrada.
    unsigned long int tamanho;

    // Flag que ser� utilizada para verificar se o primeiro
    // valor de cada entrada j� foi lido.
    bool vazio = true;

    // Loop para percorrer o arquivo.
    while (!arq.eof())
    {
        // L� um valor de cada vez.
        arq >> c;

        // Caso seja o primeiro valor, referente
        // ao tamanho, entra neste if para ler
        // o valor do tamanho e armazenar em uma
        // vari�vel.
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

        // Verifica se j� leu todos os valores.
        if (tamanho == vetor.size())
        {
            // Chama a fun��o que calcula a quantidade de
            // invers�es necess�rias para ordenar o vetor.
            cont = contaInversoes(vetor, vetor.size());

            // Verifica o vencedor de cada rodada.
            if (cont % 2 != 0)
                printf("Jake\n");
            else
                printf("Finn\n");

            // Desaloca e reinicializa o vetor.
            vetor.clear();

            // Define a flag como true, para que, na pr�xima
            // leitura, o valor do tamanho seja devidamente
            // armazenado.
            vazio = true;
        }
    }

    // Fecha o arquivo e encerra o programa
    arq.close();

    return 0;
}
