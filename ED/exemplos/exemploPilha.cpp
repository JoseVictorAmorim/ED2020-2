#include <iostream>
#include <string>
using namespace std;

class noh
{
    friend class pilha;

private:
    int dados;
    noh *proximo;

public:
    noh(int valor);
};

noh::noh(int valor)
{
    dados = valor;
    proximo = NULL;
};

class pilha
{
private:
    unsigned pTamanho;
    noh *pTopo;

public:
    pilha();
    ~pilha();

    unsigned tamanho();
    void limpaPilha();
    void empilha(int valor);
    int desempilha();
    bool vazia();
};

pilha::pilha()
{
    pTamanho = 0;
    pTopo = NULL;
}

pilha::~pilha()
{
    limpaPilha();
}

unsigned pilha::tamanho()
{
    return pTamanho;
}

void pilha::limpaPilha()
{
    while (not vazia())
    {
        desempilha();
    }
}

void pilha::empilha(int valor)
{
    noh *novo = new noh(valor);
    novo->proximo = pTopo;
    pTopo = novo;
    pTamanho++;
}

int pilha::desempilha()
{
    int aux = pTopo->dados;
    noh *tempo = pTopo;

    pTopo = pTopo->proximo;
    delete tempo;
    pTamanho--;
    return aux;
}
    
bool pilha::vazia(){
    return(pTamanho == 0);
}

int main()
{
    pilha p1;
    int num;
    cin >> num;

    while (num >= 0)
    {
        p1.empilha(num);
        cin >> num;
    }

    cout << p1.tamanho() << endl;

    while (not p1.vazia())
    {
        cout << p1.desempilha() << " " << endl;
    }

    return 0;
}