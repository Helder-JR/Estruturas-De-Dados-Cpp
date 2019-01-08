#include <iostream>
#include <iomanip>
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

struct Fila
{
    Elemento *inicio;
    Elemento *fim;
    unsigned int tamanho;    
};

Fila* nova_fila();
unsigned int tamanho_da_fila(Fila *fi);
Contato novo_contato();
int insere_na_fila(Fila *fi, Contato con);
int remove_da_fila(Fila *fi);
int deleta_fila(Fila *fi);
int consulta_na_fila(Fila *fi, Contato *con);

int main()
{
    int quantidade;
    Fila *fila = nova_fila();
    
    cout << "Digite a quantidade de contatos: ";
    cin >> quantidade;

    for (int i = 0; i < quantidade; i++)
    {
        insere_na_fila(fila, novo_contato());
    }

    return 0;
}

Fila* nova_fila()
{
    Fila* fi = new Fila;
    
    if (fi != NULL)
    {
        fi -> inicio = NULL;
        fi -> fim = NULL;
        fi -> tamanho = 0;
    }

    return fi;
}

unsigned int tamanho_da_fila(Fila *fi)
{
    if (fi != NULL)
    {
        if (fi -> inicio == NULL && fi -> fim == NULL)
        {
            return 0;
        }
        else
        {
            return fi -> tamanho;
        }  
    }
}

Contato novo_contato()
{
    Contato con;

    cin.ignore();
    cout << "Digite o nome do contato:   ";
    getline(cin, con.nome);
    cout << "Digite o número do contato: ";
    cin >> con.numero;
    cout << endl;

    return con;
}

int insere_na_fila(Fila *fi, Contato con)
{
    if (fi == NULL)
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
            no -> proximo = NULL;
            if (tamanho_da_fila(fi) == 0)
            {
                fi -> inicio = no;
            }
            else
            {
                fi -> fim -> proximo = no;
            }
            fi -> fim = no;
            fi -> tamanho++;

            return 1;
        }
    }
}

int remove_da_fila(Fila *fi)
{
    if (fi == NULL)
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
            no = fi -> inicio;
            fi -> inicio = fi -> inicio -> proximo;
            if (fi -> inicio == NULL)
            {
                fi -> fim = NULL;
            }
            delete no;
            fi -> tamanho--;

            return 1;
        }
    }
}

int deleta_fila(Fila *fi)
{
    if (fi == NULL)
    {
        return -1;
    }
    else
    {
        if (tamanho_da_fila(fi) == 0)
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
                while (tamanho_da_fila(fi) > 0)
                {
                    no = fi -> inicio;
                    fi -> inicio = fi -> inicio -> proximo;
                    if (fi -> inicio == NULL)
                    {
                        fi -> fim = NULL;
                    }
                    delete no;
                    fi -> tamanho--;
                }

                return 1;
            }
        }
    }
}

int consulta_na_fila(Fila *fi, Contato *con)
{
    if (fi == NULL)
    {
        return -1;
    }
    else
    {
        *con = fi -> inicio -> dado;
    }

}
