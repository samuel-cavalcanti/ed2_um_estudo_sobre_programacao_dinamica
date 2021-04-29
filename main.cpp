#include <iostream>
#include <vector>
#include "gtest/gtest.h"


int cut_rod(std::vector<int> &prices, int length);

int memoized_cut_rod(std::vector<int> &prices, int length);

int memoized_cut_rod_aux(std::vector<int> &prices, int length, std::vector<int> &memoized_prices);

/*
 * prices e best prices, foram tirados do livro algoritmos de thomas Cormen
 * capitulo 15- programação dinamica
 */
std::vector<int> prices_rod{1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

std::vector<int> best_prices{1, 5, 8, 10, 13, 17, 18, 22, 25, 30};


/*
 * Teste simples que verifica se copiei todos os valores
 * da tabela do livro
 */
TEST(dynamic_programming, cut_rod_lengths) {


    EXPECT_EQ(prices_rod.size(), 10);
    EXPECT_EQ(best_prices.size(), 10);
}

/*
 * verifica se a resposta dada pela minha implemetação da solução burra
 * é igual a do livro
 */
TEST(dynamic_programming, dump_cut_rod_tests) {
    std::vector<int> best_prices{1, 5, 8, 10, 13, 17, 18, 22, 25, 30};

    for (auto i = 0; i < best_prices.size(); i++) {
        auto length{i + 1};
        EXPECT_EQ(cut_rod(prices_rod, length), best_prices[i]);

    }

}

/*
 * verifica se a resposta dada pela minha implemetação da solução dinamica
 * é igual a do livro
 */
TEST(dynamic_programming, dynamic_cut_rod_tests) {
    std::vector<int> best_prices{1, 5, 8, 10, 13, 17, 18, 22, 25, 30};

    for (auto i = 0; i < best_prices.size(); i++) {
        auto length{i + 1};
        EXPECT_EQ(memoized_cut_rod(prices_rod, length), best_prices[i]);


    }

}

/*
 * Implementação do Cut Rod sem programação dinâmica
 * tempo de executação exponencial em relação a entrada  length
 */
int cut_rod(std::vector<int> &prices, int length) {
    if (length < 1)
        return 0;

    int best_price{-1};


    for (auto i = 0; i < length; i++) {
        best_price = std::max(best_price, prices[i] + cut_rod(prices, length - (i + 1)));
    }
    return best_price;

}


int memoized_cut_rod(std::vector<int> &prices, int length) {
    std::vector<int> memoized_prices(length + 1, -1);

    return memoized_cut_rod_aux(prices, length, memoized_prices);
}

int memoized_cut_rod_aux(std::vector<int> &prices, int length, std::vector<int> &memoized_prices) {
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);


    return RUN_ALL_TESTS();
}
