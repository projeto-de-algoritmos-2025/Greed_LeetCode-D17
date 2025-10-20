// Solução Ótima com Dois Ponteiros - O(n)
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxArea = 0;
        int esquerda = 0;
        int direita = height.size() - 1;

        while (esquerda < direita) {
            // A altura é sempre limitada pela menor das duas linhas
            int h = min(height[esquerda], height[direita]);
            // A largura é a distância entre os ponteiros
            int w = direita - esquerda;
            
            // Calcula a área atual e a compara com a área máxima encontrada
            maxArea = max(maxArea, h * w);

            // decisão gananciosa: move o ponteiro da linha mais baixa
            if (height[esquerda] < height[direita]) {
                esquerda++;
            } else {
                direita--;
            }
        }
        return maxArea;
    }
};