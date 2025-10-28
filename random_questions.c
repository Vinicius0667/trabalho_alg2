#include "random_questions.h"

/**
 * Dado um número de opções, retorna uma opção aleatória com base na probabilidade.
 *
 * @param char correct_question A opção correta.
 * @param int probability A probabilidade de escolher a opção correta.
 * @param char *wrong_options Um array de opções incorretas.
 * @param int number_options O número de opções incorretas.
 * @return char A opção escolhida.
 */
char get_weighted_option(char correct_question, int probability, char *wrong_options, int number_options) {
    int random_number;

    random_number = rand() % 100;

    if (random_number < probability) {
        return correct_question;
    }

    return wrong_options[rand() % number_options];
}

/**
 * Retorna um número aleatório entre min e max.
 *
 * @param unsigned min O valor mínimo.
 * @param unsigned max O valor máximo.
 * @return int O número aleatório.
 */
int get_random_number(unsigned short min, unsigned short max, int *numbers_sorted, unsigned short question_number) {
    int random_number = 0 , i = 0, repeted;

    for (i = 0; i < (question_number + 3); i++){ // zera vetor
        numbers_sorted[i] = -1;
    }

    while (!repeted){
        repeted = 0;

        random_number = rand() % (max - min + 1) + min;
        for (i = 0; i < (question_number + 3); i++) {
            if (random_number == numbers_sorted[i]) {
                repeted = 1;
                break;
            }
        }
        
        if (!repeted) {
            for (i = 0; i < (question_number + 3); i++) {
                if (numbers_sorted[i] == -1){
                    numbers_sorted[i] = random_number;
                    break;
                }
            }
            return random_number;
        }
    }
}
