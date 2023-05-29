#define M 2003	//kich thuoc hashtable

//cau truc cua 1 tu vung
struct Vocab{
    char english[256];
    char type[256];
    char meaning[256];
};
typedef struct Vocab Vocab;

//cau truc cua 1 node 
struct DictNode{
    Vocab word;
    DictNode *next;
};
typedef struct DictNode DictNode;

//khoi tao hashtable
void init(DictNode *heads[]){
    for(int i = 0; i < M; i++){
        heads[i] = NULL;
    }
} 

//khai bao node
DictNode * createNode(Vocab w){
    DictNode *new_word = (DictNode *)malloc(sizeof(DictNode));
    new_word->word = w;
    new_word->next = NULL;
    return new_word;
}

//tao hash funct djb2
int hashFunct(char *str){
    unsigned long hash = 5381;
    int c;
    
    while(c = *str++){
        hash = ((hash << 5) + hash) + c; /* hash + 33 + c */
    }

    return hash % M;
}

//them tu vao dict
void addData(DictNode *heads[], Vocab w){
    int h = hashFunct(w.english);
    DictNode *r = heads[h];
    DictNode *new_word = createNode(w);

    if(r == NULL){
        //them vao dau (lan dau tien)
        heads[h] = new_word;
    }else{
        while(r->next != NULL){
            if(strcmp(r->word.english, w.english) == 0){	//neu trung thi khong them
                break;
            }else{
                r = r->next;
            }
        }

        if(strcmp(r->word.english, w.english) != 0){
            r->next = new_word;
        }
        
    }
}

void readDict(DictNode *heads[]){
    FILE *f = fopen("dict.txt", "a+");

    while(!feof(f)){
        
        Vocab w;
        fgets(w.english, 255, f);
        fgets(w.type, 255, f);
        fgets(w.meaning, 255, f);

        addData(heads, w);
    }
    fclose(f);
}

/*MENU 1*/
void viewDict(DictNode *heads[]){

    char temp1[256], temp2[256], temp3[256];
    int len1, len2, len3;
    int num_of_vocab = 0;

    printf("WORD\t\tTYPE\t\tMEANING\n");

    for(int i = 0; i < M; i++){
        if(heads[i] != NULL){

            DictNode *new_word = heads[i]; 

            while(new_word != NULL){
                
                strcpy(temp1, new_word->word.english);
                strcpy(temp2, new_word->word.type);
                strcpy(temp3, new_word->word.meaning);

                len1 = strlen(temp1);
                len2 = strlen(temp2);
                len3 = strlen(temp3);

                temp1[len1 - 1] = '\0';
                temp2[len2 - 1] = '\0';
                temp3[len3 - 1] = '\0';

                printf("%s\t\t%s\t\t%s\n", temp1, temp2, temp3);

                new_word = new_word->next;
                num_of_vocab++;
            }
        }
    }

    printf("\nThere are %d vacabularies in this dictionary.\n", num_of_vocab);
}

/*MENU 3*/
void toLower(char str[]){
    for(int i = 0; i < strlen(str); i++){
        str[i] = tolower(str[i]);
    }
}

void searchWord(DictNode *heads[]){

    char eng[256];
    printf("Enter the word you want to search: ");
    fgets(eng, 255, stdin);
    printf("\nIntput word: %s", eng);
    toLower(eng);

    char temp1[256], temp2[256], temp3[256];
    int len1, len2, len3;

    int h = hashFunct(eng);

    DictNode *r = heads[h];

    //neu r == NULL => tai do khong co tu nao het
    while(r != NULL){
        if(strcmp(r->word.english, eng) == 0){
                    
            strcpy(temp1, r->word.english);
            strcpy(temp2, r->word.type);
            strcpy(temp3, r->word.meaning);

            len1 = strlen(temp1);
            len2 = strlen(temp2);
            len3 = strlen(temp3);
            temp1[len1 - 1] = '\0';
            temp2[len2 - 1] = '\0';
            temp3[len3 - 1] = '\0';

            printf("\nWORD\t\tTYPE\t\tMEANING\n");
            printf("%s\t\t%s\t\t%s\n", temp1, temp2, temp3);

            return;
            }
        r = r->next;
    }

    printf("\nOh no! This word is not in the dictionary!\n");
}

/*MENU 2*/
void addWord(DictNode *heads[]){
    FILE *f = fopen("dict.txt", "a+");

    Vocab w;

    printf("Enter the English word you want to add: ");
    fgets(w.english, 255, stdin);
    toLower(w.english);

    //kiem tra da co trong tu dien chua
    int h = hashFunct(w.english);
    DictNode *r = heads[h];
    //neu r == NULL => tai do khong co tu nao het
    while(r != NULL){
        if(strcmp(r->word.english, w.english) == 0){
            printf("\nOhh no! This word has been in the dictionary!\n");
            return;
            }
        r = r->next;
    }
    
    printf("Enter its type: ");
    fgets(w.type, 255, stdin);
    toLower(w.type);
    printf("Enter its meaning: ");
    fgets(w.meaning, 255, stdin);
    toLower(w.meaning);

    fprintf(f, "%s%s%s", w.english, w.type, w.meaning);

    addData(heads, w);

    printf("\nSuccess!\n");

    fclose(f);
}