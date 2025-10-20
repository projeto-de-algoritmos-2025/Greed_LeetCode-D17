/*
1235. Maximum Profit in Job Scheduling: https://leetcode.com/problems/maximum-profit-in-job-scheduling/description/
Exercício resolvido por Diego Souza e Marcos Castilhos

Na nossa abordagem:
Este problema é um exemplo clássico que combina Programação Dinâmica com uma
estratégia Gulosa (Greedy). O objetivo é encontrar o subconjunto de trabalhos
não conflitantes que maximize o lucro total.

A ideia central do algoritmo é:
1. A primeira e mais crucial etapa é a decisão gulosa de processar os trabalhos
   em uma ordem específica. Nós ordenamos os trabalhos crescentemente pelo seu
   tempo de término. Isso nos permite construir a solução de forma incremental,
   pois ao considerar um trabalho `i`, já teremos calculado as soluções ótimas
   para todos os trabalhos que terminam antes dele.
2. Utilizamos um vetor de programação dinâmica, `dp`, onde `dp[i]` armazenará o
   lucro máximo que pode ser obtido considerando os trabalhos de 0 até `i` (no
   array ordenado).
3. Para cada trabalho `i`, temos duas escolhas:
    a) Não agendar o trabalho `i`: Nesse caso, o lucro máximo que podemos obter
       é o mesmo que tínhamos até o trabalho anterior, ou seja, `dp[i-1]`.
    b) Agendar o trabalho `i`: O lucro será `profit[i]` mais o lucro máximo
       obtido com trabalhos que não conflitam com ele. Um trabalho não conflita
       se ele termina antes do trabalho `i` começar.
4. Para encontrar o lucro máximo de trabalhos não conflitantes de forma eficiente,
   precisamos encontrar o último trabalho `p` que termina antes ou no exato momento
   em que o trabalho `i` começa. Como os trabalhos estão ordenados por tempo de
   término, podemos usar busca binária (binary search) para encontrar esse
   trabalho `p` em tempo logarítmico (O(log n)).
5. A solução para `dp[i]` será então o máximo entre as duas escolhas: agendar ou
   não agendar o trabalho `i`.
6. O resultado final será o valor em `dp[n-1]`, que representa a decisão ótima
   considerando todos os trabalhos.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {

// Estrutura auxiliar para agrupar as informações de cada trabalho (job).
// Isso torna o código mais limpo e fácil de ler, em vez de manipular três vetores separados.
struct Job {
    int inicio, fim, lucro;
};

public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int tamanho = startTime.size();
        vector<Job> jobs(tamanho);

        // PASSO 1: PREPARAÇÃO - Transforma os vetores de entrada em um único vetor de objetos Job.
        for (int i = 0; i < tamanho; i++) {
            jobs[i] = {startTime[i], endTime[i], profit[i]};
        }

        // PASSO 2: ESTRATÉGIA GULOSA - Ordena os trabalhos pelo seu tempo de término.
        // Esta é a chave para a abordagem de programação dinâmica. Ao processar os jobs
        // em ordem de término, garantimos que, ao considerar um job 'i', todos os jobs
        // que terminam antes dele já foram processados.
        sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
            return a.fim < b.fim;
        });

        // PASSO 3: PROGRAMAÇÃO DINÂMICA - Inicializa o vetor 'dp'.
        // dp[i] armazenará o lucro máximo que podemos obter considerando os jobs de 0 até i.
        vector<int> dp(tamanho);
        dp[0] = jobs[0].lucro; // O caso base: o lucro máximo com apenas o primeiro job é o seu próprio lucro.

        // Itera sobre cada job a partir do segundo para construir a solução.
        for (int i = 1; i < tamanho; i++) {
            
            // PASSO 4: DECISÃO - Para cada job 'i', avaliamos as duas escolhas.
            
            // --- ESCOLHA 1: Incluir o job atual 'i'. ---
            int lucro_com_job_atual = jobs[i].lucro;

            // Encontra o último job que não conflita usando busca binária.
            // Procuramos o último job que termina ANTES ou no mesmo tempo em que o job atual COMEÇA.
            // `upper_bound` é eficiente (O(log n)) para encontrar essa posição.
            auto it = upper_bound(jobs.begin(), jobs.begin() + i, jobs[i].inicio, [](int valor_inicio, const Job& job_comparado) {
                return valor_inicio < job_comparado.fim;
            });
            
            int p = -1; // Índice do último job compatível.
            if (it != jobs.begin()) {
                // Se um job compatível foi encontrado, o iterador 'it' aponta para o próximo.
                // Portanto, voltamos uma posição para pegar o índice correto.
                it--;
                p = distance(jobs.begin(), it);
            }

            if (p != -1) {
                // Se encontramos um job compatível, somamos o lucro máximo acumulado até ele.
                lucro_com_job_atual += dp[p];
            }

            // --- ESCOLHA 2: NÃO incluir o job atual 'i'. ---
            // Se não incluirmos o job atual, o lucro máximo é o mesmo que tínhamos até o job anterior (i-1).
            int lucro_sem_job_atual = dp[i-1];

            // PASSO 5: ATUALIZAÇÃO DP - A solução ótima para dp[i] é o máximo entre as duas escolhas.
            dp[i] = max(lucro_com_job_atual, lucro_sem_job_atual);
        }

        // PASSO 6: RESULTADO FINAL - O último elemento do vetor 'dp' contém o lucro máximo
        // considerando todos os jobs, pois ele representa a decisão ótima final.
        return dp[tamanho-1];
    }
};