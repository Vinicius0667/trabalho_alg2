Question* selecionar_pergutas_nivel(Question* questions, char nivel){
    int indices[70];
    int times = 0;

    for( int i = 0; i < 70; i++){
        if(questions[i].question_level == nivel){
            indices[times++] = i;
        }
    }

    if (times > 0){
        int random_index = indices[rand() % times];
        // Excluir o indice selecionado de indices
        return &questions[random_index];
    }

    return NULL;
}