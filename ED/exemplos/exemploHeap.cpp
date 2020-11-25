#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

typedef int data;

class MaxHeap{
    private:
        data* heap;
        int capacity;
        int mSize;

        //funções auxiliares que o usuário nao deve chamar

        inline int father(int i); //conseguir posição do pai
        inline int left(int i); //conseguir posição do filho a esquerda
        inline int right(int i); //conseguir posição do filho a direita
        void heapify(); //arruma o vetor em heap chamando a corrigeDescendo
        void cRising(int i);
        void cLowering(int i);
        
    public:
        MaxHeap(int cap); //construtor
        MaxHeap(data vec[], int siz); //construtor 2
        ~MaxHeap(); //destrutor

        // printHeap é apenas DIDÁTICO
        void printHeap(); //imprimir os dados do heap -> Apenas DIDÁTICO
        data rootPeek(); //espiar a raiz
        data removeRoot(); //retirar a raiz e reorganizar o vetor
        void insert(data d); //inserir um dado no heap
};

MaxHeap::MaxHeap(int cap){
    capacity = cap;
    heap = new data[capacity];
    mSize = 0;           
}

MaxHeap::MaxHeap(data* vec, int siz){
    capacity = siz;
    heap = new data[siz];

    copy(vec, vec+siz, heap);

    mSize = siz;
    
    heapify();
}

MaxHeap::~MaxHeap(){
    delete[] heap;
}

void MaxHeap::heapify(){
    for(int i = ((mSize/2)-1); i >= 0; i--){
        cLowering(i);
    }
}


int MaxHeap::father(int i){
    return((i-1)/2);
}
int MaxHeap::left(int i){
    return((2*i)+1);
}
int MaxHeap::right(int i){
    return((2*i)+2);    
}

void MaxHeap::cLowering(int i){
    int mLeft = left(i);
    int mRight = right(i);
    int max = i;

    if((mLeft < mSize) and (heap[mLeft] > heap[max])){
        max = mLeft;
    }

    if((mRight < mSize) and (heap[mRight] > heap[max])){
        max = mRight;
    }

    if(max != i){
        swap(heap[i], heap[max]);
        cLowering(max);
    }
}

void MaxHeap::cRising(int i){
    int f = father(i);
    if(heap[i] > heap[f]){
        swap(heap[i], heap[f]);
        cRising(f);
    }
}

void MaxHeap::printHeap(){
    for(int i = 0; i < mSize; i++){
        cout << heap[i] << " ";
    }
    cout << endl;
}

data MaxHeap::rootPeek(){
    return heap[0];
}

data MaxHeap::removeRoot(){
    if(mSize==0){
        cerr << "Erro ao retirar raiz" << endl;
        exit(EXIT_FAILURE);
    }
    data aux = heap[0];
    swap(heap[0], heap[mSize-1]);
    mSize--;
    cLowering(0);
    return aux;
}

void MaxHeap::insert(data d){
    if(mSize == capacity){
        cerr << "ERRO NA INSERCAO" << endl;
        exit(EXIT_FAILURE);
    }
    heap[mSize] = d;
    cRising(mSize);
    mSize++;
}


int main(){
    int siz = 13;
    data *vec = new data[siz]; 
    
    for(int i = 0; i < siz; i++){
        cin >> vec[i];
    }
    // 50 2 90 20 230 43 8 34 66 100 110 3 13

    MaxHeap *h = new MaxHeap(vec, siz);

    for(int i = 0; i < siz; i++){
        cout << h->removeRoot() << " : ";
        h->printHeap();
    }
    cout << endl;

    for(int i = 0; i < siz; i++){
        h->insert(vec[i]);
    }

    for(int i = 0; i < siz; i++){
        cout << h->removeRoot() << " : ";
        h->printHeap();
    }

    cout << endl;

    delete h;
    delete vec;

    return 0;
}