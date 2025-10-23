#include "questions.h"
#include <stdio.h>

/**
 * Lê as questões do arquivo e as armazena em um vetor de questões.
 *
 * @param Question **questions Ponteiro para o vetor de questões.
 * @param FILE *file Ponteiro para o arquivo.
 * @param unsigned short questions_to_read Número de questões a serem lidas.
 */
void read_questions(Question **questions, FILE *file, const unsigned short start_position, const unsigned short questions_to_read) {
    fseek(file, start_position * sizeof(Question), SEEK_SET);
    
    fread(*questions, sizeof(Question), questions_to_read, file);
}

/**
 * Aloca memória para um vetor de questões.
 *
 * @param Question **questions Ponteiro para o vetor de questões.
 * @param unsigned short questions_number Número de questões a serem alocadas.
 */
void alloc_questions(Question **questions, const unsigned short questions_number) {
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
    free(*questions);
}

/**
 * Incrementa a posição do arquivo.
 *
 * @param FILE *file Ponteiro para o arquivo.
 * param unsigned short position Posição a ser incrementada.
 */
// void seek_question_position(FILE *file, const unsigned short position) {
// }
