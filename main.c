#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "questions.h"
#include "random_questions.h"
#include "embaralhar.h"

void print_question(Question question, const unsigned short question_number, const double score);

int main(void) {
    Question *questions = NULL;
    FILE *file;
    srand(time(NULL));
    double premio_total = 0.0;
    int recurso_plateia = 3, recurso_pular = 3, recurso_carta = 3, recurso_universitarios = 3;
    int nivel_atual = 1, numeracao_pergunta = 1;
    int eliminado = 0, venceu = 0;

    file = fopen("perguntas.dat", "rb");

    if (file == NULL) {
        perror("Houve um erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    alloc_questions(&questions, 70);
    read_questions(&questions, file, 70);
    fclose(file);

    while(!eliminado && !venceu && nivel_atual <= 4){
        //
        //
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
