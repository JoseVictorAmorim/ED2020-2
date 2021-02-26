# -*- coding: utf-8 -*-
"""
Algoritmo RSA - Matemática Discreta - GEX252 - 2020/01
-------------------------------------------------------------------------------------------------------------------------------------
Professora:
    Andreza Cristina Beezao Moreira.
-------------------------------------------------------------------------------------------------------------------------------------
Monitor:
    Caio de Oliveira Lopes.
-------------------------------------------------------------------------------------------------------------------------------------
"""
# -----------------------------------------------------------------------------------------------------------------------------------#
'''------------------------------------------------------------Bibliotecas--------------------------------------------------------'''
import random

# -----------------------------------------------------------------------------------------------------------------------------------#
'''----------------------------------------------Comentários gerais sobre a implementação-----------------------------------------'''
'''
Geração da Chave Pública:
    * Gera o número P aleatório, P tem que ser primo.
    * Gera o número Q também aleatório e também primo.
    * P e Q devem ser diferentes. (Existe uma explicação importante sobre a geração dos primos na função Gerar_Primo(), LEIAM!)
    * Calcula N, sendo a multiplicação de P por Q.
    * N = P * Q
    * Calcula o totiente de N, phi(N), sendo (Q-1) * (P-1), pois eles são primos.
    * Phi(N) = (Q-1) * (P-1)
    * Gera o número E (lambda, dos slides de aula), aleatório também, tendo que satisfazer a igualdade 1 < E < phi(N).
    * Depois de gerado E, o mdc entre E e phi(N) tem que ser igual a 1 (ou seja, devem ser primos entre si, para que E tenha inverso em (P-1)*(Q-1)).
    * mdc(phi(N), E) == 1; se não satisfazer isso, terá que ser gerado outro número aleatório E.
    * A chave pública é composta por N e E.

Geração da Chave Privada:
    * Para encontrar o D, precisa satisfazer a igualdade mod (D*E, phi(N)) == 1.
    * Se for igual a 1, achou o D; se não, o D é incrementado até satisfazer a condição.
    * Em síntese, D deve ser o inverso de E no mod phi(N).
    * A chave privada é composta por N e D.

Criptografar texto:
    * A chave privada é guardada pelo servidor, e a pública é enviada para o cliente.
    * O cliente possui, portanto, o E e o N.
    * Para o cliente criptografar o conteúdo que será enviado para o servidor ele tem que seguir o seguinte algoritmo:
        * Para cada caracter na string que será enviada:
            * O valor da letra em ascii é elevado a E. Por exemplo: 111^E
            * O resultado é utilizado na função modular.
            * mod(111^E, N) -> o resultado vai ser o valor criptografado e que será enviado para o servidor.

Descriptografar:
    * Para o servidor descriptografar o texto cifrado, ele deve seguir o seguinte algoritmo:
        * Para o valor cifrado de cada caracter -> valor^D -> sendo D a chave privada
        * O resultado ele utiliza na função modular, mod(resultado, N) -> retornando ao valor 111,
        que deverá ser convertido para ascii.
        * O processo se repete para todos os caracteres criptografados do texto cifrado.
'''
# -----------------------------------------------------------------------------------------------------------------------------------#
# Função Totiente.
'''
    * Classe que calcula a Função Totiente (ou Função Phi).
    * A função está simplificada pois apenas serão utilizados números primos, com isso, podemos utilizar 
    uma propriedade especial.
'''


def Totiente(num):
    if Primo(num):
        return num - 1
    else:
        return False


# Função Primo.
'''
    * Testa se um numero gerado é primo ou não.
'''


def Primo(n):
    # Testa todos os números no intervalo de 2 até N - 1 (está escrito N pois o fechamento do intervalo é exclusivo).
    for numero in range(2, n):
        # Se N for divisível por algum dos números ele não será primo.
        if n % numero == 0:
            return False
    # Se o loop for encerrado sem interrupção do retorno, significa que o número é primo.
    return True


# Função MDC.
'''
    * Calcula o MDC entre 2 números.
'''


def MDC(n1, n2):
    resto = 1
    while n2 != 0:
        resto = n1 % n2
        n1 = n2
        n2 = resto
    return n1


# Função Gerar_E.
'''
    * Gera um numero aleatório E, satisfazendo as condições.
'''


def Gerar_E(phi_de_N):
    while True:
        e = random.randint(2, phi_de_N)
        if MDC(phi_de_N, e) == 1:
            return e


# Função Gerar_Primo.
'''
    * Gera um numero primo aleatório.
'''


def Gerar_Primo():
    while True:
        # Define o intervalo dos primos gerados
        '''
        -----------------------------------------------------------------------------------------------------------------------------
        Em teoria, os primos podem ser bem pequenos, porém podem ocorrer problemas no algoritmo se P e/ou Q forem pequenos,
        pois o valor de N é gerado a partir deles.
        Esse é um problema que não ocorre no verdadeiro RSA, pois os primos utilizados são muito grandes.
        Em síntese, o valor de N não pode ser menor que o valor de algum dos "pedaços"(os blocos) da mensagem original.
        Por isso, os primos gerados serão valores um pouco maiores, apenas para que possa criptografar corretamente as mensagens que
        os alunos quiserem digitar.
        -----------------------------------------------------------------------------------------------------------------------------
        Link com a explicação desse tipo de problema:
            https://crypto.stackexchange.com/questions/15021/rsa-problem-if-i-choose-two-specific-small-prime-numbers
        -----------------------------------------------------------------------------------------------------------------------------
        Ps.: Se quiserem alterar o valor do "range" dos primos, não utilizem como limite inferior valores menores que 14, pois para
        que não haja problemas, o menor primo gerado deve ser 17.
        '''
        # Existem valores até o 255 na tabela ASCII, então por segurança os primos serão de valores acima desse.
        x = random.randint(100, 500)
        if Primo(x) == True:
            return x


# Função Criptografa.
'''
    * Cifra um texto.
'''

def Recebe(tamanho):
    lista = []
    i = 0
    while i < tamanho:
        numero = int(input('digete o numero a ser coisado :b'))
        print("numero:", numero)
        a = numero
        lista.append(a)
        i += 1
    return lista
def Criptografa(texto, e, n):
    print("valor e:", e )
    print("valor n:", n )
    tamanho = len(texto)
    i = 0
    lista = []
    while i < tamanho:
        letra = texto[i]
        print("letra:", letra)
        # A função ord() devolve o código numérico do caractere passado como parâmetro.
        k = ord(letra)
        print("valor da letra:", k)
        k = k ** e
        a = k % n
        print(a)
        lista.append(a)
        i += 1
    return lista


# Função Descriptografa.
'''
    * Descriptografa um texto criptografado.
'''

def Descriptografa2(cifra, private_key):
    n = private_key[0]
    d = private_key[1]

    lista = []
    i = 0
    tamanho = len(cifra)
    while i < tamanho:
        resultado = cifra[i] ** d
        texto = resultado % n
        lista.append(texto)
        i += 1
    return lista
def Descriptografa(cifra, private_key):
    # Recupera os valores de N e D do par ordenado apenas para tornar a leitura do código mais clara
    n = private_key[0]
    d = private_key[1]

    lista = []
    i = 0
    tamanho = len(cifra)
    while i < tamanho:
        resultado = cifra[i] ** d
        texto = resultado % n
        # A função chr() devolve o caracter corresponde ao código numérico passado como parâmetro.
        letra = chr(texto)
        lista.append(letra)
        i += 1
    return lista


# Função Calcula_Private_Key.
'''
    * Calcula a chave privada.
'''


def Calcula_Private_Key(phi, e):
    d = 0
    while ((d * e) % phi) != 1:
        d += 1
    return d


# Função que exibe o menu de opções.
def Meu_Menuzinho():
    print('------------------------------------------------------------------------------------------------------')
    print('Este é um algoritmo que simula a criftografia RSA. \n')
    print('Você pode executar com um dos três casos de teste prontos ou inserir sua própria mensagem.\n')
    print('O programa possui as seguintes opções: \n')
    print('1 - "Hello World!" \n')
    print('2 - "Esta mensagem está criptografada." \n')
    print('3 - "Bom semestre para todos!" \n')
    print('4 - Mensagem personalizada. \n')
    print('5 - Finalizar o programa. \n')
    print('------------------------------------------------------------------------------------------------------')
    try:
        menu = int(input('Digite o número do menu correspondente à operação desejada: '))
    except ValueError:
        menu = 6
    print('\n')
    print('------------------------------------------------------------------------------------------------------')
    return menu


# Função para o caso de teste.
def Teste(texto=None):
    if texto == None:
        p = int(input('digite o "P" (PARA ISSO FATORE O "N"): '))
        q = int(input('digite o "Q" (PARA ISSO FATORE O "N"): '))
        n = int(input('digite o "N": '))
        e = int(input('digite o "E": '))
        x = Totiente(q)
        y = Totiente(p)
        phi_de_N = x * y
        opcao = input('descriptografar? s/n?')
        if (opcao == "s"):
            quant = int(input('quantidade de "codigos" que serao digitados: '))
            texto_cifrado = Recebe(quant)
            public_key = (n, e)
            print('Sua chave publica é:', public_key)
            print('Sua mensagem criptografada é:', texto_cifrado)
            d = Calcula_Private_Key(phi_de_N, e)
            private_key = (n, d)
            print('Sua chave privada é:', private_key)
            texto_original = Descriptografa2(texto_cifrado, private_key)
            print('Os numeros que correspondem a sua mensagem original são:', texto_original)
        elif (opcao == "n"):
            texto = input('Insira a mensagem que deseja criptografar: ')
            public_key = (n, e)

            print('Sua chave publica é:', public_key)
            texto_cifrado = Criptografa(texto, e, n)
            print('Sua mensagem criptografada é:', texto_cifrado)
            d = Calcula_Private_Key(phi_de_N, e)
            private_key = (n, d)
            print('Sua chave privada é:', private_key)
            texto_original = Descriptografa(texto_cifrado, private_key)
            print('Sua mensagem original é:', texto_original)






# -----------------------------------------------------------------------------------------------------------------------------------#
'''-----------------------------------------------------------Implementação-------------------------------------------------------'''


# Função principal.
def main():
    # Booleana que controla a execução do código.
    PararPrograma = False

    while not PararPrograma:
        menu = Meu_Menuzinho()

        if menu == 1:
            Teste('Hello World!')
        elif menu == 2:
            Teste('Esta mensagem está criptografada.')
        elif menu == 3:
            Teste('Bom semestre para todos!')
        elif menu == 4:
            Teste()
        elif menu == 5:
            # Altera a booleana para encerrar o laço
            PararPrograma = True
            print('Programa encerrado.')
        else:
            print('Entrada inválida no menu de seleção. \n')
            print('Digite um valor válido. \n')


'''------------------------------------------------------Chamada da Função Principal----------------------------------------------'''
if __name__ == "__main__":
    main()