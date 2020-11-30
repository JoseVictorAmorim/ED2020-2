//No método ::info(), deixei comentado outras 2 opções de impressão da fila/vetor para fins de depuração
//e correção manual

#include <iostream>
using namespace std;

class circularQueue{
    private:
        int head; //inicio da fila
        int tail; //fim da fila
        int* data;
        unsigned capacity;
        unsigned mSize;
    public:
        circularQueue(int maxCapacity); //Construtor
        ~circularQueue(); //Destrutor

        void enqueue(int value);
        int dequeue();
        bool empty();
        void info(); //método para obter as informações da fila. Faz quebra de estrutura.
};

circularQueue::circularQueue(int maxCapacity){
    head = -1;
    tail = -1;
    capacity = maxCapacity;
    data = new int[capacity];
    mSize = 0;
}

circularQueue::~circularQueue(){
    delete[] data;
}

void circularQueue::enqueue(int value){
    if(mSize < capacity){
        if(empty()){
            head++;
        }
        tail++;
        tail = tail % capacity;
        data[tail] = value;
        mSize++;
    }
}

int circularQueue::dequeue(){
    int aux = -1;
    if(not empty()){
        aux = data[head];
        mSize--;
        head++;
        head = head % capacity;    
    }
    
    if(empty()){ //sem else para forçar a verificação após a mudança no primeiro if
        head = -1;
        tail = -1;
    }

    return aux;
}

bool circularQueue::empty(){
    return(mSize == 0);
}

void circularQueue::info(){
    //Esse método faz quebra de estrutura, entretanto pedido pelo exercicio.
    cout << "tamanho=" << mSize
    << " capacidade=" << capacity
    << " inicio=" << head
    << " fim=" << tail << endl;

    // Como explicado na live do dia 25/11, impressao na ordem do vetor.

    //Impressão na ordem do vetor, sem saída de lixo
    if(not empty()){
        if(tail>=head){
            for(int i = head; i <= tail; i++){
                cout << data[i] << " ";
            }
        }else{
            for(int i = 0; i <= tail; i++){
                cout << data[i] << " ";
            }
            for(unsigned i = head; i < capacity; i++){
                cout << data[i] << " ";
            }
        }
    }else{ //não há dados no vetor que não sejam lixo, portanto não dá a saida.
        cout << "";
    }

    //Impressão na ordem do vetor, com saida de lixo.
    /*if(mSize == 1){ //Se o vetor só tiver um dado, mostra apenas o dado e a posição dele no vetor.
        cout << data[head];
    }else{ 
        for(unsigned i = 0; i < capacity; i++){
            cout << data[i] << " "; 
        }
    }*/


    // Impressão na ordem da fila.
    /*if(mSize != 0){
        if(tail>=head){
        for(int i = head; i <= tail; i++){
                cout << data[i] << " ";
            }
        }else{
            for(int i = head; i < mSize; i++){
                cout << data[i] << " ";
            }
            for(int i = 0; i <= tail; i++){
                cout << data[i] << " ";
            }
        }
    } */
    cout << endl;
}

int main(){
    int maxCapacity;
    cin >> maxCapacity;

    circularQueue q1(maxCapacity);

    char choice;
    int value;
    do{
        cin >> choice;
        switch(choice){
            case 'e':
                cin >> value;
                q1.enqueue(value);
                break;
            case 'd':
                cout << q1.dequeue() << endl;
                break;
            case 'i':
                q1.info();
                break;
        }
    }while(choice != 't');

    return 0;
}