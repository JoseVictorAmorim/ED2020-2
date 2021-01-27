#include <iostream>
using namespace std;

typedef int Data;

class noh{
    friend class BST;
    private:
        noh* mLeft;
        noh* mRight;
        noh* mFather;
        Data value;
    public:
        noh(Data v);
};

noh::noh(Data v){
    //Construtor
    mLeft = NULL;
    mRight = NULL;
    mFather = NULL;
    value = v;
}

class BST{
    private:
        noh* root;
        
        noh* searchAux(noh* aux);

        noh* minAux(noh* current);

        void recursiveDestructor(noh* current);
    public:
        //construtor/destrutor
        BST();
        ~BST();

        //inserir
        void insert(Data d);

        void transplant(noh* oldNoh, noh* newNoh);

        void remove(Data d);

        //impressão
        void printOrder(){ printOrder(root); };
        void printPreOrder(){printPreOrder(root);};

        void printOrder(noh* current);
        void printPreOrder(noh* current);
};

BST::BST(){
    root = NULL;
}

BST::~BST(){
    recursiveDestructor(root);
}   

void BST::recursiveDestructor(noh* current){
    if(current != NULL){
        recursiveDestructor(current->mLeft);
        recursiveDestructor(current->mRight);
        delete current;
    }
}

void BST::insert(Data d){
    noh* newNoh = new noh(d);

    if(root == NULL){
        root = newNoh;
    }else{
        noh* current = root;
        noh* previous = NULL;
    
        while(current != NULL){
            previous = current;
            if(current->value > d){
                current = current->mLeft;
            }else{
                current = current->mRight;
            }
        }

        newNoh->mFather = previous;

        if(previous->value > newNoh->value){
            previous->mLeft = newNoh;
        }else{
            previous->mRight = newNoh;
        }
    }
}

noh* BST::searchAux(noh* aux){
    noh* current = root;

    while(current != NULL){
        if(current->value == aux->value){
            return current;
        }else if(current->value > aux->value){
            current = current->mLeft;
        }else{
            current = current->mRight;
        }
    }
    return current;
}

void BST::transplant(noh* oldNoh, noh* newNoh){
    if(root == oldNoh){
        root = newNoh;
    }else if(oldNoh == oldNoh->mFather->mLeft){
        oldNoh->mFather->mLeft = newNoh;
    }else{
        oldNoh->mFather->mRight = newNoh;
    }

    if(newNoh != NULL){
        newNoh->mFather = oldNoh ->mFather;
    }
}

void BST::remove(Data d){
    noh* aux = new noh(d);

    noh* removal = searchAux(aux);

    if(removal == NULL){
        cerr << "ERRO" << endl;
    }else{
        if(removal->mLeft == NULL){
            transplant(removal, removal->mRight);
        }else if(removal->mRight == NULL){
            transplant(removal, removal->mLeft);
        }else{
            noh* successor = minAux(removal->mRight);
            if(successor->mFather != removal){
                transplant(successor, successor->mRight);
                successor->mRight = removal->mRight;
                successor->mRight->mFather = successor;
            }
            transplant(removal, successor);
            successor->mLeft = removal->mLeft;
            successor->mLeft->mFather = successor;
        }
        delete removal;
    }
}

noh* BST::minAux(noh* current){
    while(current->mLeft != NULL){
        current = current->mLeft;
    }
    return current;
}

void BST::printOrder(noh* current){
    if(current != NULL){
        printOrder(current->mLeft);
        cout << current->value << endl;
        printOrder(current->mRight);
    }
}

void BST::printPreOrder(noh* current){
    if(current != NULL){
        cout << current->value << endl;
        printPreOrder(current->mLeft);
        printPreOrder(current->mRight);
    }
}

int main(){
    BST myTree;
    char choice;
    cin >> choice;
    Data key;
    do{
        switch(choice){
            case 'i':
                cin >> key;
                myTree.insert(key);
                break;
            case 'r':
                cin >> key;
                myTree.remove(key);
                break;
            case 'o':
                myTree.printOrder();
                cout << endl;
                break;
            case 'p':
                myTree.printPreOrder();
                cout << endl;
                break;
            case 'q':
                break;
            default:
                cout << "Comando Invalido!";
            }
            cin >> choice;
    }while(choice != 'q');
    
    return 0;
}
