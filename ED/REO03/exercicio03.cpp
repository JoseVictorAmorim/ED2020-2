/* Classe pilha, um pilha (LIFO) implementada usando encadeamento
*
* by Joukim, 2017, Estruturas de Dados
*
*/

#include <iostream>

using namespace std;

class noh {
    friend class pilha;
    private:
        int dado; // poderia ser outro tipo de variável
        noh* prox;
    public:
        noh(int valor);
};

noh::noh(int valor){
    dado = valor;
    prox = NULL;
}

// pilha dinamicamente encadeada
class pilha {
private:
    noh* topo;
    int tamanho;

public:
    pilha();
    ~pilha();
    void push(int d) { empilha(d); }
    void empilha(int d);
    int pop() { return desempilha(); }
    int desempilha(); // retorna o topo da pilha
    int espia(); // espia o topo da pilha
    int oTamanho();
    bool vazia();
    void limpaPilha(); //limpa a pilha
};

pilha::pilha(){
    topo = NULL;
    tamanho = 0;
}

pilha::~pilha(){
    limpaPilha();
}

void pilha::empilha(int d){
    noh* novo = new noh(d);
    novo->prox = topo;
    topo = novo;
    tamanho++;
}

int pilha::desempilha(){
    int aux = topo->dado;
    noh* temp = topo;
    topo = topo->prox;
    delete temp;
    tamanho--;
    return aux;
}

int pilha::espia(){
    return(topo->dado);
}

int pilha::oTamanho(){
    return tamanho;
}

bool pilha::vazia(){
    return(tamanho == 0);
}

void pilha::limpaPilha(){
    while(not vazia()){
        desempilha();
    }
}

//  Implementar aqui
int acessaElemento(pilha& p1, int elemento){
    pilha p2;
    int p = 0, tam = p1.oTamanho();
    bool presente = false;
    
    while(not presente and p < tam){
        if(p1.espia() == elemento){
            presente = true;
        }else{
            p2.empilha(p1.desempilha());
        }
        p++;
    }

    if(presente){
        p1.desempilha();
    }

    while(not p2.vazia()){
        p1.empilha(p2.desempilha());
    }

    if(p <= tam and presente){
        return p;
    }

    return -1;
}

int main() {
    pilha p1;
    int n, numero, elemento;
    cin >> n;

    while (n > 0) {
        cin >> numero;
        p1.empilha(numero);
        n--;
    }

    cin >> elemento;
    cout << acessaElemento(p1,elemento) << endl;

    while (not p1.vazia()) {
        cout << p1.desempilha() << " ";
    }

    cout << endl;

    return 0;
}