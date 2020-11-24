#include <iostream>
#include <string>
using namespace std;

class noh
{
    friend class fila;

private:
    int dado;
    noh *proximo;

public:
    noh(int valor);
};

noh::noh(int valor)
{
    dado = valor;
    proximo = NULL;
}

class fila
{
private:
    unsigned mTamanho;
    noh *mInicio;
    noh *mFim;

public:
    fila();
    ~fila();
    unsigned tamanho();

    void limpaFila();
    void enfileira(int valor);
    int desemfileira();
    bool vazia();
};

fila::fila()
{
    mInicio = NULL;
    mFim = NULL;
    mTamanho = 0;
}

fila::~fila()
{
    limpaFila();
}

void fila::limpaFila()
{
    while (not vazia())
    {
        desemfileira();
    }
}

unsigned fila::tamanho()
{
    return mTamanho;
}

void fila::enfileira(int valor)
{
    noh *novo = new noh(valor);
    if(this->vazia()){
        mInicio = novo;
    }else{
        mFim->proximo = novo;
    }
    mFim = novo;
    mTamanho++;
}

int fila::desemfileira()
{
    int valor = mInicio->dado;
    noh *tempo = mInicio;
    mInicio = tempo->proximo;
    delete tempo;
    mTamanho--;
    if(this->vazia()){
        mFim = NULL;
    }
    return valor;
}
     
bool fila::vazia()
{
    return (mTamanho == 0);
}

int main()
{
    fila f1;
    int num;
    cin >> num;

    while (num >= 0)
    {
        f1.enfileira(num);
        cin >> num;
    }

    cout << f1.tamanho() << endl;

    while (not f1.vazia())
    {
        cout << f1.desemfileira() << " " << endl;
    }

    return 0;
}
