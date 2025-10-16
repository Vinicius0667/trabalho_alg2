#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char buffer[2048];
    FILE *file = fopen("perguntas.dat", "rb");

    if (file == NULL) {
        perror("Houve um erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    fread(buffer, sizeof(buffer), 10, file);

    printf("%s\n", buffer);

    fclose(file);
}
