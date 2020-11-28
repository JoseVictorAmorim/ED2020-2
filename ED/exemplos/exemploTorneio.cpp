#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

typedef int data;
const int INVALID = -1;

class tournament{
    private:
        data* heap;
        int capacity;
        int mSize;
        int dataBegin;

        //funções auxiliares que o usuário nao deve chamar

        inline int father(int i); //conseguir posição do pai
        inline int left(int i); //conseguir posição do filho a esquerda
        inline int right(int i); //conseguir posição do filho a direita
        void heapify(); //arruma o vetor em heap chamando a corrigeDescendo
        void maxCopy(int i);
        void risingCopy(int i);
        
    public:
        tournament(int nLeaves); //construtor
        tournament(data vec[], int siz); //construtor 2
        ~tournament(); //destrutor
        // printTournament é apenas DIDÁTICO
        void printTournament(); //imprimir os dados do torneio -> Apenas DIDÁTICO
        void insert(data d); //inserir um dado no heap
};

tournament::tournament(int nLeaves){
    capacity = 1;
    while(capacity < nLeaves){
        capacity *= 2;
    }    

    capacity = capacity - 1 + nLeaves;
    heap = new data[capacity];
    dataBegin = capacity - nLeaves;

    cout << "Inicio dos dados: " << dataBegin << endl;
    cout << "Capacidade: " << capacity << endl;

    for(int i = 0; i < capacity; i++){
        heap[i] = INVALID;
    }       
}

tournament::tournament(data* vec, int siz){
    capacity = 1;
    while(capacity < siz){
        capacity *= 2;
    }
    capacity = capacity - 1 + siz;

    //Achando a potência de dois que inclui a quantidade de folhas

    heap = new data[capacity];
    dataBegin = capacity - siz;
    

    cout << "Inicio dos dados: " << dataBegin << endl;
    cout << "Capacidade: " << capacity << endl;

    copy(vec, vec+siz, heap+dataBegin);

    mSize = siz;

    heapify();
}

tournament::~tournament(){
    delete[] heap;
}

void tournament::heapify(){
    cout << "arruma: " << dataBegin - 1 << endl;
    for(int i = dataBegin - 1; i >= 0; i--){
        maxCopy(i);
    }
}


int tournament::father(int i){
    return((i-1)/2);
}
int tournament::left(int i){
    return((2*i)+1);
}
int tournament::right(int i){
    return((2*i)+2);    
}

void tournament::maxCopy(int i){
    int mLeft = left(i);
    int mRight = right(i);
    int max = INVALID;

    if(mLeft < capacity){
        if((mRight < capacity) and (heap[mRight] > heap[mLeft])){
            max = mRight;
        }else{
            max = mLeft;
        }
        heap[i] = heap[max];
    }else{
        heap[i] = INVALID;
    }
    

}

void tournament::risingCopy(int i){
    int f = father(i);
    if(heap[i] > heap[f]){
        heap[f] = heap[i];
        risingCopy(f);
    }
}

void tournament::printTournament(){
    for(int i = 0; i < capacity; i++){
        cout << heap[i] << " ";
    }
    cout << endl;
}

void tournament::insert(data d){
    if(mSize == capacity){
        cerr << "ERRO NA INSERCAO" << endl;
        exit(EXIT_FAILURE);
    }
    heap[mSize+dataBegin] = d;
    risingCopy(mSize+dataBegin);
    mSize++;
}


int main(){
    int siz;
    cin >> siz;
    data *vec = new data[siz]; 
    
    for(int i = 0; i < siz; i++){
        cin >> vec[i];
    }
    // 50 2 90 20 230 43 8 34 66 100 110 3 13

    tournament *h = new tournament(vec, siz);
    h->printTournament();
    delete h;
    delete vec;
    cout << "mahoe";
    return 0;
}