#ifndef RANDOM_H
#define RANDOM_H

#include <stdio.h>
#include <stdlib.h>

char get_weighted_option(char correct_question, int probability, char *wrong_options, int number_options);
int get_random_number(unsigned short min, unsigned short max, int numbers_sorted);

#endif
