#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char question_level;
    char question[200];
    char options[4][30];
    char answer;
} Question;

void read_questions(Question **questions, FILE *file, const unsigned short questions_to_read);
void alloc_questions(Question **questions, const unsigned short questions_number);
void free_questions(Question **questions);
void increases_position_file(FILE *file, const unsigned short position);

#endif
