//This is where we start writing our input
//Members who have worked on this file: Jonathan, Frederik

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_LEN 1000
#define WORD_LEN 500
#define MAX_FILE_LEN 50
#define DICTIONARY "Data/RO2012.opslagsord.med.homnr.og.ordklasse_sorted_2.csv"
#define DATA_TRAIN "Data/da_ddt-ud-train"
#define DATA_TEST "Data/da_ddt-ud-test"


void arraytest();
char * menu_filvalg();

void printArray(char ** array_words, char ** array_class);
void get_data(char ** data_words, char ** data_wordclass, int data_size);
void get_dictionary(char ** dictionary_words, char ** dictionary_wordclass, int data_size);

//Henter Ord og Ordklasser fra Test og Train filen.
void get_data(char ** data_words, char ** data_wordclass, int data_size){

    char * fil = menu_filvalg();

    //Laver Array med Malloc
    for (int i = 0; i < data_size; i++){
        data_words[i] = (char *)malloc(WORD_LEN * sizeof(char)); 
        data_wordclass[i] = (char *)malloc(WORD_LEN * sizeof(char)); 
    }

    //Åbner fil
    FILE *inp = fopen(fil, "r");
    char line[LINE_LEN];
    char *status = fgets(line, LINE_LEN, inp);
    
    int i = 0;
    while(i < data_size && status != 0){
        //printf("i: %d, ", i);
        //Hvis sidste linje i line er \n så byt det ud med \0
        if (line[strlen(line) - 1] == '\n'){
            line[strlen(line) - 1] = '\0';
        }
        
        //Læser alle ord fra linjen ind i Token, som nu består af flere ord.
        char *token = strtok(line, "\t");

        //Tjekker om Token er tom eller en kommentar
        if(token == NULL || token[0] == '#'){
            //printf("worked");
            status = fgets(line, LINE_LEN, inp);
            
            continue;
        }

        //skipper et ord i token.
        token = strtok(NULL, "\t");
        //printf("ord: %s ", token);
        //læser ordet fra Token og sætter det ind i Ord array
        int f;


        for(f = 0; f < (int)strlen(token); f++){
            data_words[i][f] = token[f];
        }
        data_words[i][f] = '\0';

        //skipper et ord i token.
        token = strtok(NULL, "\t");
        token = strtok(NULL, "\t");

        //printf("\t\tclass: %s\n", token);        

        for(f = 0; f < (int)strlen(token); f++){
            data_wordclass[i][f] = token[f];
        }
        data_wordclass[i][f] = '\0';

        //Læser ny linje ind i status
        status = fgets(line, LINE_LEN, inp);
        i++;
    }
    
    //printArray(array_words, array_class);
} 

//Henter Ord og ordklasser fra Ordbogs filen
void get_dictionary(char ** dictionary_words, char ** dictionary_wordclass, int data_size){

    //Fil placering
    char *fil = DICTIONARY;

    //Laver Array med Malloc
    for (int i = 0; i < data_size; i++){
        dictionary_words[i] = (char *)malloc(WORD_LEN * sizeof(char)); 
        dictionary_wordclass[i] = (char *)malloc(WORD_LEN * sizeof(char)); 
    }

    //Åbner fil
    FILE *inp = fopen(fil, "r");
    char line[LINE_LEN];
    char *status = fgets(line, LINE_LEN, inp);
    
    //Looper for hver linje i fil
    int i = 0;
    while(i < data_size && status != 0){
        //printf("i: %d ; ", i);
        //Hvis sidste linje i line er \n så byt det ud med \0
        if (line[strlen(line) - 1] == '\n'){
            line[strlen(line) - 1] = '\0';
        }
        
        //springer linje over hvis ordet ikke har en token
        //printf("\tline: %s\t",line);
        if (line[strlen(line)-1] == ';'){
            strcat(line,"x");
        }

        //printf(" line is: %s\n", line);
        char *token = strtok(line, ";");

        //printf("%s ; ", token);
        //Tjekker om Token er tom eller en kommentar
        if(token == NULL){
            status = fgets(line, LINE_LEN, inp);
            continue;
        }

        //læser ordet fra Token og sætter det ind i Ord array
        int f;
        for(f = 0; f < (int)strlen(token); f++){
            dictionary_words[i][f] = token[f];
        }
        dictionary_words[i][f] = '\0';

        //skipper et ord i token.
        token = strtok(NULL, "\r");

        
        if(token != NULL){
            for(f = 0; f < (int)strlen(token); f++){
                dictionary_wordclass[i][f] = token[f];
            }
            dictionary_wordclass[i][f] = '\0';
        }
        //printf("%s\n", token);
        
        status = fgets(line, LINE_LEN, inp);
        //printf("%d", i);
        i++;
    }

    //printArray(array_words, array_class);
} 

void printArray(char ** array_words, char ** array_class){
    int i = 0;
    while (array_words[i] != NULL){
        printf("i: %d, %s \t %s \n", i, array_words[i], array_class[i]);

        i++;
    }   
}

char * menu_filvalg(){ //Skal implementeres, så den retunerer "filnavn" i korrekt sammenhæng.
    char * fil = (char *)malloc(MAX_FILE_LEN * sizeof(char *));
    int menu;
    //Læsning til brugeren, spørg om valg til switchen 1, 2 eller 3.
    printf("------------------------\n");
    printf("Valgmulighedder\n1: Train\n2: Test\n3: Skriv selv adresse paa fil til indlaesning.\n");
    scanf("%d",&menu);

    switch (menu){
    case 1:
        return DATA_TRAIN;
    case 2:
        return DATA_TEST;
    //Case 3 sprøger til at brugeren selv skal vælge
    case 3:      
        printf("skriv filnavns'stien f.eks. Data/da_ddt-ud-train\n");
        scanf("%s", fil);
    }

    return "0";
}