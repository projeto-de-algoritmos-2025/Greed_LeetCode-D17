/*
1130. Minimum Cost Tree From Leaf Values: https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/description/
Exercício resolvido por Diego Souza e Marcos Castilhos

Na nossa abordagem:
Este problema pode ser resolvido de forma eficiente com uma abordagem gulosa (Greedy)
utilizando uma Pilha Monotônica. A ideia central é que, para minimizar a soma total
dos produtos, devemos sempre combinar os números menores primeiro. Um número pequeno,
ao ser multiplicado, deve "desaparecer" da forma mais barata possível, ou seja,
sendo multiplicado pelo menor de seus vizinhos maiores.

O algoritmo funciona da seguinte forma:
1. Mantemos uma pilha que armazena os valores das folhas em ordem estritamente
   decrescente (uma pilha monotônica).
2. Para cada número `num` no array de entrada, nós o comparamos com o topo da pilha.
3. Se o topo da pilha é menor ou igual a `num`, significa que o topo é um
   "mínimo local" (menor que seu vizinho à esquerda na pilha e que `num` à direita).
   Este é o candidato perfeito para ser combinado.
4. Nós removemos (pop) esse mínimo local, calculamos o custo (mínimo_local * o menor
   de seus vizinhos) e o somamos à resposta. Repetimos isso até que a pilha volte
   a ser decrescente.
5. Após processar o `num` atual, nós o inserimos (push) na pilha.
6. Ao final, a pilha conterá os nós "sobreviventes" em ordem decrescente. Nós
   os combinamos do topo para a base (do menor para o maior) para calcular o custo restante.
Um valor sentinela (INT_MAX) é usado na base da pilha para simplificar a lógica e
evitar a verificação de pilha vazia.
*/

#include <vector>
#include <stack>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int minimo_local;
        int temp;
        int resposta = 0;
        stack<int> pilha;

        // PASSO 1: Inicializamos a pilha com um valor sentinela.
        // Isso garante que a pilha nunca estará vazia nos cálculos de `min`
        // e serve como uma "parede" para as comparações.
        pilha.push(INT_MAX);

        // PASSO 2: Iteramos por cada folha do array.
        for (int num : arr) {
            // PASSO 3: Encontramos e processamos os mínimos locais.
            // Enquanto o topo da pilha for menor que o número atual,
            // o topo é um mínimo local que deve ser combinado agora.
            while (pilha.top() <= num) {
                minimo_local = pilha.top();
                pilha.pop();

                // PASSO 4: O custo é o mínimo local multiplicado pelo menor de seus vizinhos.
                // Seus vizinhos são o `num` atual e o novo topo da pilha.
                resposta += minimo_local * min(pilha.top(), num);
            }
            // PASSO 5: Adicionamos o número atual à pilha, mantendo a propriedade decrescente.
            pilha.push(num);
        }

        // PASSO 6: Limpamos a pilha, combinando os nós restantes.
        // A pilha agora contém uma sequência decrescente (ex: INT_MAX, 15, 8, 3).
        // Combinamos os dois menores (topo) repetidamente.
        while (pilha.size() > 2) {
            temp = pilha.top();
            pilha.pop();
            resposta += temp * pilha.top();
        }

        return resposta;
    }
};
