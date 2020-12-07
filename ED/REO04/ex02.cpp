#include <iostream>
#include <string>
using namespace std;

typedef string word;

class noh{
    friend class doubleList;
    private:
        word data;
        noh *nextNoh;
        noh* previousNoh;

    public:
        noh(word value);
};

noh::noh(word value){
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
        // construtor/destrutor
        doubleList();
        ~doubleList();

        //inserção
        inline void insert(word d);
        void insertEnd(word d);

        //impressão
        void print();
        void reversePrint();

        //verificacao se está vazia
        bool empty();

        //inverte(), pedida no exercicio
        void inverte();
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

void doubleList::insert(word d){
    insertEnd(d);
}

void doubleList::insertEnd(word d){
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

void doubleList::print(){
    noh* aux = first;

    while(aux != NULL){
        cout << aux->data << " ";
        aux = aux->nextNoh;
    }
    cout << endl;
}

void doubleList::reversePrint(){
    noh* aux = last;
    while(aux != NULL){
        cout << aux->data << " ";
        aux = aux->previousNoh;
    }
    cout << endl;
}

bool doubleList::empty(){
    return(mSize == 0);
}

void doubleList::inverte(){
    noh* aux1 = last;
    noh* aux2;
    for(int i = 0; i < mSize; i++){
        aux2 = aux1->previousNoh;
        aux1->previousNoh = aux1->nextNoh;
        aux1->nextNoh = aux2;
        aux1 = aux2;
    }
    noh* aux = first;
    first = last;
    last = aux;
}

int main(){
    doubleList myList;
    char choice;
    word w;
    do{
        cin >> choice;
        switch(choice){
            case 'I':
                cin >> w;
                myList.insert(w);
                break;
            case 'X':
                myList.inverte();
                break;
            case 'P':
                myList.print();
                break;
            case 'R':
                myList.reversePrint();
                break;
        }
    }while(choice != 'Q');
 
    myList.print();
    myList.reversePrint();
 
    return 0;
}
