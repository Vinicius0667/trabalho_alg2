#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"

void print_question(Question question, const unsigned short question_number, const double score);

int main(void) {
    Question questions;
    FILE *file;

    file = fopen("perguntas.dat", "rb");

    if (file == NULL) {
        perror("Houve um erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    questions.answer = 'a';
    strcpy(questions.options[0], "Opção A");
    strcpy(questions.options[1], "Opção B");
    strcpy(questions.options[2], "Opção C");
    strcpy(questions.options[3], "Opção D");
    strcpy(questions.question, "Qual é a capital do Brasil?");
    questions.question_level = 1;

    print_question(questions, 1, 0);

    return EXIT_SUCCESS;
}

void print_question(Question question, const unsigned short question_number, const double score) {
    printf("== ------------\n");
    printf("== Pergunta %hu\n", question_number);
    printf("== Voce possui um total acumulado de R$ %.2lf ==\n", score);
    printf("\n");
    printf("%s\n", question.question);
    for (short i = 0; i < 4; i++) {
        printf("%s\n", question.options[i]);
    }
    printf("\n");
}
