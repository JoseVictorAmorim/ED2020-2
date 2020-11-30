#include <iostream>
#include <string>
using namespace std;

class noh{
    friend class queue;

private:
    int data;
    noh *nextNoh;

public:
    noh(int value);
};

noh::noh(int value){
    data = value;
    nextNoh = NULL;
}

class queue{
    private:
        unsigned mSize;
        noh *head; //front
        noh *tail; //rear

    public:
        queue();
        ~queue();
        unsigned getSize();

        void cleanQueue();
        void enqueue(int valor);
        int dequeue();
        bool empty();
};

queue::queue(){
    head = NULL;
    tail = NULL;
    mSize = 0;
}

queue::~queue(){
    cleanQueue();
}

void queue::cleanQueue(){
    while (not empty()){
        dequeue();
    }
}

unsigned queue::getSize(){
    return mSize;
}

void queue::enqueue(int value){
    noh *temp = new noh(value);
    if(this->empty()){
        head = temp;
    }else{
        tail->nextNoh = temp;
    }
    tail = temp;
    mSize++;
}

int queue::dequeue(){
    int value = head->data;
    noh *temp = head;
    head = temp->nextNoh;
    delete temp;
    mSize--;
    if(this->empty()){
        tail = NULL;
    }
    return value;
}
     
bool queue::empty(){
    return (mSize == 0);
}

int main(){
    


    return 0;
}
