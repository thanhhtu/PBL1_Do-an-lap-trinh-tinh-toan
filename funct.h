//tat ca cac chuoi deu chuyen sang in thuong

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
void addWord(DictNode *heads[], Vocab w){
    int hash = hashFunct(w.english);
    DictNode *r = heads[hash];
    DictNode *new_word = createNode(w);

    if(r == NULL){
        //them vao dau (lan dau tien)
        heads[hash] = new_word;
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

/* MENU 1 */
//doc tu from dict to hash table
void readDict(DictNode *heads[]){
    FILE *f = fopen("dict.txt", "a+");

    while(!feof(f)){
        
        Vocab w;
        fgets(w.english, 255, f);
        fgets(w.type, 255, f);
        fgets(w.meaning, 255, f);

        addWord(heads, w);
    }
    fclose(f);
}

//in ra man hinh
void viewDict(DictNode *heads[]){
    readDict(heads);

    char temp1[256], temp2[256], temp3[256];

    int len1, len2, len3;

    int num_of_vocab = 0;

    printf("------------- VIEW DICTIONARY -------------\n\n");
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
