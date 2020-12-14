#include <iostream>
using namespace std;

typedef string car;

class noh{
    friend class queue;

    private:
        car data;
        noh *nextNoh;

    public:
        noh(car value);
};

noh::noh(car value){
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
        void enqueue(car valor);
        car dequeue();
        bool empty();
        void carRemoval(car value);
        car headPeek();
        void printQueue();
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

void queue::enqueue(car value){
    noh *temp = new noh(value);
    if(this->empty()){
        head = temp;
    }else{
        tail->nextNoh = temp;
    }
    tail = temp;
    mSize++;
}

car queue::dequeue(){
    car value = head->data;
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

car queue::headPeek(){
    return(head->data);
}

void queue::printQueue(){
    queue auxQueue;
    int count = (int)mSize;
    while(count > 0){
        auxQueue.enqueue(this->dequeue());
        cout << auxQueue.headPeek() << endl;
        this->enqueue(auxQueue.dequeue());
        count--;
    }
}

void queue::carRemoval(car value){
    queue auxQueue;
    bool onTheQueue = false;
    int initialSize = this->getSize();
    int count = 0;
    car removed;
    while(not onTheQueue and count < initialSize){
        if(this->headPeek() == value){
            onTheQueue = true;
            removed = dequeue();
        }else{
            auxQueue.enqueue(this->dequeue());
        }
        count++;
    }
    
    while(not auxQueue.empty()){
        this->enqueue(auxQueue.dequeue());
    }

    if(not onTheQueue){
        cout << "NAO ENCONTRADO" << endl;
    }else{
        cout << count << endl;
        printQueue();
    }
}

int main(){
    queue q1;
    char choice;
    car value;
    do{
        cin >> choice;
        switch(choice){
            case 'E':
                cin >> value;
                q1.enqueue(value);
                break;
            case 'D':
                cin >> value;
                q1.carRemoval(value);
                break;
        }
    }while(choice != 'S');



    return 0;
}
