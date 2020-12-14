//82.4 no dredd
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

        bool member(int k); //Membro(S,x)

        int getSize(); //Tamanho(S)

        void print(); //Imprime(S)
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
            return -1;
        }
        if(d.key == k){
            return position;
        }
        position = (position+1)%capacity;
    }while(position != finalPosition);

    return -1; //percorreu todo vetor e não encontrou
}

//adiciona(S,x)
//Adiciona o elemento x no conjunto S, descartando duplicatas. 
//Se x já fizer parte de S, não é gerado erro, apenas não se modifica o conteúdo de S.
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
//Remove o elemento x do conjunto S. 
//Se x não fizer parte de S, não é gerado erro, apenas não se modifica o conteúdo de S.
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
//Retorna true se o item x for membro do conjunto S.
bool hashTable::member(int k){
    int y = search(k);
    if(y == -1){
        return false;
    }else{
        return  true;
    }
}

//tamanho(S)
//Retorna o número de elementos de S.
int hashTable::getSize(){
    return mSize;
}

//imprime(S)
//Imprime os elementos de S. 
//Caso o conjunto seja vazio, imprime {}
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

    int myKey;

    for(int i = 0; i < 10; i++){
        cin >> myKey;
        myTable.insert(myKey); //1.Constrói o conjunto a partir de uma lista de 10 elementos
        //digitada pelo usuário.
    }
    
    for(int i = 0; i < 3; i++){
        cin >> myKey;
        myTable.remove(myKey); //2.Remove três elementos indicados pelo usuário
    }
    
    int seek;
    for(int i = 0; i < 2; i++){
        cin >> seek;
        bool x = myTable.member(seek); //3.Verifica se um dado valor informado pelo usuário é membro do conjunto.

        if(x){ //imprima 1 para pertinência e -1 para não-pertinência.
            cout << 1 << endl; 
        }else{
            cout << -1 << endl;
        }
    } //4.Repete a operação de verificação de pertinência para outro valor informado pelo usuário.

    myTable.print(); //5.Imprime o conteúdo do conjunto, na ordem em que estão armazenados.

    for(int i = 0; i < 3; i++){ //6.Adiciona três novos elementos indicados pelo usuário
        cin >> myKey;
        myTable.insert(myKey);
    }

    myTable.print(); //7.Imprime novamente o conteúdo do conjunto, na ordem em que estão armazenados.

    return 0;
}
