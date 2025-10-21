#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "questions.h"
#include "random_questions.h"
#include "embaralhar.h"

void print_question(Question question, const unsigned short question_number);

int main(void) {
    Question *questions = NULL;
    FILE *file;
    srand(time(NULL));
    double premio_total = 0.0;
    int recurso_plateia = 3, recurso_pular = 3, recurso_carta = 3, recurso_universitarios = 3;
    int nivel_dificuldade = 1, numeracao_pergunta = 1;
    int loser = 0, winner = 0;

    file = fopen("perguntas.dat", "rb");

    if (file == NULL) {
        perror("Houve um erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    alloc_questions(&questions, 70);
    read_questions(&questions, file, 70);
    fclose(file);

    printf("--------------------------\n");
    printf("SEJA BEM VINDO AO SHOW DO MILHÀO!!!");
    printf("--------------------------\n");

    while(!loser && !winner && nivel_atual <= 4){

        unsigned short question_number = (nivel_dificuldade == 4) ? 1 : 5;

        print_question(*questions, question_number);
        //
    }

    return EXIT_SUCCESS;
}

void print_question(Question question, const unsigned short question_number) {
    short i;

    printf("\nPergunta %hu\n", question_number);
    printf("\n%s\n", question.question);

    for (short i = 0; i < 4; i++) {
        printf("%s\n", question.options[i]);
    }

    printf("\n--------------------------\n");

    printf("\n--- Ajuda ---\n");
    printf("[1] Pular pergunta (%dx)\n", recurso_pular);
    printf("[2] Pedir ajuda a plateia (%dx)\n", recurso_plateia);
    printf("[3] Pedir ajuda aos universitários (%dx)\n", recurso_universitarios);
    printf("[4] Pedir ajuda as cartas (%dx)\n", recurso_carta);
    printf("[5] Parar\n");
    printf("--------------------------\n");

    printf("Entre com a sua opção [a-d] para responder ou [1-5] para receber ajuda: ");
}

// printf("\n== Voce possui um total acumulado de R$ %.2lf ==\n", score);
