#include <iostream>
#include <string>
using namespace std;

int hashFunction(int k){
    return k % 101;
}

struct data{
    int key;
    int value;
};
class hashTable{
    private:
        int mSize;
        int capacity;
        data* table;
    public:
        // construtores e destrutores
        hashTable(int cap = 101);
        ~hashTable();

        int search(int k); 

        void insert(int k); //Adiciona(S,x)

        void remove(int k); //Remove(S,x)

        bool member(int k); //membro(S,x)

        int getSize(); //tamanho(S)

        void print(); //imprime(S)
};

hashTable::hashTable(int cap){
    capacity = cap;
    table = new data[capacity];
    for(int i = 0; i < capacity; i++){
        table[i].key = -1;
        table[i].value = -1;
    }
    mSize = 0;
}

hashTable::~hashTable(){
    delete[] table;
}

int hashTable::search(int k){
    int position = hashFunction(k);
    int finalPosition = position;
    data d;
    do{
        d = table[position];
        if(d.value == -1){
            return -1;;
        }
        if(d.key == k){
            return position;
        }
        position = (position+1)%capacity;
    }while(position != finalPosition);

    return -1;; //percorreu todo vetor e não encontrou
}

//adiciona(S,x)
void hashTable::insert(int k){
    if(mSize == capacity){
        return;
    }

    if(search(k) != -1){
        return;
    }

    int position = hashFunction(k);

    while(table[position].value != -1){
        position = (position+1)%capacity;
    }
    table[position].key = k;
    table[position].value = 1;
    mSize++;
}

//remove(S,x)
void hashTable::remove(int k){
    if(mSize == 0){
        return;
    }

    int position = search(k);
    if(position == -1){
        return;
    }
    table[position].value = -1;
    table[position].key = -1;
    mSize--;
}

//membro(S,x)
bool hashTable::member(int k){
    int y = search(k);
    if(y == -1){
        return false;
    }else{
        return  true;
    }
}

//tamanho(S)
int hashTable::getSize(){
    return mSize;
}

//imprime(S)
void hashTable::print(){
    if(mSize == 0){
        cout << "{}";
    }else{
        for(int i = 0; i < capacity; i++){
            if(table[i].value != -1){
                cout << table[i].key << " ";
            }
        }
    }
    cout << endl;
}

int main(){
    hashTable myTable;

    int myKey;;

    for(int i = 0; i < 10; i++){
        cin >> myKey;
        myTable.insert(myKey);
    }
    
    for(int i = 0; i < 3; i++){
        cin >> myKey;
        myTable.remove(myKey);
    }
    

    int seek;
    for(int i = 0; i < 2; i++){
        cin >> seek;
        bool x = myTable.member(seek);
        if(x){
            cout << 1 << endl;
        }else{
            cout << -1 << endl;
        }
    }


    
    myTable.print();

    for(int i = 0; i < 3; i++){
        cin >> myKey;
        myTable.insert(myKey);
    }
   
    myTable.print();

    return 0;
}
