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
