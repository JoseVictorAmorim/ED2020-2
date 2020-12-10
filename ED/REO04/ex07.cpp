#include <iostream>
#include <string>
using namespace std;


class noh{
    friend class doubleList;
    private:
        int data;
        noh *nextNoh;
        noh* previousNoh;

    public:
        noh(int value);
};

noh::noh(int value){
    data = value;
    nextNoh = NULL;
    previousNoh = NULL;
}

class doubleList{
    private:
        int mSize;
        noh *first; 
        noh *last;
        void removeAll();
    public:
        // construtores e destrutores
        doubleList();
        ~doubleList();


        //inserção, remoção e busca
        inline void insert(int d);
        void insertEnd(int d);
        
        int search(int value);

        void print();
        bool empty();

        void removeRepeated();
        //void removeBegin();
        //void removeValue(int value);
};

doubleList::doubleList(){
    mSize = 0;
    first = NULL;
    last = NULL;
}

doubleList::~doubleList(){
    removeAll();
}

void doubleList::removeAll(){
    noh* aux = first;
    noh* temp;
    
    while(aux != NULL){
        temp = aux;
        aux = aux->nextNoh;
        delete temp;
    }

    mSize = 0;
    first = NULL;
    last = NULL;
}

void doubleList::insert(int d){
    insertEnd(d);
}

void doubleList::insertEnd(int d){
    noh* newNoh = new noh(d);

    if(empty()){
        first = newNoh;
        last = newNoh;
    }else{
        last->nextNoh = newNoh;
        newNoh->previousNoh = last; 
        last = newNoh;
    }
    mSize++;
}

int doubleList::search(int value){
    noh* aux = first;
    int auxPosition = 0;

    while((aux != NULL) and (aux->data != value)){
        auxPosition++;
        aux = aux->nextNoh;
    }

    if(aux == NULL){
        auxPosition = -1;
    }

    return auxPosition;
}

void doubleList::print(){
    noh* aux = first;

    while(aux != NULL){
        cout << aux->data << " ";
        aux = aux->nextNoh;
    }
    cout << endl;

    aux = last;
    while(aux != NULL){
        cout << aux->data << " ";
        aux = aux->previousNoh;
    }
    cout << endl;
}

bool doubleList::empty(){
    return (mSize == 0);
}

void doubleList::removeRepeated(){
    if(empty()){
        return;
    }
    noh* current = first;
    noh* aux = current->nextNoh;
        
    while(current->nextNoh != NULL){
        while(aux != NULL){
            if(aux->data == current->data){
                noh* mPrevious = aux->previousNoh;
                noh* mNext = aux->nextNoh;

                mPrevious->nextNoh= mNext;
                if(mNext != NULL){
                    mNext->previousNoh = mPrevious;
                }else{
                    last = aux->previousNoh;    
                }
                delete aux;
                mSize--;
                aux = mPrevious;            
            }
            aux = aux->nextNoh;
        } 
        current = current->nextNoh;
        aux = current->nextNoh;
    }
}
   

int main(){
    doubleList myList;

    int value, quantity;
    cin >> quantity;

    for(int i = 0; i < quantity; i++){
        cin >> value;
        myList.insert(value);
    }

    myList.removeRepeated();
    myList.print();
    return 0;
}
