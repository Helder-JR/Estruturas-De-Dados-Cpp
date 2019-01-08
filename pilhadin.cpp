#include <iostream>
#include <string>

using namespace std;

struct Contato
{
    string nome;
    int numero;
};

struct Elemento
{
    Contato dado;
    Elemento *proximo;
};

typedef Elemento* Pilha;

Pilha* nova_pilha();
unsigned int tamanho_da_pilha(Pilha *pi);
unsigned int pilha_vazia(Pilha *pi);
int deleta_pilha(Pilha *pi);
int insere_no_inicio(Pilha *pi, Contato con);
int remove_do_inicio(Pilha *pi);
int consulta_do_inicio(Pilha *pi, Contato *con);

// Programa principal.
int main()
{


    return 0;
}

Pilha* nova_pilha()
{
    Pilha* pi = new Pilha;

    if (pi != NULL)
    {
        *pi = NULL;
    }

    return pi;
}

unsigned int tamanho_da_pilha(Pilha *pi)
{
    if (pi != NULL)
    {
        if ((*pi) == NULL)
        {
            return 0;
        }
        else
        {
            int tamanho = 0;
            Elemento *no = new Elemento;

            no = *pi;
            while (no != NULL)
            {
                tamanho++;
                no = no -> proximo;
            }

            return tamanho;
        }
    }
}

unsigned int pilha_vazia(Pilha *pi)
{
    if (pi != NULL)
    {
        if ((*pi) != NULL)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

int deleta_pilha(Pilha *pi)
{
    if (pi == NULL)
    {
        return -1;
    }
    else
    {
        if (pilha_vazia(pi))
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
                while ((*pi) != NULL)
                {
                    no = *pi;
                    *pi = (*pi) -> proximo;
                    delete no;
                }
                delete pi;

                return 1;
            }
        }
    }
}

int insere_no_inicio(Pilha *pi, Contato con)
{
    if (pi == NULL)
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
            no -> dado = con;
            no -> proximo = *pi;
            *pi = no;
        }
    }
}

int remove_do_inicio(Pilha *pi)
{
    if (pi == NULL)
    {
        return -1;
    }
    else
    {
        if (pilha_vazia(pi))
        {
            return 0;
        }
        else
        {
            Elemento *no = new Elemento;

            no = *pi;
            *pi = (*pi) -> proximo;
            delete no;

            return 1;
        }
    }
}

int consulta_do_inicio(Pilha *pi, Contato *con)
{
    if (pi == NULL)
    {
        return -1;
    }
    else
    {
        if (pilha_vazia(pi))
        {
            return 0;
        }
        else
        {
            *con = (*pi) -> dado;

            return 1;
        }
    }
}
