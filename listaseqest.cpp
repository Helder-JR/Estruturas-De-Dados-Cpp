#include <iostream>
#include <iomanip>
#include <string>
#include <locale>

// Tamanho máximo que a lista pode ter, pois é estática.
#define MAX 100

using namespace std;

// TAD da lista, pode ser substituído por outra struct.
struct Aluno
{
    string nome;
    int matricula;
    float n1, n2, n3;
};

// A lista em si. Possui o tamanho e um array do tipo do TAD utilizado.
struct Lista
{
    int tamanho;
    Aluno dados[MAX];
};

// Protótipos das funções a serem adicionados posteriormente em um header.
Lista* nova_lista();
void del_lista(Lista *li);
int tam_lista(Lista *li);
int lista_cheia(Lista *li);
int lista_vazia(Lista *li);
int insere_inicio(Lista *li, Aluno al);
int insere_final(Lista *li, Aluno al);
int insere_pos(Lista *li, Aluno al, int pos);
int insere_ord(Lista *li, Aluno al);
int remove_inicio(Lista *li);
int remove_final(Lista *li);
int remove_pos(Lista *li, int pos);
int remove_mat(Lista *li, int mat);
int consulta_pos(Lista *li, Aluno *al, int pos);
int consulta_mat(Lista *li, Aluno *al, int mat);
int imprime_lista(Lista *li);

// Função principal.
int main()
{
    setlocale(LC_ALL, "");

    Aluno estudante;
    Lista *lista = nova_lista();
    int qtd;

    cout << "Digite a quantidade de itens a serem inseridos: ";
    cin >> qtd;
    cout << endl;
    cout << "---------------------------------------------------" << endl;
    for (int i = 0; i < qtd; i++)
    {
        cin.ignore();
        cout << "Digite o nome do aluno: ";
        getline(cin, estudante.nome);
        cout << "Digite a matricula do aluno: ";
        cin >> estudante.matricula;
        cout << "Digite as três notas do aluno: ";
        cin >> estudante.n1 >> estudante.n2 >> estudante.n3;
        insere_final(lista, estudante);
        cout << "---------------------------------------------------" << endl;
    }
    imprime_lista(lista);

    return 0;
}

// Função que cria uma nova lista e retorna um ponteiro para o seu endereço. Primeiro
// é criada uma variável ponteiro do tipo lista através de alocação dinâmica, então
// há a verificação se essa variável realmente foi alocada. Caso positivo o tamanho
// dessa lista criada é "setado" para zero, indicando que está vazia e a função irá
// retornar o endereço dessa lista criada.
Lista* nova_lista()
{
    Lista *li = new Lista;
    if (li != NULL)
    {
        li -> tamanho = 0;
    }
    return li;
}

// Deleta a lista que foi criada, utilizando um comando de C++. Em C pode ser
// substituído pelo comando free() da stdlib.h.
void del_lista(Lista *li)
{
    delete li;
}

// Função que retorna o valor da lista. Caso a lista não tenha sido criada
// o valor de retorno será -1.
int tam_lista(Lista *li)
{
    if (li == NULL)
    {
        return -1;
    }
    else
    {
        return li -> tamanho;
    }
}

// Função que checa se a lista está cheia, tendo como retorno 1 caso verdadeiro,
// 0 caso falso ou -1 caso a lista não exista/esteja alocada.
int lista_cheia(Lista *li)
{
    if (li == NULL)
    {
        return -1;
    }
    else
    {
        return li -> tamanho == MAX;
    }
}

// Função que checa se a lista está vazia, tendo como retorno 1 caso verdadeiro,
// 0 caso falso ou -1 caso a lista não exista/esteja alocada.
int lista_vazia(Lista *li)
{
    if (li == NULL)
    {
        return -1;
    }
    else
    {
        return li -> tamanho == 0;
    }
}

// Insere um elemento na lista (ambos passados como parâmetros) na PRIMEIRA
// posição.
// Primeiro é testada se a lista está alocada e não está cheia, então o
// elemento é inserido na primeira posição (referente ao índice 0). Caso tais
// condições não sejam satisfeitas a função retorna 0.
// A inserção é inicialmente realizada avançando todos os elementos uma
// posição, a partir do último até o primeiro, até que o primeiro índice do
// array de dados fique duplicado, e então o elemento é inserido nessa posição.
//
// Inserindo 9 (o char underscore (_) representa índice sem valor especificado):
//
// início  0 3 5 2 4 8 1 7 6 _
// avanço  0 0 3 5 2 4 8 1 7 6
// final   9 0 3 5 2 4 8 1 7 6
//
// Após isso o tamanho da lista é incrementado e a função retorna o valor 1.
int insere_inicio(Lista *li, Aluno al)
{
    if (li == NULL || lista_cheia(li))
    {
        return 0;
    }
    else
    {
        for (int i = (li -> tamanho) - 1; i >= 0; i--)
        {
            li -> dados[i + 1] = li -> dados[i];
        }
        li -> dados[0] = al;
        li -> tamanho++;
        return 1;
    }
}

// Insere um elemento na lista (ambos passados como parâmetro) na ÚLTIMA
// posição.
// Primeiro é testada se a lista está alocada e não está cheia, então o
// elemento é inserido na última posição (referente ao tamanho atual da lista).
// Por exemplo, caso o tamanho atual da lista seja 3 (referente ao índice 2),
// o elemento vai ser inserido no índice 3, que por acaso é o próximo índice
// vazio (tamanho 4).
//
// indice  0 1 2 3 4 5 ...
// tamanho 1 2 3 4 5 6 ...
//
// Então o tamanho da lista é incrementado e a função retorna 1.
int insere_final(Lista *li, Aluno al)
{
    if (li == NULL || lista_cheia(li))
    {
        return 0;
    }
    else
    {
        li -> dados[li -> tamanho] = al;
        li -> tamanho++;
        return 1;
    }
}

// Semelhante a função insere_inicio(), porém com a adição de um argumento,
// que corresponde a posição em que o elemento será inserido. Essa posição
// entra na condição do for, bem como no índice do elemento a ser inserido.
int insere_pos(Lista *li, Aluno al, int pos)
{
    if (li == NULL || lista_cheia(li) || pos < 0 || pos >= (li -> tamanho))
    {
        return 0;
    }
    else
    {
        for (int i = (li -> tamanho) - 1; i >= pos; i--)
        {
            li -> dados[i + 1] = li -> dados[i];
        }
        li -> dados[pos] = al;
        li -> tamanho++;
        return 1;
    }
}

// Insere cada elemento na lista de maneira ordenada (nesse caso o critério é a
// matrícula). Primeiro é feita a verificação se a lista está alocada e não está
// cheia. Então há um loop que vai procurar a posição em que o elemento será 
// inserido. Caso a lista não chegue ao fim e a matrícula no índice atual seja menor
// que a do elemento a ser inserido o loop continua. Após descobrir a posição que o
// elemento será inserido há outro laço que percorrerá a lista de trás para frente,
// deslocando cada elemento para o índice seguinte, até a posição em que o elemento
// a ser inserido esteja vaga. Após a inserção o tamanho da lista é incrementado e a
// função retorna 1, indicando que tudo ocorreu corretamente.
int insere_ord(Lista *li, Aluno al)
{
    int i = 0, k;

    if (li == NULL || lista_cheia(li))
    {
        return 0;
    }
    else
    {
        while (i < li -> tamanho && li -> dados[i].matricula < al.matricula)
        {
            i++;
        }
        for (k = (li -> tamanho) - 1; k >= i; k--)
        {
            li -> dados[k + 1] = li -> dados[k];
        }
        li -> dados[i] = al;
        li -> tamanho++;
        return 1;
    }
}

// Remove um elemento do início da lista atráves de um loop em que cada elemento da 
// posição i tem seu conteúdo sobrescrito pelo elemento da posição i + 1. Para isso
// a função primeiramente verifica através de uma condição se a lista está alocada e
// não está vazia (caso isso aconteça a função retorna 0). É então executado um laço
// que percorre a lista do primeiro até o penúltimo elemento, onde cada elemento da
// lista recebe os dados do próximo elemento. O laço é executado dessa maneira (até
// o penúltimo elemento) para que não haja erro de indexação quando o iterador chegar
// no último elemento, que teoricamente teria de receber os dados do elemento de um
// índice fora da quantidade armazenada na lista.
int remove_inicio(Lista *li)
{
    if (li == NULL || lista_vazia(li))
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < (li -> tamanho) - 1; i++)
        {
            li -> dados[i] = li -> dados[i + 1];
        }
        li -> tamanho--;
        return 1;
    }
}

// Função que remove um elemento do fim da lista. Há a verificação se a lista está
// alocada e não está vazia, caso positivo o tamanho da lista é decrementado, ocasionando
// a sobrescrita do elemento na última posição quando algum outro elemento for inserido.
int remove_final(Lista *li)
{
    if (li == NULL || lista_vazia(li))
    {
        return 0;
    }
    else
    {
        li -> tamanho--;
        return 1;
    }
}

// Remove um elemento a partir de uma posição passada como parâmetro. Primeiro é feira a
// verificação se a lista está alocada e não está vazia, além de a posição a ser removida
// não ser menor do que 0 ou maior ou igual a o tamanho atual da lista, o que geraria um
// erro de indexação e faria com que a função retornasse o valor 0. Caso não haja esse
// retorno, então será executado um laço que a partir da posição especificada a ser removida
// fará com que todos os dados da lista na posição i tenham seus dados sobrescritos pelos
// elementos na posição i + 1, processo semelhante a remoção pelo início da lista.
int remove_pos(Lista *li, int pos)
{
    if (li == NULL || lista_vazia(li) || pos < 0 || pos >= (li -> tamanho))
    {
        return 0;
    }
    else
    {
        for (int i = pos; i < (li -> tamanho) - 1; i++)
        {
            li -> dados[i] = li -> dados[i + 1];
        }
        li -> tamanho--;
        return 1;
    }
}

// Função que remove um elemento de uma lista através do número de matrícula. Primeiro é
// verificada se a lista está alocada e não está vazia. Então há um laço que percorre a
// lista com condição de o iterador não chegar no fim da lista e a matrícula do elemento
// atual ser diferente da matrícula do elemento que será removido. Caso o iterador chegue
// fim da lista a função retorna 0. Caso a matrícula do aluno que vai ser removida seja 
// encontrada será executado outro laço, que dessa vez terá início a partir do índice que
// será removido. O processo é semelhante a remoção pelo início da lista, com a diferença
// de a iteração iniciar pelo índice do elemento que será removido.
int remove_mat(Lista *li, int mat)
{
    int i = 0, k;

    if (li == NULL || lista_vazia(li))
    {
        return 0;
    }
    else
    {
        while (i < li -> tamanho && li ->dados[i].matricula != mat)
        {
            i++;
        }
        if (i == li -> tamanho)
        {
            return 0;
        }
        else
        {
            for (k = i; k < (li -> tamanho) - 1; k++)
            {
                li -> dados[k] = li -> dados[k + 1];
            }
            li -> tamanho--;
            return 1;
        }
    }
}

// Consulta um elemento a partir de um número de matrícula passado como parâmetro. Primeiro
// é feira a verificação se a lista está alocada e não está vazia, além de a posição a ser
// removida não ser menor do que 0 ou maior ou igual a o tamanho atual da lista, o que geraria
// um erro de indexação e faria com que a função retornasse o valor 0. Caso não haja esse
// retorno, o elemento passado também como parâmetro vai receber os dados do elemento na
// posição desejada.
int consulta_pos(Lista *li, Aluno *al, int pos)
{
    if (li == NULL || pos < 0 || pos >= (li -> tamanho))
    {
        return 0;
    }
    else
    {
        *al = li -> dados[pos];
        return 1;
    }
}

// Faz a consulta de um elemento através do número e matrícula. Primeiro há a verificação se a
// lista está alocada. Após isso um laço percorrerá a lista enquanto não chegar ao fim ou o número
// de matrícula do elemento atual seja diferente do número passado como parâmetro. Caso o iterador
// do laço se torne igual ao tamanho da lista (indicando que não encontrou o elemento) a função
// retorna 0. Caso contrário, o dado passado como parâmetro irá receber os dados do elemento do
// índice em que o iterador parou no loop anterior. É interessante perceber que o iterador i é
// declarardo no início da função e com valor 0 (que será o primeiro índice a ser percorrido no laço)
// para que dessa forma seu valor seja preservado mesmo depois do primeiro loop.
int consulta_mat(Lista *li, Aluno *al, int mat)
{
    int i = 0;

    if (li == NULL)
    {
        return 0;
    }
    else
    {
        while (i < li -> tamanho && li ->dados[i].matricula != mat)
        {
            i++;
        }
        if (i == li -> tamanho)
        {
            return 0;
        }
        else
        {
            *al = li -> dados[i];
            return 1;
        }
    }
}

// Função que imprime na saída os dados da lista. Primeiro é verificada se a lista está alocada e não
// está vazia. Então há um laço que percorrendo os elementos da lista mostra seus dados de maneira
// formatada.
int imprime_lista(Lista *li)
{
    if(li == NULL || lista_vazia(li))
    {
        return 0;
    }
    else
    {
        cout << "---------------------------------------------------" << endl;
        for (int i = 0; i < li -> tamanho; i++)
        {
            cout << "Nome:      " << li -> dados[i].nome << endl;
            cout << "Matrícula: " << li -> dados[i].matricula << endl;
            cout << fixed << "Notas:     " << setprecision(2) << li -> dados[i].n1 << " " << li -> dados[i].n2 << " " << li -> dados[i].n3 << endl;
            cout << fixed << "Média:     " << setprecision(2) << (li -> dados[i].n1 + li -> dados[i].n2 + li -> dados[i].n3) / 3 << endl;
            cout << "---------------------------------------------------" << endl;
        }
    }
}

