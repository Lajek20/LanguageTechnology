#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "input.c"
#include "functions.c"



#define WORDS_IN_DATA 80000
#define WORDS_IN_DICTIONARY 64894


int main(void){
    
    
    char **data_words = (char **)malloc(WORDS_IN_DATA * sizeof(char *));
    char **data_wordclass = (char **)malloc(WORDS_IN_DATA * sizeof(char *));
    
    char **estimate_wordclass = (char **)malloc(WORDS_IN_DATA * sizeof(char *));

    //truefalse array
    int *truefalse_array = (int*)calloc(WORDS_IN_DATA, sizeof(int));

    char **dictionary_words = (char **)malloc(WORDS_IN_DICTIONARY * sizeof(char *));
    char **dictionary_wordclass = (char **)malloc(WORDS_IN_DICTIONARY * sizeof(char *));

    get_data(data_words, data_wordclass, WORDS_IN_DATA);
    get_dictionary(dictionary_words, dictionary_wordclass, WORDS_IN_DICTIONARY);
    
    int winrate = 0;
    int i;

    int tidstagning = 0;
    int printud = 0;
    printf("Vil du tage tid? tryk 1, ellers tryk andet\n");
    scanf("%d", &tidstagning);
    printf("Vil du printe ordklasser ud til konsol? tryk 1, ellers tryk andet\n");
    scanf("%d", &printud);
    //estimate_wordclass[0] = get_estimate(dictionary_words, dictionary_wordclass, data_words[0]);

    //printf("%d: %s\t%s\t%s\t%d\n",i+1, data_words[0], data_wordclass[0], estimate_wordclass[0], truefalse_array[0]);

    //estimate_wordclass[0] = get_estimate(dictionary_words, dictionary_wordclass, data_words[4405]);
    //printf("%s %s\n",estimate_wordclass[0], data_words[4405]);
    


        clock_t t; 
        t = clock(); 

    

    for(i = 0; i < WORDS_IN_DATA; i++) {

        estimate_wordclass[i] = get_estimate(dictionary_words, dictionary_wordclass, data_words[i]);

        if(data_words[i] != NULL || data_wordclass[i] != NULL || estimate_wordclass[i] != NULL){
            
            //Understående strcmp har endnu ingen funktion, da de er formateret hver for sig.
            //+ så bliver int(output_truefalse) ikke 0 eller 1, da stringcomp. ikke giver 1 eller 0.
            if(strcmp(data_wordclass[i], estimate_wordclass[i]) == 0) {
            truefalse_array[i] = 1;
            winrate++;
            }
            if(printud == 1){
            printf("%d: %s\t%s\t%s\t%d\n",i+1, data_words[i], data_wordclass[i], estimate_wordclass[i], truefalse_array[i]);
            }

        }else{
            //printf("%d: Fejl\n", i);
        }
    }
    
    printf("Programmets accuracy er: %d out of %d\n", winrate, i);
    if(tidstagning == 1){
        t = clock() - t; 
        double time_taken = ((double)t)/CLOCKS_PER_SEC;
  
        printf("Det tog %f sekunder at finde %d ordklasser \n", time_taken, WORDS_IN_DATA); 
        printf("Ord pr. sek: %d \n", ((int)(1 / time_taken * WORDS_IN_DATA))); 
    }

    //Free plads (kunne godt være mere grundigt)
    free(data_words);
    free(data_wordclass);
    free(estimate_wordclass);
    free(truefalse_array);
    free(dictionary_words);
    free(dictionary_wordclass);
    
    return 0;
}