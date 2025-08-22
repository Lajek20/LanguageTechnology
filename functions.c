// This is where we start writing out functions
// Members who have worked on this file:

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDS_IN_ORDBOG 64896
#define WORDS_COUNT 300
#define SUB_END_COUNT 9
#define SUB_END_LEN 4
#define ADJ_END_COUNT 8
#define ADJ_END_LEN 5
#define VER_END_COUNT 11
#define VER_END_LEN 5
#define ADV_END_COUNT 5
#define ADV_END_LEN 4
#define ORDBOG_CLASS_COUNT 15
#define ORDBOG_CLASS_LEN 11

int str_ending_compare(char *ord, char *ending);
char *to_lower_case(char *ord);

int substantiver(char *ord);  // navneord
int is_capital_letter(char first_letter);
int sub_correct_ending(char *ord);

int adjektiver(char *ord);  // tillaegsord
int adj_correct_ending(char *ord);

int verber(char *ord);  // udsagnsord
int ver_correct_ending(char *ord);  

int adverbier(char *ord);  // biord
int adv_correct_ending(char *ord);

int artikler(char *ord);  // kendeord
int is_article(char *ord);

int konjunktioner(char *ord);  // bindeord
int is_conjunction(char *ord);

int praepositioner(char *ord);  // forholdsord
int is_preposition(char *ord);

int udraabsord(char *ord);  // udraabsord
int is_yelling(char *ord);

int lydord(char *ord);  // lydord
int is_sound(char *ord);

int talord(char *ord);  // talord
int cmp_talord(char *ord);
int str_talord(char *ord);

int pronomener(char *ord); // stedord 
int is_pronomener(char *ord);

char * BinSearch(char ** ord_array, char ** word_class, char * ord);

int bin_search(char *search, char **ord_array);
char ** get_wordclass(int index, char **dictionary_words, char **dictionary_wordclass);
char * get_estimate(char ** dictionary_words, char ** dictionary_wordclass, char * ord);

void run_switch2(char *ord, int * class_score, char ** dictionary_words, int index);
int class_index(char *ord);

char * index_to_dataclass(int index);

int str_ending_compare(char *ord, char *ending) {
    int c;
    // int result;
    int ord_len = (strlen(ord) + 1);
    int ending_len = (strlen(ending) + 1);
    char ord_ending[ending_len];

    // printf(" %s, %s\n", ord, ending);

    for (c = 1; c <= ending_len; c++) {
        ord_ending[ending_len - c] = ord[ord_len - c];
    }

    // printf(" %s, %s\n", ending, ord_ending);

    return strcmp(ending, ord_ending);
}



char *to_lower_case(char *ord) {

    char * lowercase_ord = malloc(WORDS_COUNT * sizeof(* lowercase_ord));

    int ord_len = strlen(ord) + 1;
    int c;

    for (c = 0; c < ord_len; c++) {
        lowercase_ord[c] = tolower(ord[c]);
    }
    //printf("Omskrevet ord er %s.\n", ord);
    return lowercase_ord;
}

int substantiver(char *ord) {
    //printf(" %s\n\n", ord);
    int score = 0;
    if (is_capital_letter(ord[0]) == 2) {
        //printf("capital er opfyldt\n\n");
        //printf("nyt ord er %s\n\n", to_lower_case(ord));
        score++;
    } else {
        //printf("capital er ikke opfyldt\n\n");
    }

    if (sub_correct_ending(ord) == 1) {
        //printf("sub_ending er opfyldt\n\n");
        score++;
    } else {
        //printf("sub_ending er ikke opfyldt\n\n");
    }

    return score;
}

int is_capital_letter(char first_letter) {
    if (first_letter >= 'A' && first_letter <= 'Z') {
        return 2;
    } else if (first_letter >= 'a' && first_letter <= 'z') {
        return 1;
    } else {
        return 0;
    }
}

int sub_correct_ending(char *ord) {
    // int c;
    char sub_endings[SUB_END_COUNT][SUB_END_LEN] = {"ene", "ne", "er", "et",
                                                    "en",  "r",  "s",  "e"};

    for (int c = 0; c < SUB_END_COUNT; c++) {
        if (str_ending_compare(ord, sub_endings[c]) == 0) {
            return 1;
        }
    }
    return 0;
}

int adjektiver(char *ord) {
    if (adj_correct_ending(ord) == 1) {
        //printf("adj_ending er opfyldt\n\n");
        return 1;
    } else {
        //printf("adj_ending er ikke opfyldt\n\n");
        return 0;
    }
    return 0;
}

int adj_correct_ending(char *ord) {
    // int c;
    char adj_endings[ADJ_END_COUNT][ADJ_END_LEN] = {"este", "est", "ere", "st",
                                                    "re",   "t",   "e"};

    for (int c = 0; c < ADJ_END_COUNT; c++) {
        if (str_ending_compare(ord, adj_endings[c]) == 0) {
            return 1;
        }
    }
    return 0;
}

int verber(char *ord) {
    if (ver_correct_ending(ord) == 1) {
        //printf("ver_ending er opfyldt\n\n");
        return 1;
    } else {
        //printf("ver_ending er ikke opfyldt\n\n");
        return 0;
    }
    return 0;
}

int ver_correct_ending(char *ord) {
    // int c;
    char ver_endings[VER_END_COUNT][VER_END_LEN] = {
        "ende", "tes", "ede", "es", "te", "et", "de", "er", "t", "r", "e"};

    for (int c = 0; c < VER_END_COUNT; c++) {
        if (str_ending_compare(ord, ver_endings[c]) == 0) {
            return 1;
        }
    }
    return 0;
}

int adverbier(char *ord) {
    if (adv_correct_ending(ord) == 1) {
        //printf("adv_ending er opfyldt\n\n");
        return 1;
    } else {
        //printf("adv_ending er ikke opfyldt\n\n");
        return 0;
    }
    return 0;
}

int adv_correct_ending(char *ord) {
    // int c;
    char adv_endings[ADV_END_COUNT][ADV_END_LEN] = {"vis", "lig", "ig", "t"};

    for (int c = 0; c < ADV_END_COUNT; c++) {
        if (str_ending_compare(ord, adv_endings[c]) == 0) {
            return 1;
        }
    }
    return 0;
}

int artikler(char *ord) {
    if (is_article(ord) == 1) {
        //printf("article er opfyldt\n\n");
        return 1;
    } else {
        //printf("article er ikke opfyldt\n\n");
        return 0;
    }

    return 0;
}

int is_article(char *ord) {
    char article[5][6] = {"den", "det", "en", "et", "de"};

    for (int i = 0; i < (int)sizeof(article); i++) {
        if (strcmp(ord, article[i]) ==
            0)  // strcmp(ene_string, anden_string) tjekker om første-string
                // tilsvarer anden-string {
            return 1;
    }
    return 0;
}

int konjunktioner(char *ord) {
    if (is_conjunction(ord) == 1) {
        //printf("conjunction er opfyldt\n\n");
        return 1;
    } else {
        //printf("conjunction er ikke opfyldt\n\n");
        return 0;
    }
    return 0;
}

int is_conjunction(char *ord) {
    char sideordnende[5][8] = {"eller", "for", "men", "saa", "og"};
    char underordnende[12][8] = {"hvorfor", "hvordan", "hvilken", "hvilket",
                                 "fordi",   "hvor",    "hvad",    "hvis",
                                 "naar",    "mens",    "der",     "som"};
    char saa[3][6] = {"om", "at", "da"};

    for (int i = 0; i < (int)sizeof(sideordnende); i++) {
        if (strcmp(ord, sideordnende[i]) == 0) {
            return 1;
        }
    }
    for (int i = 0; i < (int)sizeof(underordnende); i++) {
        if (strcmp(ord, underordnende[i]) == 0) {
            return 1;
        }
    }
    for (int i = 0; i < (int)sizeof(saa); i++) {
        if (strcmp(ord, saa[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int praepositioner(char *ord) {
    if (is_preposition(ord) == 1) {
        //printf("preposition er opfyldt\n\n");
        return 1;
    } else {
        //printf("preposition er ikke opfyldt\n\n");
        return 0;
    }
    return 0;
}

int is_preposition(char *ord) {
    char preposition[26][14] = {
        "omkring", "mellem", "gennem", "under", "efter", "foran", "forbi",
        "inden",   "langs",  "over",   "imod",  "uden",  "foer",  "til",
        "fra",     "ved",    "for",    "med",   "hos",   "mod",   "bag",
        "paa",     "om",     "af",     "ad",    "i"};

    for (int i = 0; i < 26; i++) {
        if (strcmp(ord, preposition[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int udraabsord(char *ord) {
    if (is_yelling(ord) == 1) {
        //printf("udraabsord er opfyldt\n\n");
        return 1;
    } else {
        //printf("udraabsord er ikke opfyldt\n\n");
        return 0;
    }
    return 0;
}

int is_yelling(char *ord) {
    char yelling[17][9] = {"tillykke", "fandens", "satans", "farvel", "barvo",
                           "fuck",     "lort",    "roev",   "hej",    "nej",
                           "aah",      "ja",      "av",     "wow",    "shh",
                           "hmm",      "ih"};

    for (int i = 0; i < (int)sizeof(yelling); i++) {
        if (strcmp(ord, yelling[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int lydord(char *ord) {
    if (is_sound(ord) == 1) {
        //printf("lydord er opfyldt\n\n");
        return 1;
    } else {
        //printf("lydord er ikke opfyldt\n\n");
        return 0;
    }
    return 0;
}

int is_sound(char *ord) {
    char sound[9][11] = {"dingeling", "kykliky", "pladask", "hvisle", "bipper",
                         "miav",      "atju",    "muh",     "bip"};

    for (int i = 0; i < (int)sizeof(sound); i++) {
        if (strcmp(ord, sound[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int talord(char *ord) {
    if (cmp_talord(ord) == 1 || str_talord(ord) == 1) {
        //printf("talord er opfyldt\n\n");
        return 1;
    } else {
        //printf("talord er ikke opfyldt\n\n");
        return 0;
    }
    return 0;
}

int cmp_talord(char *ord) {
    char talord[33][11] = {
        "nul",      "en",      "to",         "tre",     "fire",     "fem",
        "seks",     "syv",     "otte",       "ni",      "ti",       "elleve",
        "tolv",     "tretten", "fjorten",    "femten",  "seksten",  "sytten",
        "atten",    "nitten",  "tyve",       "tredive", "fyrre",    "halvtreds",
        "tres",     "treds",   "halvfjerds", "firs",    "halvfems", "hundred",
        "hundrede", "tusind",  "tudsinde"};

    for (int i = 0; i < (int)sizeof(talord); i++) {
        if (strcmp(ord, talord[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int str_talord(char *ord) {
    char tal_ord[22][11] = {
        "enog",    "toog",       "treog",   "fireog",  "femog",     "seksog",
        "syvog",   "otteog",     "niog",    "hundred", "hundrede",  "tusind",
        "tusinde", "tyve",       "tredive", "fyrre",   "halvtreds", "tres",
        "treds",   "halvfjerds", "firs",    "halvfems"};

    for (int i = 0; i < (int)sizeof(tal_ord); i++) {
        if (strstr(ord, tal_ord[i])) {
            return 1;
        }
    }
    return 0;
}

int pronomener(char *ord) {
    if (is_pronomener(ord) == 1) {
        //printf("pronomener er opfyldt\n\n");
        return 1;
    } else {
        //printf("pronomener er ikke opfyldt\n\n");
        return 0;
    }
    return 0;
}

int is_pronomener(char *ord) {
    char personlige[18][6] = {"jeg", "du",    "han", "hun", "det", "den",
                              "vi",  "i",     "de",  "mig", "dig", "dem",
                              "ham", "hende", "os",  "jer", "dem"};
    char ejestedord[16][7] = {
        "min",  "mit",  "mine",  "din",   "dit",   "dine", "hans", "hendes",
        "dens", "dets", "vores", "jeres", "deres", "sin",  "sit",  "sine"};
    char henvisende[2][6] = {"der", "som"};

    for (int i = 0; i < (int)sizeof(personlige); i++) {
        if (strcmp(ord, personlige[i]) == 0) {
            return 1;
        }
    }

    for (int i = 0; i < (int)sizeof(ejestedord); i++) {
        if (strcmp(ord, ejestedord[i]) == 0) {
            return 1;
        }
    }

    for (int i = 0; i < (int)sizeof(henvisende); i++) {
        if (strcmp(ord, henvisende[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

//returns the index of the searched word, in the given array.
int bin_search(char *search, char **dictionary_words){
    
    char * lowercase_search = to_lower_case(search);
   
    int maxRuntime = 0;
    int first = 0;
    int last = WORDS_IN_ORDBOG;
    int middle = (first+last)/2;

   
    while (first <= last && maxRuntime < 30){
        // printf("%d, %d, %d\n", first, last, middle);
        if ((strcmp(lowercase_search, dictionary_words[middle])) > 0){
            first = middle;
        
        }else if ((strcmp(dictionary_words[middle], lowercase_search)) == 0){
            // printf("'%s' found at location %d.\n", lowercase_search, middle+1);
            free(lowercase_search);
            return middle;
        }
        else{
            last = middle;
        }

        middle = (first + last)/2;
        maxRuntime++;
    }
    if (first > last){
        printf("Not found! '%s' isn't present in the list.\n", lowercase_search);
    }
    //printf("naede til return\n");
    free(lowercase_search);
    return -1;
}

char ** get_wordclass(int index, char **dictionary_words, char **dictionary_wordclass){

    char ** wordclasses = malloc(10 * sizeof(char *));
    for(int i=0; i<10; i++){
        wordclasses[i] = malloc(300 * sizeof(char));
    }

    //Checker at wordclasses blev oprettet i Memory,
    if(wordclasses != NULL){
        int new_index = index;
        int i = 0;
        //checks above index and acumulate wordclasses
        while(strcmp(dictionary_words[index], dictionary_words[new_index]) == 0){
            //wordclasses[i] = (char *)malloc(WORDS_COUNT * sizeof(char));
            if(wordclasses[i] != NULL){
                wordclasses[i] = dictionary_wordclass[new_index];
                new_index++;
                i++;
            }else{
                printf("NO SPACE IN MEMORY");
            }            
        } // addr2line -e ./a.out 0x564b002f2a65 
        //checks below index and acumulate wordclasses
        new_index = index-1;
        while(strcmp(dictionary_words[index], dictionary_words[new_index]) == 0){
            //wordclasses[i] = (char *)malloc(WORDS_COUNT * sizeof(char));
            if(wordclasses[i] != NULL){
                wordclasses[i] = dictionary_wordclass[new_index];
                new_index--;
                i++;
                
            }else{
                printf("NO SPACE IN MEMORY");
            }    
        }
    }else{
        //Exit failure hvis der ikke var palds i memory
        printf("NO SPACE IN MEMORY");
    }
    
    return wordclasses;
}


int containscomma(char * word){
    int commacount = 0;
    for(int i = 0; i < (int)sizeof(word);i++){
        if(word[i] == ','){
            commacount++;
        }
    }
    return commacount;
}

char * get_estimate(char ** dictionary_words, char ** dictionary_wordclass, char * ord){
    
    //int *wordclass = calloc(WORDS_COUNT, sizeof(int));
    int * class_score = calloc(WORDS_COUNT, sizeof(int));
    
    if(class_score == NULL){
        exit(EXIT_FAILURE);
    }

    int index = bin_search(ord, dictionary_words);
    //printf("%d, %s", index, dictionary_words[index]);

    if(index != -1){
        char ** wordclasses = get_wordclass(index, dictionary_words, dictionary_wordclass);
        //printf("%s\n", wordclasses[0]);
        int i = 0;
        //checker om ordet indeholder 2 klasser og splitter den op i 2 klasser hvis den gør.
        
        while(i < 10 && wordclasses[i] != NULL){
            if(containscomma(wordclasses[i]) > 0){
            //if(strstr(wordclasses[i], ",") != NULL){
                //printf("%s\n",wordclasses[i]);
                char * token = strtok(wordclasses[i], ",");
                wordclasses[i] = token;
                token = strtok(NULL, ",");
                wordclasses[i+1] = token;
            }
            i++;  
        }
        if(wordclasses[1] == 0 && strcmp(wordclasses[0], "x") != 0){

            int class_i = class_index(wordclasses[0]);
            //printf("%s\n", wordclasses[0]);
            char * ordklasse = index_to_dataclass(class_i);
            return ordklasse;
            
        }else{
            //run switch
            for(int j = 0; j < i; j++){
                run_switch2(wordclasses[j], class_score, dictionary_words, index);
            }
            //check highest score 
            int score = -1;
            for(int j = 0; j < ORDBOG_CLASS_COUNT; j++){
                if(class_score[j] != 0 && class_score[j] >= score){
                    score = j;
                }
            }
            char * ordklasse = index_to_dataclass(score);
            return ordklasse;
        }
    
    }else{
        //printf("ordet findes ikke i ordbogen vi kører standart funktioner:");
    }
    return "x";
}

void run_switch2(char *ord, int * class_score, char ** dictionary_words, int index) {    
    if(strcmp(ord, "x") == 0){
        //printf("- we have to run other tests on this word: \n");
    }else if(strcmp(ord, "pron") == 0){
        class_score[0] = 1; //pronomener(dictionary_words[index]);
    }else if(strcmp(ord, "artikel") == 0){
        class_score[1] = 1; //artikler(dictionary_words[index]);
    }else if(strcmp(ord, "sb") == 0){
        class_score[2] = 1; //substantiver(dictionary_words[index]);
        //printf("substantiv + %d\n", class_score[2]);
    }else if(strcmp(ord, "vb") == 0){
        class_score[3] = 1; //verber(dictionary_words[index]);
    }else if(strcmp(ord, "adj") == 0){
        class_score[4] = 1; //adjektiver(dictionary_words[index]);
    }else if(strcmp(ord, "adv") == 0){
        class_score[5] = 1; //adverbier(dictionary_words[index]);
    }else if(strcmp(ord, "konj") == 0){
        class_score[6] = 1; //konjunktioner(dictionary_words[index]);
    }else if(strcmp(ord, "prop") == 0){
        //class_score[7] = prop(dictionary_words[index]); // Dette skal laves
    }else if(strcmp(ord, "praep") == 0){
        class_score[8] = 1; //praepositioner(dictionary_words[index]);
    }else if(strcmp(ord, "praefiks") == 0){
        //class_score[9] = praefiks(dictionary_words[index]); // Dette skal laves
    }else if(strcmp(ord, "talord") == 0){
        class_score[10] = 1; //talord(dictionary_words[index]);
    }else if(strcmp(ord, "lydord") == 0){
        class_score[11] = 1; //lydord(dictionary_words[index]);
    }else if(strcmp(ord, "udraabsord") == 0){
        class_score[12] = 1; //udraabsord(dictionary_words[index]);
    }else if(strcmp(ord, "fork") == 0){
        //class_score[13] = fork(dictionary_words[index]) // Dette skal laves
    }else{
        //printf("fejl i switch");
    }
    
    //return "test";
}

int class_index(char *ord) {    
    
    if(strcmp(ord, "pron")){
        return 0;
    }else if (strcmp(ord, "artikel")){
        return 1;
    }else if (strcmp(ord, "sb")){
        return 2;
    }else if (strcmp(ord, "vb")){
        return 3;
    }else if (strcmp(ord, "adj")){
        return 4;
    }else if (strcmp(ord, "adv")){
        return 5;
    }else if (strcmp(ord, "konj")){
        return 6;
    }else if (strcmp(ord, "prop")){
        return 7;
    }else if (strcmp(ord, "praep")){
        return 8;
    }else if (strcmp(ord, "praefiks")){
        return 9;
    }else if (strcmp(ord, "talord")){
        return 10;
    }else if (strcmp(ord, "lydord")){
        return 11;
    }else if (strcmp(ord, "udraabsord")){
        return 12;
    }else if (strcmp(ord, "fork")){
        return 13;
    }else if (strcmp(ord, ".")){
        return 14;
    }
    return -1;
}

char * index_to_dataclass(int index) {
    switch (index)
    {
    case 0:
        return "PRON";
        break;
    case 1:
        return "DET";
        break; 
    case 2:
        return "NOUN";
        break; 
    case 3:
        return "VERB"; //eller AUX
        break; 
    case 4:
        return "ADJ";
        break; 
    case 5:
        return "ADV";
        break; 
    case 6:
        return "CCONJ"; // Eller SCONJ og PART
        break; 
    case 7:
        return "PROPN";
        break; 
    case 8:
        return "ADP"; 
        break; 
    case 9:
        return "x";//Praefiks eksistere ikke
        break; 
    case 10:
        return "NUM";
        break; 
    case 11:
        return "INTJ"; 
        break; 
    case 12:
        return "x"; //udråbsord eksistere ikke
        break; 
    case 13:
        return "x"; //forkortelser eksistere ikke
        break;   
    case 14:
        return "PUNCT";
        break;   
    }

    return "x";
}