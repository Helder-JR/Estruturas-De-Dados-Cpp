#include <iostream>
#include <iomanip>
#include <string>
#include <locale>

using namespace std;

// TAD que serve de base para a fila.
struct Aluno
{
    string nome;
    int matricula;
    float n1, n2, n3;
};

// O que compõe a fila. É composto pelo TAD e por um ponteiro que aponta para o próximo elemento da
// fila.
struct Elemento
{
    Aluno dado;
    Elemento *proximo;
};

// A fila em si. É composta de dois ponteiros. Um aponta para o início e outro para o final, além de
// uma variável que conta o tamanho da fila, que será incrementada a cada inserção de novo elemento e
// decrementada a cada remoção.
struct Fila
{
    Elemento *inicio;
    Elemento *fim;
    unsigned int tamanho;
};

// Protótipo das funções que mais tarde serão incluídas em um header.
Fila* nova_fila();
void deleta_fila(Fila *fi);
unsigned int tamanho_fila(Fila *fi);
int fila_vazia(Fila *fi);
int insere_final(Fila *fi, Aluno al);
int remove_inicio(Fila *fi);
int consulta_fila(Fila *fi, Aluno *al);
int imprime_fila(Fila *fi);

// Programa principal.
int main()
{
    setlocale(LC_ALL, "");
    Fila* fila = nova_fila();
    Aluno estudante;
    int quantidade;

    cout << "Digite a quantidade de elementos que serão inseridos: ";
    cin >> quantidade;
    cout << endl;

    for (int i = 0; i < quantidade; i++)
    {
        cin.ignore();
        cout << "Digite o nome do " << i + 1 << "º estudante: ";
        getline(cin, estudante.nome);
        cout << "Digite a matrícula desse estudante: ";
        cin >> estudante.matricula;
        cout << "Digite as três notas desse estudante: ";
        cin >> estudante.n1 >> estudante.n2 >> estudante.n3;
        cout << endl;
        insere_final(fila, estudante);
    }

    imprime_fila(fila);

    return 0;
}

// Função que cria uma nova fila. Primeiro é criado um ponteiro por alocação dinâmica que irá receber
// o endereço da fila, e caso seja alocada com sucesso seus valores de início e fim irão apontar para
// NULL e seu tamanho será definido como 0, indicando que a lista está vazia. Então a função retornará
// o endereço da fila criada para a variável (também ponteiro) que solicitou sua criação.
Fila* nova_fila()
{
    Fila *fi = new Fila;
    if (fi != NULL)
    {
        fi -> inicio = NULL;
        fi -> fim = NULL;
        fi -> tamanho = 0;
        
        return fi;
    }
}

// Função que deleta a fila. Primeiro cada um de seus elementos é deletado, por fim a fila em si é
// deletada. O algoritmo começa com a condição de a lista estar alocada em memória, então haverá também
// a condição de a fila não estar vazia (tamanho 0), pois caso esteja é necessário apenas que a fila
// seja desalocada da meméria. Caso contenha elementos será criado um elemento auxiliar que irá receber
// cada elemento a ser deletado. Após isso será executado um laço enquanto o início da fila não apontar
// para NULL (outro indicativo de fila vazia), O elemento do início da fila terá seu endereço passado ao
// elemento auxiliar (que irá mais tarde deletá-lo), então o início da fila agora apontará para o próximo
// elemento da fila, através do acesso a ele pelo membro 'proximo' do elemento. A partir daí o tamanho
// da fila será decrementado e o elemento auxiliar (que correspondia antes ao primeiro elemento) será
// desalocado (deletado). Por fim, após o término desse laço a fila será deletada.
void deleta_fila(Fila *fi)
{
    if (fi != NULL)
    {
        if (fi -> tamanho > 0)
        {
            Elemento *no;
            while (fi -> inicio != NULL)
            {
                no = fi -> inicio;
                fi -> inicio = fi -> inicio -> proximo;
                fi -> tamanho--;
                delete no;
            }
            delete fi;
        }
        else
        {
            delete fi;
        }
    }
}

// Função que retorna o tamanho da fila através apenas do acesso ao seu membro tamanho, tendo apenas
// como condição de execução a fila estar alocada em memória.
unsigned int tamanho_fila(Fila *fi)
{
    if (fi != NULL)
    {
        return fi -> tamanho;
    }
}

int fila_vazia(Fila *fi)
{
    if (fi == NULL)
    {
        return -1;
    }
    else
    {
        if (fi -> tamanho == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int insere_final(Fila *fi, Aluno al)
{
    if (fi == NULL)
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
            no -> dado = al;
            no -> proximo = NULL;
            if (fi -> tamanho == 0)
            {
                fi -> inicio = no;
            }
            else
            {
                fi -> fim -> proximo = no;
            }
            fi -> fim = no;
            fi -> tamanho++;
            delete no;

            return 1;
        }
    }
}

int remove_inicio(Fila *fi)
{
    if (fi == NULL || fi -> tamanho == 0)
    {
        return 0;
    }
    else
    {
        Elemento *no = new Elemento;

        no = fi -> inicio;
        fi -> inicio = fi -> inicio -> proximo;
        fi -> tamanho--;
        if (fi -> tamanho == 0)
        {
            fi -> fim = NULL;
        }
        delete no;

        return 1;
    }
}

int consulta_fila(Fila *fi, Aluno *al)
{
    if (fi == NULL || al == NULL)
    {
        return 0;
    }
    else
    {
        *al = fi -> inicio -> dado;

        return 1;
    }
}

int imprime_fila(Fila *fi)
{
    if (fi == NULL || fi -> tamanho == 0)
    {
        return 0;
    }
    else
    {
        Elemento *no = new Elemento;

        no = fi -> inicio;
        while (no != NULL)
        {
            cout << "Nome:      " << no -> dado.nome << endl;
            cout << "Matrícula: " << no -> dado.matricula << endl;
            cout << fixed << "Notas:     " << setprecision(2) << no -> dado.n1 << " " << no -> dado.n2 << " " << no -> dado.n3 << endl;
            cout << fixed << "Média:     " << setprecision(2) << (no -> dado.n1 + no -> dado.n2 + no -> dado.n3) / 3 << endl;
            cout << endl;
            no = no -> proximo;
        }
        delete no;

        return 1;
    }
}
