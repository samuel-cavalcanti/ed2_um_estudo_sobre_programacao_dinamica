# Programação Dinâmica

[![Build Status](https://www.travis-ci.com/samuel-cavalcanti/ed2_um_estudo_sobre_programacao_dinamica.svg?branch=main)](https://www.travis-ci.com/samuel-cavalcanti/ed2_um_estudo_sobre_programacao_dinamica)
[![codecov](https://codecov.io/gh/samuel-cavalcanti/ed2_um_estudo_sobre_programacao_dinamica/branch/main/graph/badge.svg)](https://codecov.io/gh/samuel-cavalcanti/ed2_um_estudo_sobre_programacao_dinamica)

## Notas do Professor

O objetivo é escrever um relatório que explique o que o que é programação dinâmica (PD) e dê um exemplo de algoritmo com
PD (implementação em C ou CPP).

## o que é programação dinâmica (PD)

A programação dinâmica, assim como o método de divisão e conquista, resolve problemas combinando as soluções para
subproblemas. (Nesse contexto, “programação” se refere a um método tabular, não ao processo de escrever código de
computador.) Um algoritmo de programação dinâmica resolve cada subsubproblema só uma vez e depois grava sua resposta
em uma tabela, evitando assim, o trabalho de recalcular a resposta toda vez que resolver cada subsubproblema.

## Cortes de Hastes (exemplo de algoritmo com PD)

O problema do corte de hastes é o seguinte. Dada uma haste de n polegadas de comprimento e uma tabela de preços _p_i_
para i = 1, 2, ..., n, determine a receita máxima _r_n_ que se pode obter cortando a haste e vendendo os pedaços.
Observe que, se o preço _p_n_ para uma haste de comprimento n for suficientemente grande, uma solução ótima pode exigir
que ela não seja cortada. Considere o caso quando n = 4. A Tabela abaixo mostra todas as maneiras de cortar uma haste de
4 polegadas de comprimento, incluindo não cortá-la. Vemos que cortar uma haste de 4 polegadas em duas peças de 2
polegadas produz a receita p2 + p2 = 5 + 5 = 10, que é ótima.

| Comprimento _i_   | 1 | 2 | 3 | 4  | 5  | 6  | 7  | 8  | 9  | 10 |
|-------------------|---|---|---|----|----|----|----|----|----|----|
| Preço _p_i_       | 1 | 5 | 8 | 9  | 10 | 17 | 17 | 20 | 24 | 30 |
| melhor preço _r_i_| 1 | 5 | 8 | 10 | 13 | 17 | 18 | 22 | 25 | 30 | 

### Implementação recursiva de cima para baixo

```c++
int cut_rod(std::vector<int> &prices, int length) {
    if (length < 1)
        return 0;

    int best_price{-1};


    for (auto i = 0; i < length; i++) {
        best_price = std::max(best_price, prices[i] + cut_rod(prices, length - (i + 1)));
    }
    return best_price;

}
```
O procedimento CUT- ROD toma como entrada um arranjo p[0 ..length-1] de preços
e um inteiro length, e retorna a máxima receita possível para uma haste de
comprimento length. Se length for menoUtilização de programação dinâmica para o corte ótimo de hastesr que 1, nenhuma receita é possível e,
portanto, CUT- ROD retorna 0 . A linha 4 inicializa a receita máxima q para -1,
de modo que o laço for na linhas 7 calcula corretamente best_price = max 0 ≤ i < n,
(p[i] + CUT- ROD(p, n, i)); então, na ultima linha  retorna esse valor.

## Utilização de programação dinâmica para o corte ótimo de hastes

O método da programação dinâmica funciona da seguinte maneira: agora que já
observamos que uma solução recursiva ingênua é ineficiente porque resolve os
mesmos problemas repetidas vezes, nós a adaptamos para resolver cada problema
somente uma vez e armazenar sua solução. Se precisarmos nos referir novamente
a esse problema mais tarde, bastará que o examinemos, em vez de o recalcular.
Assim, a programação dinâmica usa memória adicional para poupar tempo de computação;
serve como exemplo de uma __permuta tempo-memória__.

```c++

int memoized_cut_rod(std::vector<int> &prices, int length) {
    // alocando a memória extra para poupar tempo de computação
    std::vector<int> memoized_prices(length + 1, -1);

    return memoized_cut_rod_aux(prices, length, memoized_prices);
}

int memoized_cut_rod_aux(std::vector<int> &prices, int length, std::vector<int> &memoized_prices) {
    // antes de executar o algoritimo, examina-se o vetor de preços
    // e caso o resultado já tenha sido calculado, retorna o valor.
    if (memoized_prices[length] >= 0)
        return memoized_prices[length];

    auto best_price{-1};

    if (length == 0)
        best_price = 0;
    else {
        for (auto i = 1; i <= length; i++) {
            auto best_price_i = prices[i - 1] + memoized_cut_rod_aux(prices, length - i, memoized_prices);
            best_price = std::max(best_price, best_price_i);
        }

    }

    memoized_prices[length] = best_price;
    return best_price;

}
```

Aqui, o procedimento principal __MEMOIZED-CUT-ROD__ inicializa um novo arranjo auxiliar
memoized_prices[0 .. n] com o valor -1, Então, ele chama sua rotina auxiliar, __MEMOIZED-CUT-ROD- AUX__.

O procedimento __MEMOIZED-CUT-ROD-AUX__ é apenas a versão memoizada com algumas motificações  no nosso procedimento
anterior, __CUT-ROD__. Primeiro ele consulta o memoized_prices  para verificar se o valor desejado já é conhecido;
se for, retorna esse valor. Caso contrário, as linhas 6-16 calculam o valor desejado best_price na maneira usual,
salva em memoized_prices, e retorna o valor.