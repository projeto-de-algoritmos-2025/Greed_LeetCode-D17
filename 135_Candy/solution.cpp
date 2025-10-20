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
