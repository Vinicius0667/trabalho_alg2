#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "questions.h"
#include "random_questions.h"
// #include "embaralhar.h"

void print_question(Question question, const unsigned short question_number, int recurso_plateia, int recurso_pular, int recurso_carta, int recurso_universitarios, double premio_total);

int main(void) {
    Question *questions = NULL;
    FILE *file;
    srand(time(NULL));
    double premio_total = 0.0;
    char answer;
    int recurso_plateia = 3, recurso_pular = 3, recurso_carta = 3, recurso_universitarios = 3;
    int nivel_dificuldade = 1;
    int loser = 0, winner = 0;

    file = fopen("perguntas.dat", "rb");

    if (file == NULL) {
        perror("Houve um erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    printf("\n------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n                                          SEJA BEM VINDO AO SHOW DO MILHÃO!!!                                                 \n");
    printf("\n------------------------------------------------------------------------------------------------------------------------------\n");
    
    while(!loser && !winner && nivel_dificuldade <= 4){
        unsigned short questions_by_level = (nivel_dificuldade == 4) ? 10 : 20;
        unsigned short acertos = 1;
        
        unsigned short question_number = (nivel_dificuldade == 4) ? 1 : 5;
        unsigned short start_pos = (nivel_dificuldade - 1) * 20;

        if (questions != NULL){
            free_questions(&questions);
        }

        alloc_questions(&questions, questions_by_level);

        if (nivel_dificuldade == 2) premio_total = 10000;
        if (nivel_dificuldade == 3) premio_total = 100000;
        // if(count == 1 && nivel_dificuldade == 4) premio_total = 1000000; GANHOU
        
        while (!loser){
            read_questions(&questions, file, start_pos, questions_by_level);

            unsigned short random_number = get_random_number(0,questions_by_level);
            Question *atual_question = &questions[random_number];
            
            print_question(*atual_question, acertos, recurso_plateia, recurso_pular, recurso_carta, recurso_universitarios, premio_total);
            scanf(" %c", &answer);

            if (answer == atual_question->answer){
                printf("\nVocê acertou!!!\n");
                if(acertos >= 1 && nivel_dificuldade == 1) premio_total = 1000 * acertos;
                if(acertos >= 1 && nivel_dificuldade == 2) premio_total = 10000 * (acertos +1);
                if(acertos >= 1 && nivel_dificuldade == 3) premio_total = 100000 * (acertos +1);
                acertos += 1;
            } else {
                printf("\nVocê perdeu tudo!!! : (\n");
                loser = 1;
                break;
            }

            if (acertos > question_number){
                nivel_dificuldade++;
                break;
            }
        }

        if (loser) break;
    }
    
    fclose(file);
    return EXIT_SUCCESS;
}

void print_question(Question question, const unsigned short acertos, int recurso_plateia, int recurso_pular, int recurso_carta, int recurso_universitarios, double premio_total) {

    
    printf("\nPergunta %hu\n", acertos); // acertos vai ser aumentado na main, de 1 - 5
    printf("\n%s\n", question.question);
    
    printf("\na) %s\n", question.options[0]);
    printf("b) %s\n", question.options[1]);
    printf("c) %s\n", question.options[2]);
    printf("d) %s\n", question.options[3]);
    // Perguntas do segundo Bloco não estão sendo lidas corretamentes...
    printf("\n------------------------------------------------------------------------------------------------------------------------------\n");

    printf("\n--- Ajuda ---\n");
    printf("[1] Pular pergunta (%dx)\n", recurso_pular);
    printf("[2] Pedir ajuda a plateia (%dx)\n", recurso_plateia);
    printf("[3] Pedir ajuda aos universitários (%dx)\n", recurso_universitarios);
    printf("[4] Pedir ajuda as cartas (%dx)\n", recurso_carta);
    printf("[5] Parar\n");
    printf("\n------------------------------------------------------------------------------------------------------------------------------\n");

    printf("\n== Voce possui um total acumulado de R$ %.2lf ==\n", premio_total);
    printf("Entre com a sua opção [a-d] para responder ou [1-5] para receber ajuda: ");
}

