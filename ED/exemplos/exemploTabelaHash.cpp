#include <iostream>
#include <string>
using namespace std;

int hashFunction(int k){
    return k % 11;
}

class noh{
    friend class hashTable;
    private:
        int key;
        int data;
        noh *nextNoh;

    public:
        noh(int value, int k);
};

noh::noh(int value, int k){
    data = value;
    key = k;
    nextNoh = NULL;
}

class hashTable{
    private:
        //int mSize;
        int capacity;
        noh **table;
        void removeAll();
    public:
        // construtores e destrutores
        hashTable(int cap = 11);
        ~hashTable();

        //inserção de value com chave k;
        void insert(int value, int k);

        //recuperação
        int recover(int k);

        //alteração
        void changeValue(int value, int k);

        //remoção de valor vinculado a chave
        void removeValue(int k);

        //print para debug
        void print();
};

hashTable::hashTable(int cap){
    capacity = cap;
    table = new noh*[capacity];
    for(int i = 0; i < capacity; i++){
        table[i] = NULL;
    }
}

hashTable::~hashTable(){
    removeAll();
}

void hashTable::removeAll(){
    for(int i = 0; i < capacity; i++){
        noh* temp = table[i];
        while(temp != NULL){
            noh* aux = temp;
            temp = temp->nextNoh;
            delete aux;
        }
    }
    delete[] table;
}

void hashTable::insert(int value, int k){
    int position = hashFunction(k);
    noh* current = new noh(value, k);

    if(table[position] == NULL){
        current->nextNoh = NULL;
        table[position] = current;
    }else{
        noh* current = table[position];
        if(current->nextNoh == NULL){
            noh* newNoh = new noh(value, k);
            current->nextNoh = newNoh;
        }else{
            while(current->nextNoh != NULL){
                current = current->nextNoh;
            }
            noh* newNoh = new noh(value, k);
            current->nextNoh = newNoh;
        }
    }
}

int hashTable::recover(int k){
    int position = hashFunction(k);

    if((table[position] != NULL) and (table[position]->key == k)){
        return table[position]->data;
    }else{
        noh* current = table[position];

        while((current != NULL) and (current->key != k)){
            current = current->nextNoh;
        }

        if((current != NULL) and (current->key == k)){
            return current->data;
        }else{
            return -1;
        }

    }
}

void hashTable::changeValue(int value, int k){
    int position = hashFunction(k);

    if(table[position] == NULL){
        cerr << "ERRO NA ALTERAÇÃO" << endl;
    }else{
        noh* current = table[position];

        if((current->nextNoh == NULL) and (current->key != k)){
            cerr << "ERRO NA ALTERAÇÃO" << endl;
        }else if((current->nextNoh == NULL) and (current->key == k)){
            current->data = value;
        }else if(current->nextNoh != NULL){
            bool aux = false;

            while((current->nextNoh != NULL) and (not aux)){
                if(current->key == k){
                    current->data = value;
                    aux = true;
                }
                current = current->nextNoh;
            }

            if(not aux){
                cerr << "ERRO NA ALTERAÇÃO" << endl;
            }
        }
    }
}

void hashTable::removeValue(int k){
    int position = hashFunction(k);

    if((table[position] != NULL) and (table[position]->key != k)){
        noh* aux = table[position];
        table[position] = table[position]->nextNoh;
        delete aux;
    }else{
        noh* previous = NULL;
        noh* current = table[position];

        while((current != NULL) and (current->key != k)){
            previous = current;
            current = current->nextNoh;
        }

        if((current != NULL) and (current->key == k)){
            previous->nextNoh = current->nextNoh;
            delete current;
        }else{
            cerr << "Erro na remoção" << endl;
        }
    }
}

void hashTable::print(){
    noh* current;
    for (int i = 0; i < capacity; i++) {
        cout << i << ":";
        current = table[i];
        while (current != NULL) {
            cout << "[" << current->key << "/"
                 << current->data << "]->";
            current = current->nextNoh;
        }
        cout << "NULL  ";
    }
}

int main( ) {
    hashTable th;
    int quantity;
    int mKey;
    int mValue;

    // insercao na tabela
    cin >> quantity;
    for (int i=0; i < quantity; i++) {
        cin >> mValue;
        mKey = hashFunction(mValue);
        th.insert(mValue, mKey);
    }

    th.print();

    return 0;
}

