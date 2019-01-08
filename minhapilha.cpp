#include <iostream>
#include <string>
#include <locale>

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

struct Pilha
{
    Elemento *inicio;
    Elemento *fim;
    unsigned int tamanho;
};

Pilha* nova_pilha();
unsigned int tamanho_da_pilha(Pilha *pi);
int deleta_pilha(Pilha *pi);
int insere_na_pilha(Pilha *pi, Contato con);
int remove_da_pilha(Pilha *pi);
int consulta_na_pilha(Pilha *pi, Contato *con, int opcao);

int main()
{
    setlocale(LC_ALL, "");
    Pilha *pilha = nova_pilha();
    Contato contato, *consulta = new Contato;
    int quantidade;

    cout << "Digite a quantidade de elementos: ";
    cin >> quantidade;
    cout << endl;
    for (int i = 0; i < quantidade; i++)
    {
        cin.ignore();
        cout << "Digite o nome do contato: ";
        getline(cin, contato.nome);
        cout << "Digite o número do contato: ";
        cin >> contato.numero;
        cout << endl;
        if (insere_na_pilha(pilha, contato) == 1)
        {
            cout << "Tamanho da pilha: " << tamanho_da_pilha(pilha) << endl;
        }
        if (int teste = consulta_na_pilha(pilha, consulta, 0) == 1)
        {
            cout << "Nome:   " << consulta -> nome << endl;
            cout << "Número: " << consulta -> numero << endl;
            cout << endl;
        }
        else
        {
            cout << "Erro: " << teste << endl;
        }
    }
    deleta_pilha(pilha);
    cout << "Tamanho da pilha: " << tamanho_da_pilha(pilha) << endl;
    

    return 0;
}

Pilha* nova_pilha()
{
    Pilha *pi = new Pilha;

    if (pi != NULL)
    {
        pi -> inicio = NULL;
        pi -> fim = NULL;
        pi -> tamanho = 0;

        return pi;        
    }
}

unsigned int tamanho_da_pilha(Pilha *pi)
{
    if (pi != NULL)
    {
        if (pi -> inicio == NULL && pi -> fim == NULL)
        {
            return 0;
        }
        else
        {
            return pi -> tamanho;
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
        if (tamanho_da_pilha(pi) == 0)
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
                while (tamanho_da_pilha(pi) > 0)
                {
                    no = pi -> inicio;
                    pi -> inicio = pi -> inicio -> proximo;
                    delete no;
                    pi -> tamanho--;
                }
                delete pi;

                return 1;
            }
        }
    }
}

int insere_na_pilha(Pilha *pi, Contato con)
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
            if (tamanho_da_pilha(pi) == 0)
            {
                pi -> fim = no;
            }
            no -> proximo = pi -> inicio;
            pi -> inicio = no;
            pi -> tamanho++;

            return 1;
        }
    }
}

int remove_da_pilha(Pilha *pi)
{
    if (pi == NULL)
    {
        return -1;
    }
    else
    {
        if (tamanho_da_pilha(pi) == 0)
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
                no = pi -> inicio;
                pi -> inicio = pi -> inicio -> proximo;
                delete no;
                pi -> tamanho--;

                return 1;
            }
        }
    }
}

int consulta_na_pilha(Pilha *pi, Contato *con, int opcao)
{
    if (pi == NULL)
    {
        return -1;
    }
    else
    {
        if (tamanho_da_pilha(pi) == 0)
        {
            return 0;
        }
        else
        {
            switch (opcao)
            {
                case 0:
                {
                    *con = pi -> inicio -> dado;
                    break;
                }
                case 1:
                {
                    *con = pi -> fim -> dado;
                    break;
                }
            }

            return 1;
        }
    }
}
