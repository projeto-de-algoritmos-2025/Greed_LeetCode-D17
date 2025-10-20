/*
11. Container With Most Water: https://leetcode.com/problems/container-with-most-water/
Exercício resolvido por Diego Souza e Marcos Castilhos

Na nossa abordagem:
O objetivo deste problema é encontrar a maior área de um contêiner que pode ser formado
por duas linhas verticais a partir de um array de alturas. A área é o produto da
largura (distância entre as linhas) pela altura (limitada pela linha mais baixa).

Uma solução de força bruta, testando todos os pares de linhas, seria muito lenta (O(n²)).
Em vez disso, aplicamos a técnica dos "Ponteiros Duplos" (Two Pointers), uma estratégia
muito mais eficiente (O(n)) que resolve o problema em uma única passada.

A ideia central do algoritmo é:
1.  Inicializamos dois ponteiros: um ponteiro `left` no início do array (índice 0) e um
    ponteiro `right` no final. Esta configuração inicial nos dá a maior largura
    possível.
    
2.  Em um loop, que executa enquanto `left` for menor que `right`, nós realizamos
    os seguintes passos:
    a) Calculamos a área atual. A largura é `right - left` e a altura é o mínimo
       entre as alturas das duas linhas: `min(height[left], height[right])`.
    b) Comparamos a área atual com a área máxima encontrada até agora e a atualizamos
       se a atual for maior.

3.  Para otimizar o algoritmo, precisamos decidir qual ponteiro mover. A largura (`right - left`)
    sempre diminuirá no próximo passo. Portanto, a única maneira de potencialmente encontrar uma
    área maior é aumentando a altura do contêiner.

4.  A altura do contêiner é sempre limitada pela linha mais baixa. Se movermos o ponteiro
    da linha mais alta, a altura do próximo contêiner ainda será limitada pela mesma
    linha baixa, mas com uma largura menor, garantindo uma área menor. Assim, a única
    escolha promissora é mover o ponteiro associado à linha mais baixa, na esperança
    de encontrar uma linha mais alta que compense a redução da largura.

5.  O processo é repetido até que os ponteiros se cruzem. O valor final armazenado como
    área máxima será a solução.
*/
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