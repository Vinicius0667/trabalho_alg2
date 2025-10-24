#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "questions.h"
// #include "random_questions.h"
// #include "embaralhar.h"

void print_question(Question question, const unsigned short question_number, int recurso_plateia, int recurso_pular, int recurso_carta, int recurso_universitarios);

int main(void) {
    Question *questions = NULL;
    FILE *file;
    srand(time(NULL));
    double premio_total = 0.0;
    char answer;
    int recurso_plateia = 3, recurso_pular = 3, recurso_carta = 3, recurso_universitarios = 3;
    int nivel_dificuldade = 1, numeracao_pergunta = 1;
    int loser = 0, winner = 0;

    file = fopen("perguntas.dat", "rb");

    if (file == NULL) {
        perror("Houve um erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    printf("\n------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n                                          SEJA BEM VINDO AO SHOW DO MILHÃO!!!                                                 \n");
    printf("\n------------------------------------------------------------------------------------------------------------------------------\n");

    
    // unsigned short max_question = (nivel_dificuldade == 4) ? 1 : 5;
    unsigned short question_number = 1;
    
    while(!loser && !winner && nivel_dificuldade <= 4){
        unsigned short questions_by_level = (nivel_dificuldade == 4) ? 10 : 20;
        unsigned short start_pos = (nivel_dificuldade - 1) * 20;
        
        alloc_questions(&questions, questions_by_level);
        read_questions(&questions, file, start_pos, questions_by_level);

        question_number = (question_number > 5) ? 1 : question_number;

        print_question(*questions, question_number, recurso_plateia, recurso_pular, recurso_carta, recurso_universitarios);
        
        scanf(" %c", &answer);
        // printf("%c", answer);
        
        if (answer == questions->answer){
            printf("\nVocê acertou!!!\n");
            question_number += 1;
        } else {
            printf("\nVocê perdeu tudo!!! : ( \n");
            break;
        }
    }
    
    fclose(file);
    return EXIT_SUCCESS;
}

void print_question(Question question, const unsigned short question_number, int recurso_plateia, int recurso_pular, int recurso_carta, int recurso_universitarios) {

    
    printf("\nPergunta %hu\n", question_number); // Question_number vai ser aumentado na main, de 1 - 5
    printf("\n%s\n", question.question);
    
    printf("\na) %s\n", question.options[0]);
    printf("b) %s\n", question.options[1]);
    printf("c) %s\n", question.options[2]);
    printf("d) %s\n", question.options[3]);

    printf("\n------------------------------------------------------------------------------------------------------------------------------\n");

    printf("\n--- Ajuda ---\n");
    printf("[1] Pular pergunta (%dx)\n", recurso_pular);
    printf("[2] Pedir ajuda a plateia (%dx)\n", recurso_plateia);
    printf("[3] Pedir ajuda aos universitários (%dx)\n", recurso_universitarios);
    printf("[4] Pedir ajuda as cartas (%dx)\n", recurso_carta);
    printf("[5] Parar\n");
    printf("\n------------------------------------------------------------------------------------------------------------------------------\n");

    printf("Entre com a sua opção [a-d] para responder ou [1-5] para receber ajuda: ");
}

// printf("\n== Voce possui um total acumulado de R$ %.2lf ==\n", score);
