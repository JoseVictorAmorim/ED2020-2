#include <iostream>
#include <string>
using namespace std;


class noh{
    friend class list;
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

class list{
    private:
        int mSize;
        noh *first; 
        noh *last;
        void removeAll();
        void reversePrintAux(noh* myNoh);
    public:
        // construtores e destrutores
        list();
        list(const list& mList);
        ~list();

        //sobercarga do operador de atribuição
        list& operator=(const list& mList);

        //inserção, remoção e busca
        inline void insert(int d);
        void insertEnd(int d);
        void insertBegin(int d);
        void insertOnPosition(int position, int d);
        int search(int value);

        void print();
        void reversePrint();
        bool empty();

        void removeEnd();
        void removeBegin();
        void removeValue(int value);
};

list::list(){
    mSize = 0;
    first = NULL;
    last = NULL;
}

//construtor de cópia
list::list(const list& mList){
    mSize = 0;
    first = NULL;
    last = NULL;

    noh* aux = mList.first;
    while(aux != NULL){
        insertEnd(aux->data);
        aux = aux->nextNoh;
    }
}

list::~list(){
    removeAll();
}

void list::removeAll(){
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

list& list::operator=(const list& mList){
    removeAll();

    noh* aux = mList.first;

    while(aux != NULL){
        insertEnd(aux->data);
        aux = aux->nextNoh;
    }

    return *this;
}

void list::insert(int d){
    insertEnd(d);
}

void list::insertEnd(int d){
    noh* newNoh = new noh(d);

    if(empty()){
        first = newNoh;
        last = newNoh;
    }else{
        last->nextNoh = newNoh;
        last = newNoh;
    }
    mSize++;
}

void list::insertBegin(int d){
    noh* newNoh = new noh(d);

    if(empty()){
        first = newNoh;
        last = newNoh;
    }else{
        newNoh->nextNoh = first;
        first = newNoh;
    }
    mSize++;
}

void list::insertOnPosition(int position, int d){
    noh* newNoh = new noh(d);

    if((position <= mSize) and (position >= 0)){
        if(empty()){
            first = newNoh;
            last = newNoh;
        }else if(position == 0){
            newNoh->nextNoh = first;
            first = newNoh;
        }else if(position == mSize){
            last->nextNoh = newNoh;
            last = newNoh;
        }else{
            noh* aux = first;
            int auxPosition = 0;

            while(auxPosition < (position-1)){
                aux = aux->nextNoh;
                auxPosition++;
            }
            newNoh->nextNoh = aux->nextNoh;
            aux->nextNoh = newNoh;
        }
        mSize++;
    }else{
        cerr << "POSICAO INEXISTENTE" << endl;
        exit(EXIT_FAILURE);
    }
}

int list::search(int value){
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

void list::print(){
    noh* aux = first;

    while(aux != NULL){
        cout << aux->data << " ";
        aux = aux->nextNoh;
    }
    cout << endl;
}

void list::reversePrint(){
    reversePrintAux(first);
    cout << endl;
}

void list::reversePrintAux(noh* myNoh){
    if(myNoh != NULL){
        reversePrintAux(myNoh->nextNoh);
        cout << myNoh->data << " ";
    }
}

bool list::empty(){
    return (mSize == 0);
}

void list::removeEnd(){
    if(empty()){
        cerr << "REMOVENDO DE LISTA VAZIA VELHO? AI NAO PORRA" << endl;
        exit(EXIT_FAILURE);
    }

    noh* aux = first;
    noh* previous;

    while(aux->nextNoh != NULL){
        previous = aux;
        aux = aux->nextNoh;
    }

    delete last;
    previous->nextNoh = NULL;
    last = previous; 
    mSize--;
    if(empty()){
        first = NULL;
    }
}

void list::removeBegin(){
    if(empty()){
        cerr << "REMOVENDO DE LISTA VAZIA VELHO? AI NAO PORRA" << endl;
        exit(EXIT_FAILURE);
    }

    noh* removed = first;
    first = first->nextNoh;
    delete removed;
    mSize--;
    if(empty()){
        last = NULL;
    }
}

void list::removeValue(int value){
    noh* aux = first;
    noh* previous;
    int auxPosition = 0;

    while((aux != NULL) and (aux->data != value)){
        auxPosition++;;
        previous = aux;
        aux = aux->nextNoh;
    }

    if(aux == NULL){
        auxPosition = -1;
        cout << "Dado inexistente na fila" << endl;
    }else{
        previous->nextNoh = aux->nextNoh;
        aux = previous;
        mSize--;
        if(empty()){
            first = NULL;
        }
    }
}

int main(){
    list myList;
    
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
    myList.insertOnPosition(3, 25);
    myList.print();
    myList.reversePrint();

    cout << myList.search(0) << endl;
    cout << myList.search(50) << endl;
    cout << myList.search(12) << endl;

    cout << "SOBRECARGA DO CONSTRUTOR DE COPIA" << endl;
    list otherList(myList);
    otherList.print();
    otherList.reversePrint();

    cout << "SOBRECARGA DO OPERADOR DE ATRIBUIÇÃO" << endl;
    list moreOneList;
    moreOneList = otherList;

    moreOneList.print();
    moreOneList.reversePrint();
    
    cout << "EI, PSIU" << endl;
    moreOneList.removeEnd();
    moreOneList.print();
    moreOneList.removeEnd();
    moreOneList.print();

    cout << "EI, PSIU" << endl;
    moreOneList.removeBegin();
    moreOneList.print();
    moreOneList.removeBegin();
    moreOneList.print();

    int v;
    cin >> v;

    moreOneList.removeValue(v);
    moreOneList.print();

    return 0;
}
