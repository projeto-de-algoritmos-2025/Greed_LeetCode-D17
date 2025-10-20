/*
135. Candy: https://leetcode.com/problems/candy/
Exercício resolvido por Diego Souza e Marcos Castilhos

Na nossa abordagem:
O problema pede para encontrarmos o número mínimo de doces a serem distribuídos
para crianças em uma fila, com base em suas classificações (ratings). A distribuição
deve seguir duas regras: toda criança ganha pelo menos um doce, e uma criança com
rating maior que seu vizinho adjacente deve receber mais doces que ele.

A principal dificuldade é que a quantidade de doces de uma criança depende tanto
do vizinho da esquerda quanto do da direita. Uma abordagem puramente local em uma
única passada geralmente falha em casos mais complexos (como uma longa sequência
decrescente após um pico). A solução ótima e elegante utiliza uma estratégia
ambiciosa (Greedy) em duas passadas, que resolve as dependências de forma sistemática.

A ideia central do algoritmo é:
1.  Inicialização: Começamos sendo justos, mas econômicos. Criamos um vetor `candies`
    e damos exatamente 1 doce para cada criança. Isso satisfaz a primeira regra
    ("pelo menos um doce") e estabelece uma linha de base para nossos cálculos.

2.  Primeira Passada (Esquerda para a Direita): Percorremos o array de crianças da
    esquerda para a direita (do índice 1 ao fim). Nesta passada, focamos apenas na
    relação com o vizinho da ESQUERDA. Se uma criança `i` tem um rating maior que
    sua vizinha `i-1`, ela deve receber mais doces. Portanto, definimos `candies[i]`
    como `candies[i-1] + 1`. Ao final desta varredura, a regra do vizinho esquerdo
    está satisfeita para todos.

3.  Segunda Passada (Direita para a Esquerda): Agora, percorremos o array em sentido
    inverso (do penúltimo ao primeiro elemento). Desta vez, focamos na relação com o
    vizinho da DIREITA. Se a criança `i` tem um rating maior que sua vizinha `i+1`,
    ela precisa ter mais doces. No entanto, não podemos simplesmente sobrescrever o
    valor da primeira passada. A criança `i` deve ter mais doces que AMBOS os vizinhos,
    se aplicável. Por isso, a atualização é `candies[i] = max(candies[i], candies[i+1] + 1)`.
    O uso da função `max` é a chave: ela garante que, ao satisfazermos a regra do
    vizinho direito, não violamos a contagem (potencialmente maior) já estabelecida
    na primeira passada.

4.  Soma Total: Após as duas passadas, o vetor `candies` contém a distribuição mínima
    que satisfaz ambas as regras simultaneamente. O resultado final, que é o número
    total de doces, é a soma de todos os elementos deste vetor.
*/
#include <iostream>
#include <vector>
#include <numeric> // Para accumulate
#include <algorithm> // Para max

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if (n == 0) {
            return 0;
        }

        // 1. Inicializa todos com 1 doce.
        vector<int> candies(n, 1);

        // 2. Passada da esquerda para a direita.
        // Garante que a criança com rating maior que o vizinho da ESQUERDA tenha mais doces.
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i-1]) {
                candies[i] = candies[i-1] + 1;
            }
        }

        // 3. Passada da direita para a esquerda.
        // Garante que a criança com rating maior que o vizinho da DIREITA tenha mais doces.
        // O uso do 'max' é crucial para não violar a condição da primeira passada.
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i+1]) {
                candies[i] = max(candies[i], candies[i+1] + 1);
            }
        }

        // 4. Soma o total de doces.
        // accumulate é uma forma eficiente de somar os elementos de um contêiner.
        return accumulate(candies.begin(), candies.end(), 0);
    }
};
