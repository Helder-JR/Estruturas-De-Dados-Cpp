#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <locale>

#define DEBUG 1
#define INSERT 2

using namespace std;

// TAD que compôe os dados da lista.
struct Aluno
{
    string nome;
    int matricula;
    float n1, n2, n3;
};

// É o que compõe cada membro da lista. Consiste de uma struct que tem dados e um
// ponteiro para uma struct do mesmo tipo, que indica o próximo elemento da lista.
struct Elemento
{
    Aluno dado;
    Elemento* proximo;
};

// Struct que representa a lista em si, representada por um ponteiro que aponta para o primeiro
// elemento da lista, um para o último e uma variável que guarda o tamanho da lista.
struct Lista
{
    Elemento *inicio;
    Elemento *fim;
    unsigned int tamanho;
};

// Protótipos das funções que serão incluídas em headers posteriormente.
Lista* nova_lista();
unsigned int tamanho_da_lista(Lista *li);
int deleta_lista(Lista *li);
int insere_no_inicio(Lista *li, Aluno al);
int insere_no_fim(Lista *li, Aluno al);
int insere_na_posicao(Lista *li, Aluno al, unsigned int pos);
int insere_ordenadamente(Lista *li, Aluno al);
int remove_do_inicio(Lista *li);
int remove_do_fim(Lista *li);
int remove_na_posicao(Lista *li, unsigned int pos);
int consulta_por_posicao(Lista *li, Aluno *al, unsigned int pos);
int consulta_por_nome(Lista *li, Aluno *al, string nome);

// Programa principal.
int main()
{
    Lista *lista = nova_lista();
    Aluno aluno, *cons = new Aluno;
    unsigned int quantidade;

    cout << "Digite a quantidade de alunos: ";
    cin >> quantidade;
    
    for (int i = 0; i < quantidade; i++)
    {
        cin.ignore();
        cout << "Digite o nome do " << i + 1 << "º aluno: ";
        getline(cin, aluno.nome);
        cout << "Digite a matrícula do " << i + 1 << "º aluno: ";
        cin >> aluno.matricula;
        cout << "Digite as notas do " << i + 1 << "º aluno: ";
        cin >> aluno.n1 >> aluno.n2 >> aluno.n3;

        #if INSERT == 0
            insere_no_inicio(lista, aluno);
        #elif INSERT == 1
            insere_no_fim(lista, aluno);
        #elif INSERT == 2
            insere_ordenadamente(lista, aluno);
        #endif

        #if DEBUG == 1
            consulta_por_nome(lista, cons, aluno.nome);
            cout << cons -> nome << endl;
            cout << cons -> matricula << endl;
            cout << fixed << setprecision(2) << cons -> n1 << " " << cons -> n2 << " " << cons -> n3 << endl;
        #endif
    }

    return 0;
}

// Função que cria uma nova struct Lista através de alocação dinâmica. Caso a lista seja corretamente
// alocada então seu início e fim apontarão para NULL, e seu tamanho será definido como 0,  indicando
// que está vazia. Por fim, a função retorna o endereço dessa lista.
Lista* nova_lista()
{
    Lista *li = new Lista;

    if (li != NULL)
    {
        li -> inicio = NULL;
        li -> fim = NULL;
        li -> tamanho = 0;

        return li;
    }
}

// Função que retorna o tamanho da lista (passada como parâmetro). Caso essa lista esteja alocada, então
// uma condição irá verificar se o começo e o fim da lista apontam para NULL, indicando que está vazia.
// Caso positivo a função irá retornar 0, do contrário ela retornará o tamanho da lista em questão. O tipo
// de retorno da lista é unsigned int para certificar que valores negativos não serão devolvidos na execução
// dessa função.
unsigned int tamanho_da_lista(Lista *li)
{
    if (li != NULL)
    {
        if (li -> inicio == NULL && li -> fim == NULL)
        {
            return 0;
        }
        else
        {
            return li -> tamanho;
        }
    }
}

int deleta_lista(Lista *li)
{
    if (li == NULL)
    {
        return -1;
    }
    else
    {
        if (tamanho_da_lista(li) == 0)
        {
            delete li;
            
            return 0;
        }
        else
        {
            Elemento *no = new Elemento;

            if (no == NULL)
            {
                return 0;
            }
            else
            {
                while (tamanho_da_lista(li) > 0)
                {
                    no = li -> inicio;
                    li -> inicio = li -> inicio -> proximo;
                    delete no;
                    li -> tamanho--;
                }
                delete li;
            }

            return 1;
        }
    }
}

int insere_no_inicio(Lista *li, Aluno al)
{
    if (li == NULL)
    {
        return -1;
    }
    else
    {
        Elemento *no = new Elemento;

        if (no == NULL)
        {
            return 0;
        }
        else
        {
            no -> dado = al;
            if (tamanho_da_lista(li) == 0)
            {
                li -> fim = no;
            }
            no -> proximo = li -> inicio;
            li -> inicio = no;
            li -> tamanho++;

            return 1;
        }
    }
}

int insere_no_fim(Lista *li, Aluno al)
{
    if (li == NULL)
    {
        return -1;
    }
    else
    {
        Elemento *no = new Elemento;

        if (no == NULL)
        {
            return 0;
        }
        else
        {
            no -> dado = al;
            no -> proximo = NULL;
            if (tamanho_da_lista(li) == 0)
            {
                li -> inicio = no;
            }
            else
            {
                li -> fim -> proximo = no;
            }
            li -> fim = no;
            li -> tamanho++;

            return 1;
        }
    }
}

int insere_na_posicao(Lista *li, Aluno al, unsigned int pos)
{
    if (li == NULL)
    {
        return -1;
    }
    else
    {
        Elemento *no = new Elemento, *anterior, *atual = li -> inicio;

        if (no == NULL)
        {
            return 0;
        }
        else
        {
            no -> dado = al;
            if (tamanho_da_lista(li) == 0)
            {
                no -> proximo = li -> inicio;
                li -> inicio = no;
                li -> fim = no;
            }
            else
            {
                if (pos == 0)
                {
                    no -> proximo = li -> inicio;
                    li -> inicio = no;
                }
                else
                {
                    if (pos >= tamanho_da_lista(li))
                    {
                        no -> proximo = NULL;
                        li -> fim -> proximo = no;
                        li -> fim = no;
                    }
                    else
                    {
                        for (int i = 0; i < pos; i++)
                        {
                            anterior = atual;
                            atual = atual -> proximo;
                        }
                        no -> proximo = atual;
                        anterior -> proximo = no;
                    }
                }
            }
            li -> tamanho++;

            return 1;
        }
    }
}

int insere_ordenadamente(Lista *li, Aluno al)
{
    if (li == NULL)
    {
        return -1;
    }
    else
    {
        Elemento *no = new Elemento, *anterior, *atual = li -> inicio;

        if (no == NULL)
        {
            return 0;
        }
        else
        {
            no -> dado = al;
            if (tamanho_da_lista(li) == 0)
            {
                no -> proximo = li -> inicio;
                li -> inicio = no;
                li -> fim = no;
            }
            else
            {
                while (atual != li -> fim -> proximo && atual -> dado.nome < al.nome)
                {
                    anterior = atual;
                    atual = atual -> proximo;
                }
                if (atual = li -> inicio)
                {
                    no -> proximo = li -> inicio;
                    li -> inicio = no;
                }
                else
                {
                    if (atual = li -> fim -> proximo)
                    {
                        anterior -> proximo = no;
                        no -> proximo = atual;
                        li -> fim = no;

                    }
                    else
                    {
                        no -> proximo = atual;
                        anterior -> proximo = no;
                    }
                }
            }
            li -> tamanho++;

            return 1;
        }
    }
}

int remove_do_inicio(Lista *li)
{
    if (li == NULL)
    {
        return -1;
    }
    else
    {
        if (tamanho_da_lista(li) == 0)
        {
            return 0;
        }
        else
        {
            Elemento *no = new Elemento;

            if (no == NULL)
            {
                return 0;
            }
            else
            {
                no = li -> inicio;
                li -> inicio = li -> inicio -> proximo;
                delete no;
                li -> tamanho--;

                return 1;
            }
        }
    }
}

int remove_do_fim(Lista *li)
{
    if (li == NULL)
    {
        return -1;
    }
    else
    {
        if (tamanho_da_lista(li) == 0)
        {
            return 0;
        }
        else
        {
            Elemento *no = new Elemento, *anterior, *atual = li -> inicio;

            if (no == NULL)
            {
                return 0;
            }
            else
            {
                for (int i = 0; i < tamanho_da_lista(li) - 1; i++)
                {
                    anterior = atual;
                    atual = atual -> proximo;
                }
                li -> fim = anterior;
                delete atual;
                li -> tamanho--;

                return 1;
            }
        }
    }
}

int remove_na_posicao(Lista *li, unsigned int pos)
{
    if (li == NULL)
    {
        return -1;
    }
    else
    {
        if (tamanho_da_lista(li) == 0)
        {
            return 0;
        }
        else
        {
            Elemento *no = new Elemento, *anterior, *atual = li -> inicio;

            if (no == NULL)
            {
                return 0;
            }
            else
            {
                if (pos == 0)
                {
                    no = li -> inicio;
                    li -> inicio = li -> inicio -> proximo;
                    delete no;
                }
                else
                {
                    if (pos >= tamanho_da_lista(li) - 1)
                    {
                        for (int i = 0; i < tamanho_da_lista(li) - 1; i++)
                        {
                            anterior = atual;
                            atual = atual -> proximo;
                        }
                        li -> fim = anterior;
                        delete atual;
                    }
                    else
                    {
                        for (int i = 0; i < pos; i++)
                        {
                            anterior = atual;
                            atual = atual -> proximo;
                        }
                        anterior -> proximo = atual -> proximo;
                        delete atual;
                    }
                }
                li -> tamanho--;

                return 1;
            }
        }
    }
}

int consulta_por_posicao(Lista *li, Aluno *al, unsigned int pos)
{
    if (li == NULL)
    {
        return -1;
    }
    else
    {
        if (tamanho_da_lista(li) == 0)
        {
            return 0;
        }
        else
        {
            if (pos == 0)
            {
                *al = li -> inicio -> dado;
            }
            else
            {
                if (pos >= tamanho_da_lista(li) - 1)
                {
                    *al = li -> fim -> dado;
                }
                else
                {
                    Elemento *no = new Elemento;

                    if (no == NULL)
                    {
                        return 0;
                    }
                    else
                    {
                        no = li -> inicio;
                        for (int i = 0; i < pos; i++)
                        {
                            no = no -> proximo;
                        }
                        *al = no -> dado;
                    }
                }

                return 1;
            }
        }
    }
}

int consulta_por_nome(Lista *li, Aluno *al, string nome)
{
    if (li == NULL)
    {
        return -1;
    }
    else
    {
        if (tamanho_da_lista(li) == 0)
        {
            return 0;
        }
        else
        {
            Elemento *no = new Elemento;

            if (no == NULL)
            {
                return 0;
            }
            else
            {
                no = li -> inicio;
                while (no != li -> fim -> proximo && no -> dado.nome != nome)
                {
                    no = no -> proximo;
                }
                if (no == NULL)
                {
                    return 0;
                }
                else
                {
                    *al = no -> dado;

                    return 1;
                }
            }
        }
    }
}
