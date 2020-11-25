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
        circularQueue(int maxCapacity);
        ~circularQueue();
        void enqueue(int value);
        int dequeue();
       // void clearQueue();
       // bool empty();
        void info();
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
    head = -1;
    tail = -1;
    capacity = 0;
    mSize = 0;
}

void circularQueue::enqueue(int value){
    if(mSize < capacity){
        tail++;
        tail = tail % capacity;
        data[tail] = value;
        if(mSize == 0){
            head++;
        }
        mSize++;
    }
}

int circularQueue::dequeue(){
    if(mSize > 0){
        int aux = data[head];
        mSize--;
        head++;
        head = head % capacity;    
        return aux;
    }else if(mSize == 0){
        head = -1;
        tail = -1;
    }
    return -1;
}

void circularQueue::info(){
    cout << "tamanho=" << mSize
    << " capacidade=" << capacity
    << " inicio=" << head
    << " fim=" << tail << endl;

    // saida na ordem do vetor
    for(int i = 0; i < mSize; i++){
        cout << data[i] << " "; //Quebra de estrutura, porem pedido pelo exercício
    }
   
    // saida na ordem da fila 
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