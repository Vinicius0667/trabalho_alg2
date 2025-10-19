#include "random_questions.h"

/**
 * Dado uma probabilidade, retorna uma opção aleatória com base na probabilidade.
 * Caso a probabilidade seja 0, retorna uma opção aleatória entre 'a' e 'd' (alguma das opções).
 */
char get_weighted_option(char correct_question, int prob) {
    int probability;
    char wrong_options[3], i;

    if (prob == 0) {
        return 'a' + (rand() % 4);
    }

    for (i = 'a'; i <= 'd'; i++) {
        if (i != correct_question) {
            wrong_options[i - 'a'] = i;
        }
    }

    probability = rand() % 10;

    if (probability < prob) {
        return correct_question;
    }

    return wrong_options[rand() % 3];
}
