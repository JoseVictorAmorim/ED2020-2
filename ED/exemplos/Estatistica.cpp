#include <iostream>
#include <cmath>
using namespace std;

int moda(float *vec, int tamanho){
    int cont[tamanho];
    int moda = 0, conta = 0;
    for(int i = 0; i < tamanho; i++){
         for(int j=i+1;j<tamanho;j++){  
            if(vec[i]==vec[j]){
                cont[i]++;
                if(cont[i]>conta){
                    conta=cont[i];
                    moda=i;
                    }
                } 
            }
        cont[i]=0;
    }
    return vec[moda];
};

float media(float *vet, int tamanho){
    float soma = 0;
    for(int i = 0; i < tamanho; i++){
        soma += vet[i];
    }
    return(soma/tamanho);
}

float mediana(float *vet, int tamanho){
    if((tamanho % 2) != 0){
        return(vet[((tamanho)/2)]);
    }else{
        int a, b;
        a = ((tamanho)/2);
        b = ((tamanho)/2)-1;
        return(((vet[a]) + (vet[b])) / 2);
    }
}

void quartis(float *vet, int tamanho){
    float q1, q2, q3;
    q1 = mediana(vet, tamanho/2);
    q2 = mediana(vet, tamanho);
    float* vecAux = new float[tamanho/2];
    int j = 0;
    for(int i = tamanho+1/2; i < tamanho; i++){
        vecAux[j] = vet[i];
        j++;
    }
    q3 = mediana(vecAux, tamanho/2);

    cout << "1º QUARTIL: " << q1 << endl;
    cout << "2º QUARTIL: " << q2 << endl;
    cout << "3º QUARTIL: " << q3 << endl;
    delete[] vecAux;
}

float variancia(float *vet, int tamanho){
    float somaQuad = 0, somaV = 0;
    for(int i = 0; i < tamanho; i++){
        somaQuad += pow(vet[i], 2);
    }
    for(int i = 0; i < tamanho; i++){
        somaV += vet[i];
    }
    somaV = pow(somaV, 2);
    float x = somaQuad - somaV/tamanho;
    float y = 1/float((tamanho-1));
    return y*x;
}

void medidasDispersao(float *vet, int tamanho){
    float ampl = vet[tamanho-1] - vet[0];
    cout << "AMPLITUDE: " << ampl << endl;

    float var = variancia(vet, tamanho);
    cout << "VARIANCIA: " << var << endl;

    float dp = sqrt(var);
    cout << "DESVIO PADRAO: " << dp << endl;
    
}
void selection_sort(float *vet, int tamanho){
	int menor, auxiliar;
	for(int i = 0; i < tamanho-1; i++){
		menor = i;
		for(int j = i+1; j < tamanho; j++){
			if(vet[j] < vet[menor]){
				menor = j;
			}
		}
		auxiliar = vet[i];
		vet[i] = vet[menor];
		vet[menor] = auxiliar;
	}
}


int main(){
    int tam;
    cin >> tam;

    float *vec = new float[tam];
    for(int i = 0; i < tam; i++){
        cin >> vec[i];
    }

    selection_sort(vec, tam);
    cout << "VETOR ORDENADO: ";
    for (int i = 0; i < tam; i++){
        cout << vec[i] << " ";
    }
    cout << endl;

    cout << "MODA: " << moda(vec, tam) << endl;
    cout << "MEDIA: " << media(vec, tam) << endl;
    cout << "MEDIANA: " << mediana(vec, tam) << endl;
    quartis(vec, tam);
    medidasDispersao(vec, tam);

    delete[] vec;
    return 0;
}