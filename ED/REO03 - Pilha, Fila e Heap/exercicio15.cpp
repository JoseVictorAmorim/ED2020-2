#include <iostream>
#include <cstdlib>
using namespace std;
class Pessoa {
    public:
        int senha;
        int prioridade;
};

bool operator>(const Pessoa& p1, const Pessoa& p2) {
    return p1.prioridade > p2.prioridade;
}

std::ostream& operator<<(std::ostream& saida, const Pessoa& p) {
    saida << "(s" << p.senha << ",p" << p.prioridade << ")";
    return saida;
}

typedef Pessoa TDado;

class MaxHeap {
    friend std::ostream& operator << (std::ostream& saida, const MaxHeap& h);
    public:
        MaxHeap(int cap);
        ~MaxHeap();
        void Inserir(TDado d);
        bool Retirar(TDado& ptDado);
        bool Vazia();
    private:
        TDado* heap;
        int capacidade;
        int tamanho;
        void ArrumarDescendo(int i);
        void ArrumarSubindo(int i);
        inline int Direito(int i); 
        inline int Esquerdo(int i);
        inline int Pai(int i);
};

using namespace std;

MaxHeap::MaxHeap(int cap) {
    capacidade = cap;
    heap = new TDado[cap];
    tamanho = 0;
}

MaxHeap::~MaxHeap() {
    delete[] heap;
}

void MaxHeap::ArrumarDescendo(int i) {
    // Arruma descendo a partir da posicao i.
    int esq = Esquerdo(i);
    int dir = Direito(i);
    int maior = i;

    if((esq < tamanho) and (heap[esq] > heap[maior])){
        maior = esq;
    }

    if((dir < tamanho) and (heap[dir] > heap[maior])){
        maior = dir;
    }

    if(maior != i){
        swap(heap[i], heap[maior]);
        ArrumarDescendo(maior);
    }
}

void MaxHeap::ArrumarSubindo(int i) {
    // Arruma subindo a partir da posicao i.
    int p = Pai(i);
    if(heap[i]> heap[p]){
        swap(heap[i], heap[p]);
        ArrumarSubindo(p);
    }
}

int MaxHeap::Pai(int i) {
    return((i-1)/2);
}

int MaxHeap::Esquerdo(int i) {
    return((2*i)+1);
}

int MaxHeap::Direito(int i) {
    return((2*i)+2);
}

bool MaxHeap::Retirar(TDado& ptDado) {
    // Retira e retorna o maior valor.
    // Retorna falso se a heap estiver vazia.
    if(Vazia()){
        return false;
    }
    ArrumarDescendo(0);
    ptDado = heap[0];
    swap(heap[0], heap[tamanho-1]);
    tamanho--;
    ArrumarDescendo(0);
  
    return true;
}

bool MaxHeap::Vazia() {
    return(tamanho == 0);
}

void MaxHeap::Inserir(TDado d){
    // Insere um dado na heap.
    if(tamanho < capacidade){
        heap[tamanho] = d;
        ArrumarSubindo(tamanho);
        tamanho++;
    }
}

std::ostream& operator << (std::ostream& saida, const MaxHeap& h) {
    // Operador de escrita pode ser util para depurar a heap.
    for (int i=0; i < h.tamanho; ++i)
        saida << h.heap[i] << ' ';
    return saida;
}

unsigned Indice(char tipo) {
    // Funcao para converter tipo de pessoa na fila para indices no vetor de contadores.
    switch (tipo) {
        case 'P': return 0;
        case 'V': return 1;
        case 'C': return 2;
        case 'N': return 3;
    }
    return 0;
}

void Decrementar(unsigned& contador, char tipo) {
    // Funcao para decretar um contador de prioridades.
    --contador;
    if (contador == 0) {
        switch (tipo) {
            case 'P': contador = 50; break;
            case 'V': contador = 46; break;
            case 'C': contador = 42; break;
            case 'N': contador = 38; break;
        }
    }
}

int main() {
    unsigned capacidade;
    cin >> capacidade;
    MaxHeap heap(capacidade);
    char comando;
    unsigned indice;
    unsigned vetContadores[] = { 50, 46, 42, 38 };
    char tipo;
    unsigned senha = 0;
    Pessoa pessoa;
    do {
        cin >> comando;
        switch (comando) {
            case 'c': // chegada
                cin >> tipo;
                indice = Indice(tipo);
                pessoa.senha = ++senha;
                pessoa.prioridade = vetContadores[indice];
                heap.Inserir(pessoa);
                Decrementar(vetContadores[indice], tipo);
                cout << pessoa.senha << ' ' << pessoa.prioridade << endl;
                break;
            case 'a': // atendimento
                if (heap.Retirar(pessoa))
                    cout << pessoa.senha << endl;
                else
                    cout << "ninguem na fila" << endl;
                break;
            case 's': //sair do programa
                break;
        }
    } while (comando != 's');
    return 0;
}