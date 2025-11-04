#include "questions.h"
#include <stdio.h>

/**
 * Lê as questões do arquivo e as armazena em um vetor de questões.
 *
 * @param Question **questions Ponteiro para o vetor de questões.
 * @param FILE *file Ponteiro para o arquivo.
 * @param unsigned short questions_to_read Número de questões a serem lidas.
 */
void read_questions(Question **questions, FILE *file, size_t questions_to_read) {
    fread(*questions, sizeof(Question), questions_to_read, file);
}

/**
 * Aloca memória para um vetor de questões.
 *
 * @param Question **questions Ponteiro para o vetor de questões.
 * @param unsigned short questions_number Número de questões a serem alocadas.
 */
void alloc_questions(Question **questions, size_t questions_number) {
    *questions = (Question *) malloc(sizeof(Question) * questions_number);

    if (*questions == NULL) {
        perror("Houve um erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
}

/**
 * Libera a memória alocada para um vetor de questões.
 *
 * @param Question **questions Ponteiro para o vetor de questões.
 */
void free_questions(Question **questions) {
    if (*questions != NULL) {
        free(*questions);
        *questions = NULL;
    }
}
