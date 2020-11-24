#include <iostream>
#include <string>
using namespace std;
 // ola
/*enum type
{
	fib,
	fet,
	ric
}; */

class FFR
{
private:
	//type typeChosen;
	int num1, num2;
	long calculateFib(int n);
	//long calculateFet(int n);
	//long calculateRic(int n);
	long *calculateFibSequence(int n);
	//long* calculateFetSequence(int n);
	//long* calculateRicSequence(int n);
public:
	FFR(); //construtor para Fibonacci
	//FFR(type c, int n1, int n2) //construtor para FET e RIC
	long termCalculator(int n); //calcula o termo n
	long *sequenceCalculator(int n);
}; //retorna um vetor com os n primeiro termos

long FFR::calculateFib(int n)
{
    if (n <= 1) 
        return n; 
        
    return (calculateFib(n-1) + calculateFib(n-2)); 
} 


long *FFR::calculateFibSequence(int n)
{
	long *vec = new long[n];

	for (int i = 0; i < n; i++)
	{
		vec[i] = calculateFib(i);
	}

	return vec;
}

FFR::FFR()
{
	num1 = 0;
	num2 = 0;
}

/*FFR::FFR(type c, int n1, int n2){
    if(c == 1){
        calculateFetSequence(c);
    }   
    else{
        calculateRicSequence(c);
    }
}*/

long FFR::termCalculator(int n)
{
	return calculateFib(n);
}

long *FFR::sequenceCalculator(int n)
{
	return calculateFibSequence(n);
}

int main()
{
	FFR calculator;

	bool menu = true;
	int n;
	while (menu)
	{
		cout << "=============Controle de Cultivo da Chacara=============" << endl
			 << "->O que deseja fazer?" << endl
			 << endl
			 << "  [1] Calcular o termo \"n\" da sequencia de Fibonnacci" << endl
			 << "  [2] Calcular os n termos da sequencia de Fibonnacci" << endl
			 << "=====================================================" << endl;

		int choice;
		cout << "Escolha uma opcao: ";
		cin >> choice;

		string product;
		switch (choice)
		{
		case 1:
			cout << "Digite a posição do termo para ver seu Fib respectivo: ";
			cin >> n;
			cout << endl
				 << endl;
			cout << calculator.termCalculator(n) << endl;
			break;
		case 2:
			cout << "Digite o número de termos a serem calculados: ";
			cin >> n;
			for (int i = 0; i < n; i++)
			{
				cout << calculator.sequenceCalculator(n)[i] << " ";
			}
			cout << endl;
			break;

		default:
			//cout << "Por favor, insira uma opcao valida." << endl;
			menu = false;
			break;
		}
	}
	return 0;
}
