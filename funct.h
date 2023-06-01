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

//khoi tao node moi
DictNode * createNode(Vocab w){
    DictNode *new_word = (DictNode *)malloc(sizeof(DictNode));
    new_word->word = w;
    new_word->next = NULL;
    return new_word;
}

//hash funct djb2
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

//hien thi
void display(DictNode *r){
    char temp1[256], temp2[256], temp3[256];
    int len1, len2, len3;
    strcpy(temp1, r->word.english);
    strcpy(temp2, r->word.type);
    strcpy(temp3, r->word.meaning);

    len1 = strlen(temp1);
    len2 = strlen(temp2);
    len3 = strlen(temp3);

    temp1[len1 - 1] = '\0';
    temp2[len2 - 1] = '\0';
    temp3[len3 - 1] = '\0';

    printf("%s\t\t%s\t\t%s\n", temp1, temp2, temp3);
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
            
                display(new_word);

                new_word = new_word->next;
                num_of_vocab++;
            }
        }
    }

    printf("\nThere are %d vacabularies in this dictionary.\n", num_of_vocab);
}

//lower
void toLower(char str[]){
    for(int i = 0; i < strlen(str); i++){
        str[i] = tolower(str[i]);
    }
}

//find data
int findData(DictNode *heads[], char eng[], DictNode *&r){
    int h = hashFunct(eng);
    r = heads[h];
    
    //neu r == NULL => tai do khong co tu nao het
    while(r != NULL){
        if(strcmp(r->word.english, eng) == 0){  
            return 0;   //tim duoc
        }
        r = r->next;
    }
    return 1;
}

/*MENU 3*/
void searchWord(DictNode *heads[]){
    char eng[256];
    printf("Enter the word you want to search: ");
    fgets(eng, 255, stdin);
    toLower(eng);
    printf("\nIntput word: %s", eng);

    DictNode *r = NULL;
    if(findData(heads, eng, r) == 0){
       
        printf("\nWORD\t\tTYPE\t\tMEANING\n");
        display(r);

        return;
    }else{
        printf("\nOh no! This word is not in the dictionary!\n");
    }
}

/*MENU 4*/
void addWord(DictNode *heads[]){
    Vocab w;
    printf("Enter the English word you want to add: ");
    fgets(w.english, 255, stdin);
    toLower(w.english);

    //kiem tra da co trong tu dien chua
    DictNode *r = NULL;
    if(findData(heads, w.english, r) == 0){
        printf("\nOhh no! This word has been in the dictionary!\n");
        return;
    }else{
        printf("Enter its type: ");
        fgets(w.type, 255, stdin);
        toLower(w.type);
        printf("Enter its meaning: ");
        fgets(w.meaning, 255, stdin);
        toLower(w.meaning);

        addData(heads, w);

        printf("\nAdd successfully!\n");
    }
}

//delete data
int deleteData(DictNode *heads[], char eng[]){
    int h = hashFunct(eng);

    DictNode *r = heads[h]; //node k muon xoa
    DictNode *prev = NULL;  //node k - 1

    //neu r == NULL => tai do khong co tu nao het
    while(r != NULL){
        if(strcmp(r->word.english, eng) == 0){
            if(prev == NULL){
                heads[h] = r->next;
            }else{
                prev->next = r->next;
            }
            free(r);
            return 0;
        }
        prev = r;
        r = r->next;
    }

    return 1;
    
}

/*MENU 6*/
void deleteWord(DictNode *heads[]){
    char eng[256];
    printf("Enter the word you want to delete: ");
    fgets(eng, 255, stdin);
    toLower(eng);
    printf("\nIntput word: %s", eng);

    char temp1[256], temp2[256], temp3[256];
    int len1, len2, len3;

    if(deleteData(heads, eng) == 0){
        printf("\nDelete successfully!\n");
        return;
    }else{
        printf("\nOh no! This word is not in the dictionary!\n");
    }
}

//update dict sau moi lan chay chuong trinh
void updateDict(DictNode *heads[]){

    //tao 1 file moi de luu tru du lieu
    FILE *f = fopen("temp.txt", "w");

    for(int i = 0; i < M; i++){
        DictNode *r = heads[i];

        while(r != NULL){
            fprintf(f, "%s%s%s", r->word.english, r->word.type, r->word.meaning);
            r = r->next;
        }
    }
    
    fclose(f);

    //xoa file dict.txt cu
    remove("dict.txt");

    //doi ten file temp.txt moi thanh dict.txt
    rename("temp.txt", "dict.txt");

}

/*MENU 5*/
void editWord(DictNode *heads[]){
    Vocab w;    //de luu tu moi

    char eng[256];
    printf("Enter the word you want to edit: ");
    fgets(eng, 255, stdin);
    toLower(eng);

    DictNode *r = NULL;
    if(findData(heads, eng, r) == 0){
        //hien thi tu muon sua
        printf("\nWORD\t\tTYPE\t\tMEANING\n");
        display(r);

        //sao chep tu muon sua
        strcpy(w.english, r->word.english);
        strcpy(w.type, r->word.type);
        strcpy(w.meaning, r->word.meaning);

        //sua
        int choice;
        printf("\nPress:\n");
        printf("1. To edit word.\n2. To edit type.\n3. To edit type.\nAny key to exit.\n");

        printf("Your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice){
            case 1:{
                printf("\nEnter new English word: ");
                fgets(w.english, 255, stdin);
                toLower(w.english);

                printf("\nEdit successfully!\n");
                break;
            }
            case 2:{
                printf("\nEnter new type: ");
                fgets(w.type, 255, stdin);
                toLower(w.type);

                printf("\nEdit successfully!\n");
                break;
            }
            case 3:{
                printf("\nEnter new meaning: ");
                fgets(w.meaning, 255, stdin);
                toLower(w.meaning);

                printf("\nEdit successfully!\n");
                break;
            }
            default:{
                fflush(stdin);
                break;
            }
        }

        //xoa tu cu ra khoi tu dien
        deleteData(heads, w.english);
        //them tu moi sua vao tu dien
        addData(heads, w);

        return;
    }else{
        printf("\nOh no! This word is not in the dictionary!\n");
    }

}