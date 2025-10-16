#include "questions.h"
#include <stdio.h>

void read_questions(Question **questions, FILE *file, const unsigned short questions_to_read) {
    fread(*questions, sizeof(Question), questions_to_read, file);
}

void alloc_questions(Question **questions, const unsigned short questions_number) {
    *questions = (Question *) malloc(sizeof(Question) * questions_number);

    if (*questions == NULL) {
        perror("Houve um erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
}

void free_questions(Question **questions) {
    free(*questions);
}

void increases_position_file(FILE *file, const unsigned short position) {
    fseek(file, SEEK_CUR, position * sizeof(Question));
}
