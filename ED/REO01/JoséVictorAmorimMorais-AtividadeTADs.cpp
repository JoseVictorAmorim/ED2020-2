/* Definição do projeto: 
	1-Inicialização de todos vetores com 100 posições;

 	2-"Especies" e "Fornecedores" declarados como structs por não conterem métodos;

	3-Incluido no struct "Especies" o atributo "tipo", para classificar a especie;

	4-Incluido na class "Admin" o método "listarEspecies", a fim de dar algum uso para as espécies cadastradas
	e eventuais testes de funcionamento.

*/
#include <iostream>
#include <string>
using namespace std;

struct species
{
	string name;
	string type;
	string plantingPeriod;
	string productionTime;
};

struct provider
{
	string name;
	string product;
	string phoneNumber;
};

class admin
{
private:
	species *speciesList;
	provider *providersList;
	int totalSpecies;
	int totalProviders;

public:
	admin();
	~admin();
	void newSpecie();
	void newProvider();
	void providerSearch(string productProvided);
	void listSpecies();
};

admin::admin()
{
	speciesList = new species[100];
	providersList = new provider[100];
	totalSpecies = 0;
	totalProviders = 0;
}

admin::~admin()
{
	//cout para verificar a entrada no destrutor

	//cout << "Deletando..." << endl;
	delete[] speciesList;
	delete[] providersList;
	totalSpecies = 0;
	totalProviders = 0;
	//cout para verificar a saida do destrutor, e por consequencia o funcionamento do mesmo

	//cout << "Deletado com sucesso!" << endl;
}

void admin::newSpecie()
{
	int typeChoice;
	if (totalSpecies < 99)
	{
		cout << "Insira o nome da especie: ";
		getline(cin, speciesList[totalSpecies].name);
		cout << "Escolha o tipo de especie: " << endl;
		cout << " [1] Flores " << endl;
		cout << " [2] Hortalicas " << endl;
		cout << " [3] Frutas " << endl;
		cout << "-> Escolha uma opcao: ";
		cin >> typeChoice;
		cin.ignore();
		switch (typeChoice)
		{
		case 1:
			cout << "Voce escolheu o tipo \"Flores\"!" << endl;
			speciesList[totalSpecies].type = "Flores";
			break;
		case 2:
			cout << "Voce escolheu o tipo \"Hortalicas\"!" << endl;
			speciesList[totalSpecies].type = "Hortalicas";
			break;
		case 3:
			cout << "Voce escolheu o tipo \"Frutas\"!" << endl;
			speciesList[totalSpecies].type = "Frutas";
			break;
		default:
			cout << "Você não escolheu nenhum tipo válido" << endl;
		}
		cout << "Insira o periodo de plantacao da especie: ";
		getline(cin, speciesList[totalSpecies].plantingPeriod);
		cout << "Insira o tempo de producao da especie: ";
		getline(cin, speciesList[totalSpecies].productionTime);
		cout << "---Especie cadastrada com sucesso---" << endl
			 << endl
			 << endl;
		totalSpecies++;
	}
	else
	{
		cout << "Nao foi possível adicionar nova especie: Capacidade Lotada" << endl;
	}
}

void admin::newProvider()
{
	if (totalProviders < 99)
	{
		cout << "Insira o nome do fornecedor: ";
		getline(cin, providersList[totalProviders].name);
		cout << "Insira o produto do fornecedor: ";
		getline(cin, providersList[totalProviders].product);
		cout << "Insira o numero do fornecedor: ";
		getline(cin, providersList[totalProviders].phoneNumber);
		cout << "--Fornecedor cadastrado com sucesso!---" << endl
			 << endl
			 << endl;
		totalProviders++;
	}
	else
	{
		cout << "Não foi possivel adicionar novo fornecedor: Capacidade Lotada" << endl;
	}
}

void admin::providerSearch(string productProvided)
{
	int counter = 0;
	cout << "=>Lista de vendedores do produto \"" << productProvided << "\":" << endl
		 << "-------------" << endl;
	for (int i = 0; i < totalProviders; i++)
	{
		if (providersList[i].product == productProvided)
		{
			cout << providersList[i].name << endl;
			cout << providersList[i].phoneNumber << endl;
			cout << "-------------" << endl;
			counter++;
		}
	}
	if (counter == 0)
	{
		cout << "Nao ha fornecedores para esse tipo de produto" << endl;
	}
	cout << endl
		 << endl;
}

void admin::listSpecies() //método extra para a listagem das espécies cadastradas
{
	cout << "===Lista de Especies===" << endl;
	for (int i = 0; i < totalSpecies; i++)
	{
		cout << "->Nome: " << speciesList[i].name << endl;
		cout << "->Tipo de cultivo: " << speciesList[i].type << endl;
		cout << "->Periodo de plantacao: " << speciesList[i].plantingPeriod << endl;
		cout << "->Tempo de producao: " << speciesList[i].productionTime << endl;
		cout << "-----------" << endl
			 << endl
			 << endl;
	}
}

int main()
{
	int nSpecies, nProviders;
	admin *administrator = new admin;

	//Ccnsiderando o storytelling da questão, primeiro Morgana cadastra todas espécies que já existem em sua chácara

	cout << "Digite o numero de especies a serem cadastradas:  ";
	cin >> nSpecies;
	cin.ignore();
	for (int i = 0; i < nSpecies; i++)
	{
		administrator->newSpecie();
	}

	//Em sequência, ela registra os fornecedores atuais dos produtos que usa

	cout << "Agora, digite o numero de Fornecedores a serem cadastrados: ";
	cin >> nProviders;
	cin.ignore();
	for (int i = 0; i < nProviders; i++)
	{
		administrator->newProvider();
	}

	/*E por ultimo, ela pode realizar uma das seguintes ações:
	 * Incluir novas espécies de cultivo
	 * Incluir novo fornecedor
	 * Buscar por fornecedores a partir de um produto 
	 * ->Listar espécies (extra)*/

	bool menu = true;
	while (menu)
	{
		cout << "=============Controle de Cultivo da Chacara=============" << endl
			 << "->O que deseja fazer?" << endl
			 << endl
			 << "  [1] Incluir nova especie de cultivo" << endl
			 << "  [2] Incluir novo fornecedor" << endl
			 << "  [3] Buscar por fornecedores de um produto" << endl
			 << "  [4] Listar especies" << endl
			 << "  [5] Encerrar execucao" << endl
			 << "=====================================================" << endl;

		int choice;
		cout << "Escolha uma opcao: ";
		cin >> choice;

		string product;
		switch (choice)
		{
		case 1:
			cin.ignore();
			administrator->newSpecie();
			break;
		case 2:
			cin.ignore();
			administrator->newProvider();
			break;
		case 3:
			cout << "Digite o nome do produto para ver seus fornecedores: ";
			cin >> product;
			administrator->providerSearch(product);
			break;
		case 4:
			administrator->listSpecies();
			break;
		case 5:
			cout << "Execucao Encerrada! Volte sempre, Morgana!" << endl;
			menu = false;
			break;
		default:
			cout << "Por favor, insira uma opcao valida." << endl;
			break;
		}
	}
	delete administrator;
	return 0;
}