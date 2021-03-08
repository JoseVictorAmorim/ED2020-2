#include <iostream>
using namespace std;
typedef int Dado;

class noh
{ 
    friend class lista;
    
    private:
        const Dado dado;
        noh* proximo;
        
    public:
        noh(Dado d = 0);
};
noh::noh(Dado d) : dado(d) 
{
    proximo = NULL;
}
class lista 
{
    private: // atributos
        noh* primeiro;
        noh* ultimo;
        int tamanho;
        
    public: // metodos
        lista();
        ~lista();
        void Insere(Dado dado);
        void InserePos(Dado dado, int pos);
        void Remove(int posicao);
        int Posicao(Dado valor);
        void Imprime();
        void Troca();
        inline bool VaziaVer();
};
lista::lista() 
{
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}
lista::~lista()
{
    noh* iter = primeiro;
    noh* proximo = NULL;
    while (iter != NULL) {
        proximo = iter->proximo;
        delete iter;
        iter = proximo;
    }
}
void lista::Imprime() 
{
    noh* aux = primeiro;
    while (aux != NULL) 
    {
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
    cout << endl;
}
void lista::Troca()
{
	noh* atual = primeiro;
	noh* aux2 = atual->proximo;
	noh* aux;
	
	while (atual->proximo != NULL){
		if (atual == primeiro){
			aux = aux2->proximo;
			aux2->proximo = atual;
			primeiro = atual->proximo;
			atual->proximo = aux;
			atual = aux;
			aux2 = aux->proximo;
		}
		else {
			aux = aux2->proximo;
			aux2->proximo = atual;
			atual->proximo = aux;
			atual = aux;
			aux2 = aux->proximo;
		}
	}
}
void lista::Insere(Dado dado) 
{
	noh* aux = new noh(dado);
	if(aux)
	{
		aux->proximo=NULL;
		if(primeiro == NULL)
		{	
			primeiro = aux;
			ultimo = aux;	
		}
		else
		{
			ultimo->proximo = aux;
			ultimo = aux;
		}
		tamanho++;
	}
}
void lista::InserePos(Dado dado, int posicao) 
{
	if(posicao >= 0 and posicao <= tamanho)
	{
		noh* aux = new noh(dado); // cria um ponteiro q armazena o valor que queremos
		if ( aux )
		{
			if(primeiro == NULL) //LISTA VAZIA
			{
				primeiro = aux;
				ultimo = aux;	
			}
			else // percorre o ponteiro ate achar o elemento anterior, guardano o endereço de memoria pro elemento desejado (proximo)
			{
				int cont = 0; //contador ~>posicao
				noh* nav = primeiro; // nav ~>ponteiro q vai apontando para os elementos da lista
				while(cont < posicao-1) // para em um a menos
				{
					nav = nav->proximo; // nav copia o endereço de memoria para o proximo que é o elemnto que queremos
					cont++;
				}
				if(posicao == 0) // se for no comeco
				{
					aux->proximo = nav; // o proximo e nav
					primeiro = aux; // o ponteiro que indica o começo da lista aponta pra o aux, que e o elemento
				}
				else if(posicao == tamanho) // se for no final
				{
					ultimo = aux;
					//ultimo->proximo = aux;?
				}
				else // se for em uma posicao aleatória
				{
					aux->proximo = nav->proximo; //o proximo do novo elemento  aponta pra posicao encontrada
					nav->proximo = aux; // a posicao muda para o auxiliar
				}				
			}
			tamanho++;
		}
	}
}
// remove o item da posição passada por parâmetro
// Atenção - o código deve tratar de posição inválidas
void lista::Remove(int posicao) {	
	int cont=0;	
	if(posicao >= 0 and posicao < tamanho) {// posicao valida{
		noh* nav = primeiro; // percorrer toda a lista
		while(cont < posicao-1){
			nav = nav->proximo; // nav fica com o endereço de memoria do que queremos
			cont++;
		}if(posicao == 0){
			primeiro = nav->proximo; // o primeiro aponta pro proximo do primeiro
			delete(nav); // deleta 
		}else if(posicao == tamanho-1) {
			delete(nav->proximo); // no penultimo deleta o ponteiro pro proximo
			nav->proximo = primeiro; // coloca o proximo como vazio
			ultimo = nav; // aponta o ponteiro do ultimo pro penultimo e encerra a lista nele
			// o ultimo ainda existe mas nao esta conectado a lista
		}
		else{
			noh* aux = nav->proximo; // auxiliar que guarda o proximo do que queremos
			nav->proximo = nav->proximo->proximo; // o proximo do que queremos pula um e vai pra frente
			delete(aux); // deleta o auxiliar que contem o endereco de memoria que queremos isolando o valor da lista e assim o removendo
		}tamanho--;
	}
}
// procura por um elemento e retorna a posição ou -1 se não encontrado
int lista::Posicao(Dado valor) 
{
	noh* nav = primeiro;// o contador so q com um ponteiro e para ponteiros
	int cont = 0;
	while(nav != NULL and valor != nav->dado) // enquanto nao chegar no fim (ultimo = null) 
	//e o valor for diferente do que esta no momento ( quer dizer que chegou )
	{
		cont++; //guarda as posições
		nav = nav->proximo;
	}
	if(nav == NULL) // percorreu a lista ate o fim
	{
		return -1;
	}
	else
	{
		return cont; 
	}
}
// verifica se a lista está vazia
inline bool lista::VaziaVer()  // inline?
{
	if(tamanho == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int main() 
{ 
    lista list;
    int valor;
	while (valor != -1){
		cin >> valor;
		if (valor != -1){
		list.Insere(valor);
		}
	}
    list.Troca();
    list.Imprime();
    return 0;
}