#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "questions.h"
#include "random_questions.h"

#define MAX_LEVEL 4
#define MAX_QUESTIONS 20
#define HITS 5

void print_question(Question question, const unsigned short question_number, const double score);
void print_helps(const unsigned short *helps);
void get_wrong_answer(char correct_answer, char *wrong_answers);
void get_help(
    Question *questions,
    int question_index,
    char *wrong_answers,
    unsigned short probability,
    unsigned short *random_options,
    int option_number,
    char *user_answer
);
void response_flux_control (
    Question *questions,
    char *user_answer,
    unsigned short *helps,
    int *question_drawn,
    unsigned short *random_options,
    unsigned short *lose
);

int main(void) {
    Question *questions;
    FILE *file;
    unsigned short level = 1, counter = 0, i, lose = 0, hits = 0;
    unsigned short helps[4] = {3, 3, 3, 3}, used_questions[4][20] = {0}, random_options[4] = {0};
    double total_prize = 0;
    int question_drawn;
    char user_answer;
    srand(time(NULL));

    file = fopen("perguntas.dat", "rb");

    if (file == NULL) {
        perror("Houve um erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    while (level <= MAX_LEVEL && !lose) {
        if (level < MAX_LEVEL) {
            alloc_questions(&questions, MAX_QUESTIONS);
            read_questions(&questions, file, MAX_QUESTIONS);

            while (hits < HITS && !lose) {
                lose = 1;
                question_drawn = get_random_number(0, MAX_QUESTIONS - 1);

                for (i = 0; i < counter; i++) {
                    if (used_questions[level - 1][i] == question_drawn) {
                        question_drawn = -1;
                        break;
                    }
                }

                if (question_drawn != -1) {
                    used_questions[level - 1][counter] = question_drawn;
                    print_question(*(questions + question_drawn), counter + 1, total_prize);
                    print_helps(helps);
                    scanf("%c%*c", &user_answer);

                    response_flux_control(questions, &user_answer, helps, &question_drawn, random_options, &lose);

                    if ((user_answer - '0') == 5) {
                        lose = 0;
                        printf("\nParabéns, seu premio foi de R$ %.2lf\n\n", total_prize);
                        return EXIT_SUCCESS;
                    }

                    if (user_answer == (questions + question_drawn)->answer) {
                        printf("Certa resposta!\n");
                        lose = 0;
                        hits++;
                        total_prize += pow(10, level + 2);
                    }

                    for (i = 0; i < 4; i++) {
                        random_options[i] = 0;
                    }
                    counter++;
                }
            }
        } else {
            alloc_questions(&questions, (size_t) MAX_QUESTIONS / 2);
            read_questions(&questions, file, (size_t) MAX_QUESTIONS / 2);

            while (!lose) {
                lose = 1;
                question_drawn = get_random_number(0, (int) (MAX_QUESTIONS / 2) - 1);
                for (i = 0; i < counter; i++) {
                    if (used_questions[level - 1][i] == question_drawn) {
                        question_drawn = -1;
                        break;
                    }
                }

                if (question_drawn != -1) {
                    used_questions[level - 1][counter] = question_drawn;
                    print_question(*(questions + question_drawn), counter + 1, total_prize);
                    print_helps(helps);
                    scanf("%c%*c", &user_answer);

                    response_flux_control(questions, &user_answer, helps, &question_drawn, random_options, &lose);

                    if ((user_answer - '0') == 5) {
                        printf("\nParabens, seu premio foi de R$ %.2lf\n\n", total_prize);
                        return EXIT_SUCCESS;
                    }

                    if (user_answer == (questions + question_drawn)->answer) {
                        total_prize = pow(10, 6);
                        printf("\nParabens, seu premio foi de R$ %.2lf\n\n", total_prize);
                        return EXIT_SUCCESS;
                    }

                    total_prize = 0;

                    for (i = 0; i < 4; i++) {
                        random_options[i] = 0;
                    }
                    counter++;
                }
            }
        }
        free_questions(&questions);
        hits = 0;
        counter = 0;
        level++;
        if (level < MAX_LEVEL && !lose)
            total_prize = pow(10, level + 2);
    }

    fclose(file);
    printf("Infelizmente, voce perdeu, obrigado por jogar!!!\n");
    printf("Seu premio foi de R$ %.2lf\n", total_prize);
    return EXIT_SUCCESS;
}

void response_flux_control (
    Question *questions,
    char *user_answer,
    unsigned short *helps,
    int *question_drawn,
    unsigned short *random_options,
    unsigned short *lose
) {
    char wrong_answers[3];
    unsigned short random_card, random_number;
    if ((*user_answer - '0' ) < 5 && (*user_answer - '0') >= 1) {
        helps[*user_answer - 1]--;

        if ((*user_answer - '0') == 1 && helps[0] > 0) {
            lose = 0;
            printf("Questao pulada\n");
            helps[0]--;
        } else if ((*user_answer - '0') == 2 && helps[1] > 0) {
            get_help(questions, *question_drawn, wrong_answers, 40, random_options, 30, user_answer);
            helps[1]--;
        } else if ((*user_answer - '0') == 3 && helps[2] > 0) {
            get_help(questions, *question_drawn, wrong_answers, 70, random_options, 3, user_answer);
            helps[2]--;
        } else if ((*user_answer - '0') == 4 && helps[3] > 0) {
            get_wrong_answer((questions + *question_drawn)->answer, wrong_answers);
            random_card = get_random_number(0, 3);

            random_options[(questions + *question_drawn)->answer - 'a'] = 1;

           printf("A carta selecionada elimina %hu questoes\n", random_card);

            while (random_card > 0) {
                random_number = get_random_number(0, 3);
                if (!random_options[random_number]) {
                    random_options[random_number] = 1;
                    printf("A opcao %c esta errada\n", random_number + 'a');
                    random_card--;
                }
            }
            printf("Digite sua resposta:\n");
            scanf("%c%*c", user_answer);
            helps[3]--;
        }
    }
}

void print_question(Question question, const unsigned short question_number, const double total_prize) {
    printf("== ------------\n");
    printf("== Pergunta %hu\n", question_number);
    printf("== Voce possui um total acumulado de R$ %.2lf ==\n", total_prize);
    printf("\n");
    printf("%s\n", question.question);
    for (short i = 0; i < 4; i++) {
        printf("%c) %s\n", 'a' + i, question.options[i]);
    }
    printf("\n");
}

void print_helps(const unsigned short *helps) {
    printf("-- Ajuda --\n");
    printf("[1] Pular pergunta (%hux)\n", helps[0]);
    printf("[2] Pedir ajuda a plateia (%hux)\n", helps[1]);
    printf("[3] Pedir ajuda aos universitarios (%hux)\n", helps[2]);
    printf("[4] Pedir ajuda as cartas (%hux)\n", helps[3]);
    printf("[5] Parar\n");
}

void get_wrong_answer(char correct_answer, char *wrong_answers) {
    int idx = 0;

    for (char i = 'a'; i <= 'd'; i++) {
        if (i != correct_answer) {
            if (idx < 4) {
                wrong_answers[idx] = i;
                idx++;
            }
        }
    }
}

void get_help(Question *questions,
        int question_index,
        char *wrong_answers,
        unsigned short probability,
        unsigned short *random_options,
        int option_number,
        char *user_answer
    ) {
    char random_option;
    short j;

    get_wrong_answer((questions + question_index)->answer, wrong_answers);
    for (j = 0; j < option_number; j++) {
        random_option = get_weighted_option((questions + question_index)->answer, probability, wrong_answers, 3);
        random_options[random_option - 'a']++;
    }

    for (j = 0; j < 4; j++) {
        printf("\nVotos para a opção %c: %hu\n", 'a' + j, random_options[j]);
    }
    printf("\nDigite sua resposta:\n");
    scanf("%c%*c", user_answer);
}
