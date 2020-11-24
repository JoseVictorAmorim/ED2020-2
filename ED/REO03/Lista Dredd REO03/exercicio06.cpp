#include <iostream>
using namespace std;

class circularQueue{
    private:
        int head;
        int tail;
        int* data;
        unsigned capacity;
        unsigned mSize;
    public:
        circularQueue(int maxCapacity);
        ~circularQueue();
        unsigned getSize();
        void enqueue(int value);
        int dequeue();
        void clearQueue();
        bool empty();
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
        if(mSize > 0){
            head++;
            head = head % capacity;
        }else{
            head = -1;
            tail = -1;
        }
        return aux;
    }else{
        return -1;
    }
}

unsigned circularQueue::getSize(){
    return mSize;
}

void circularQueue::clearQueue(){
    while(not this->empty()){
        this->dequeue();
    }
}

bool circularQueue::empty(){
    return(mSize == 0);
}

void circularQueue::info(){
    cout << "tamanho=" << mSize
    << " capacidade=" << capacity
    << " inicio=" << head
    << " fim=" << tail << endl;

    for(int i = 0; i < capacity; i++){
        cout << data[i] << " "; //Quebra de estrutura, porem pedido pelo exercício
    }
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