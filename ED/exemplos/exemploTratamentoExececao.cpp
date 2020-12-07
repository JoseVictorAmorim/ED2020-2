#include <iostream>
#include <string>
#include <stdexcept>
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
        //void reversePrintAux(noh* myNoh);
    public:
        // construtores e destrutores
        doubleList();
        doubleList(const doubleList& mList);
        ~doubleList();

        //sobercarga do operador de atribuição
        doubleList& operator=(const doubleList& mList);

        //inserção, remoção e busca
        inline void insert(int d);
        void insertEnd(int d);
        void insertBegin(int d);
        void insertOnPosition(int position, int d);
        bool search(int value, int& position);

        void print();
       // void reversePrint();
        bool empty();

        void removeEnd();
        void removeBegin();
        void removeValue(int value);
};

doubleList::doubleList(){
    mSize = 0;
    first = NULL;
    last = NULL;
}

//construtor de cópia
doubleList::doubleList(const doubleList& mList){
    mSize = 0;
    first = NULL;
    last = NULL;

    noh* aux = mList.first;
    while(aux != NULL){
        insertEnd(aux->data);
        aux = aux->nextNoh;
    }
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

doubleList& doubleList::operator=(const doubleList& mList){
    removeAll();

    noh* aux = mList.first;

    while(aux != NULL){
        insertEnd(aux->data);
        aux = aux->nextNoh;
    }

    return *this;
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

void doubleList::insertBegin(int d){
    noh* newNoh = new noh(d);

    if(empty()){
        first = newNoh;
        last = newNoh;
    }else{
        newNoh->nextNoh = first;
        first->previousNoh = newNoh;
        first = newNoh;
    }
    mSize++;
}

void doubleList::insertOnPosition(int position, int d){
    noh* newNoh = new noh(d);

    if((position <= mSize) and (position >= 0)){
        if(empty()){
            first = newNoh;
            last = newNoh;
        }else if(position == 0){
            newNoh->nextNoh = first;
            first->previousNoh = newNoh;
            first = newNoh;
        }else if(position == mSize){
            last->nextNoh = newNoh;
            newNoh->previousNoh = last;
            last = newNoh;
        }else{
            noh* aux = first;
            int auxPosition = 0;

            while(auxPosition < (position-1)){
                aux = aux->nextNoh;
                auxPosition++;
            }
            newNoh->nextNoh = aux->nextNoh;
            aux->nextNoh->previousNoh = newNoh;
            aux->nextNoh = newNoh;
            newNoh->previousNoh = aux;
        }
        mSize++;
    }else{
        throw runtime_error("ERRO: Posicao inexistente");
    }
}

bool doubleList::search(int value, int& position){
    noh* aux = first;
    position = 0;

    while((aux != NULL) and (aux->data != value)){
        position++;
        aux = aux->nextNoh;
    }

    if(aux == NULL){
        position = -1;
        return false;
    }   
    return true;
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

void doubleList::removeEnd(){
    if(empty()){
        cerr << "REMOVENDO DE LISTA VAZIA VELHO? AI NAO PORRA" << endl;
        exit(EXIT_FAILURE);
    }

    noh* removed = last;
    last = last->previousNoh;
    if(last != NULL){
        last->nextNoh = NULL;
    }
    delete removed;
    mSize--;
    if(empty()){
        last = NULL;
    }
}
   
void doubleList::removeBegin(){
    if(empty()){
        cerr << "REMOVENDO DE LISTA VAZIA VELHO? AI NAO PORRA" << endl;
        exit(EXIT_FAILURE);
    }

    noh* removed = first;
    first = first->nextNoh;
    if(first!=NULL){
        first->previousNoh = NULL;
    }
    delete removed;
    mSize--;

    if(empty()){
        last = NULL;
    }
}

void doubleList::removeValue(int value){
    noh* aux = first;

    while((aux != NULL) and (aux->data != value)){
        aux = aux->nextNoh;
    }   
    if(aux == NULL){
        cerr << "Dado inexistente na fila" << endl;
        exit(EXIT_FAILURE);
    }else{
        noh* mPrevious = aux->previousNoh;
        noh* mNext = aux->nextNoh;

        if(mPrevious != NULL){
            mPrevious->nextNoh= mNext;
        }else{
            first = aux->nextNoh;
        }
        
        if(mNext != NULL){
            mNext->previousNoh = mPrevious;
        }else{
            last = aux->previousNoh;    
        }
        delete aux;
        mSize--;
        if(empty()){
            first = NULL;
            last = NULL;
        }
    }
}

int main(){
    doubleList myList;
    
    cout << "*** TESTE DE LISTA *** " << endl;
    cout << "Quantidade de valores a inserir: ";
    int value, num;
    cin >> num;

    for(int i = 0; i < num; i++){
        cin >> value;
        myList.insert(value);
    }

    myList.print();

    myList.insertBegin(18);
    try{
        myList.insertOnPosition(12, 25);
    }catch (exception& e){
        cout << e.what() << endl;
    }
    myList.print();;

    int p;
    bool x = myList.search(29, p);


    if(x){
        cout << "Encontrado na posição: " << p << endl;
    }else{
        cout << "Elemento nao encontrado" << endl;
    }

    
    return 0;
}
