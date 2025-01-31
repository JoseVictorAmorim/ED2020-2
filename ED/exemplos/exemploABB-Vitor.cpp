#include <iostream>
using namespace std;

typedef int Dado;

class Noh
{
    friend class ArvoreABB;
    private:
        Noh* mEsquerdo;
        Noh* mDireito;
        Noh* mPai;
        Dado valor;
    public:
        Noh(Dado d);
};

Noh::Noh(Dado d){
    //Construtor
    mEsquerdo = NULL;
    mDireito = NULL;
    mPai = NULL;
    valor = d;
}

class ArvoreABB
{
    private:
        Noh* mRaiz;
    public:
        ArvoreABB();
        ~ArvoreABB();
        void insere(Dado d);
        Noh* buscaAux(Noh* aux);
        void transplanta(Noh* antigo, Noh* novo);
        void remove(Dado d);
        Noh* minimoAux(Noh* atual);
        void imprimeOrdem(){ imprimeOrdem(mRaiz);}
        void imprimeOrdem(Noh* atual);
        void imprimePre(){ imprimePre(mRaiz);}
        void imprimePre(Noh* atual);
        void D(){ destruct(mRaiz);}
        void destruct(Noh* atual);
        Dado Nivel(Dado chave);
};

ArvoreABB::ArvoreABB(){
    //Contructor
    mRaiz = NULL;
}

ArvoreABB::~ArvoreABB(){
    //Destructor
    D();
}

void ArvoreABB::insere(Dado d){
    //Insere interativamente
    Noh* novo = new Noh(d);
    if(mRaiz == NULL){
        mRaiz = novo;
    } else {
        Noh* atual = mRaiz;
        Noh* ant = NULL;
        
        while(atual != NULL){
            ant = atual;
            if(atual -> valor > d){
                atual = atual -> mEsquerdo;
            } else {
                atual = atual -> mDireito;
            }
        }
        novo -> mPai = ant;
        if(ant -> valor > novo -> valor){
            ant -> mEsquerdo = novo;
        } else {
            ant -> mDireito = novo;
        }
    }
}

Noh* ArvoreABB::buscaAux(Noh* aux){
    //Faz a busca na estrutura e retorna
    Noh* atual = mRaiz;
    while(atual != NULL){
        if(atual -> valor == aux -> valor){
            return atual;
        } else if(atual -> valor > aux -> valor){
            atual = atual -> mEsquerdo;
        } else {
            atual = atual -> mDireito;
        }
    }
    return atual;
}

void ArvoreABB::transplanta(Noh* antigo, Noh* novo){
    //Troca dois nos
    if(mRaiz == antigo){
        mRaiz = novo;
    } else if(antigo == antigo -> mPai -> mEsquerdo){
        antigo -> mPai -> mEsquerdo = novo;
    } else {
        antigo -> mPai -> mDireito = novo;
    }
    if(novo != NULL){
        novo -> mPai = antigo -> mPai;
    }
}

void ArvoreABB::remove(Dado d){
    //Remove um elemento (noh) da arvore
    Noh* aux = new Noh(d);
    Noh* remover = buscaAux(aux);
    
    if(remover == NULL){
        cout << "ERRO" << endl;
    } else {
        if(remover -> mEsquerdo == NULL){
            transplanta(remover, remover -> mDireito);
        } else if(remover -> mDireito == NULL){
            transplanta(remover, remover -> mEsquerdo);
        } else {
            Noh* sucessor = minimoAux(remover -> mDireito);
            if(sucessor -> mPai != remover){
                transplanta(sucessor, sucessor -> mDireito);
                sucessor -> mDireito = remover -> mDireito;
                sucessor -> mDireito -> mPai = sucessor;
            }
            transplanta(remover, sucessor);
            sucessor -> mEsquerdo = remover -> mEsquerdo;
            sucessor -> mEsquerdo -> mPai = sucessor;
        }
        delete remover;
    }
}

Noh* ArvoreABB::minimoAux(Noh* atual){
    //Retorna o minimo da arvore
    while(atual -> mEsquerdo != NULL){
        atual = atual -> mEsquerdo;
    }
    return atual;
}

void ArvoreABB::imprimeOrdem(Noh* atual){
    if(atual != NULL){
        imprimeOrdem(atual -> mEsquerdo);
        Dado altura = Nivel(atual->valor);
        cout << atual -> valor << "/" << altura << " ";
        imprimeOrdem(atual -> mDireito);
    }
}

void ArvoreABB::imprimePre(Noh* atual){
    if(atual != NULL){
        Dado altura = Nivel(atual->valor);
        cout << atual -> valor << "/" << altura << " ";
        imprimePre(atual -> mEsquerdo);
        imprimePre(atual -> mDireito);
    }
}

void ArvoreABB::destruct(Noh* atual){
    if(atual != NULL){
        destruct(atual->mEsquerdo);
        destruct(atual->mDireito);
        delete atual;
    }
}

Dado ArvoreABB::Nivel(Dado chave){
    Noh* atual = mRaiz;
    Dado cont = 0;
    while(atual != NULL){
        if(atual->valor == chave){
            return cont;
        } else if(atual -> valor > chave){
            atual = atual -> mEsquerdo;
        } else {
            atual = atual -> mDireito;
        }
        cont++;
    }
    return cont;
}

int main()
{
    ArvoreABB minhaArvore;
    char escolha;
    cin >> escolha;
    Dado chave;
    do{
        switch(escolha){
            case 'i':
                cin >> chave;
                minhaArvore.insere(chave);
                break;
            case 'r':
                cin >> chave;
                minhaArvore.remove(chave);
                break;
            case 'o':
                minhaArvore.imprimeOrdem();
                cout << endl;
                break;
            case 'p':
                minhaArvore.imprimePre();
                cout << endl;
                break;
            case 'q':
                break;
            default:
                cout << "Comando Invalido!";
            }
            cin >> escolha;
    }while(escolha != 'q');
    
    
    return 0;
}

