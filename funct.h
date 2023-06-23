#define M 2003	//kich thuoc hashtable

typedef struct Vocab Vocab;
typedef struct DictNode DictNode;

void addData(DictNode *heads[], Vocab w);
void addWord(DictNode *heads[]);
DictNode* createNode(Vocab w);
int deleteData(DictNode *heads[], char eng[]);
void deleteWord(DictNode *heads[]);
void display(DictNode *r);
void editWord(DictNode *heads[]);
int findData(DictNode *heads[], char eng[], DictNode *&r);
int hashFunct(char *str);
int index(DictNode *heads[], int not_nulll);
void init(DictNode *heads[]);
void playGame(DictNode *heads[], int not_null[], int number_of_not_null);
int random(int lenght);
void readDict(DictNode *heads[]);
int replace(char eng[]);
void searchWord(DictNode *heads[]);
void tolower(char eng[]);
void updateDict(DictNode *heads[]);
void viewDict(DictNode *heads[]);

//cau truc cua 1 tu vung
struct Vocab{
    char english[256];
    char type[256];
    char meaning[256];
};

//cau truc cua 1 node 
struct DictNode{
    Vocab word;
    DictNode *next;
};

//khoi tao hashtable
void init(DictNode *heads[]){
    for(int i = 0; i < M; i++){
        heads[i] = NULL;
    }
} 

//khoi tao node moi
DictNode* createNode(Vocab w){
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

//doc tu vao tu dien tu file dict.txt
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

//update file sau moi lan chay chuong trinh
void updateDict(DictNode *heads[]){
    //tao file temp.txt de luu tru du lieu
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

//hien thi 1 tu
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

//viet thuong chuoi eng
void toLower(char eng[]){
    for(int i = 0; i < strlen(eng); i++){
        eng[i] = tolower(eng[i]);
    }
}

//tim xem co eng trong tu dien khong
int findData(DictNode *heads[], char eng[], DictNode *&r){
    int h = hashFunct(eng);
    r = heads[h];
    
    //neu r == NULL => khong co tu nao tai do
    while(r != NULL){
        if(strcmp(r->word.english, eng) == 0){  
            return 0;   //tim duoc
        }
        r = r->next;
    }
    return 1;
}

//xoa eng khoi tu dien
int deleteData(DictNode *heads[], char eng[]){
    int h = hashFunct(eng);

    DictNode *r = heads[h]; //node k muon xoa
    DictNode *prev = NULL;  //node k - 1

    //neu r == NULL => khong co tu nao tai do
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

/*MENU 1*/
void viewDict(DictNode *heads[]){
    printf("WORD\t\tTYPE\t\tMEANING\n");

    int num_of_vocab = 0;
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

/*MENU 2*/
//chon 1 so ngau nhien be hon eng
int random(int lenght){
	time_t t;   //bien t la kieu du lieu thoi gian
	srand((unsigned)time(&t));  //khoi tao bo sinh so ngau nhien cho ham random
	return rand() % (lenght - 1);   //chon 1 so bat ki be hon do dai eng
}

//chon 1 ki tu bat ki trong eng thay bang dau * 
int replace(char eng[]){ 
	int lenght, random_pos;
	lenght = strlen(eng);
	random_pos = random(lenght); //chon bat ki 1 vi tri so trong eng
	eng[random_pos] = '*';
	return random_pos; //tra ve vi tri thay dau *
}

//tra ve mang not_null chia cac vi trí i sao cho heads[i] != NULL
int index(DictNode *heads[], int not_null[]) {
	int i;
	int j = 0;
	for (i = 0; i < M; i++){
		if (heads[i] == NULL)
			continue;
		else{
			not_null[j] = i;
			j++;
		}
	}
	return j;
}

void playGame(DictNode *heads[], int not_null[], int number_of_not_null){
	char missing_char;
	char temp[256], eng[256];
	int position;
	int address = 0;
	int point = 0;

	do{
		system("cls");
		printf("------------- PLAY GAME -------------\n\n");
		printf("Your point: %d", point);
		
		address = not_null[random(number_of_not_null + 1)];
		strcpy(eng, heads[address]->word.english);
		strcpy(temp, heads[address]->word.english);

		position = replace(temp);
		printf("\n\nFind the word: %s", temp);
		printf("\nEnter the missing character: ");
		fflush(stdin);
		missing_char = getchar();
		temp[position] = tolower(missing_char);
		printf("\nYour answer: %s", temp);

		if (strcmp(temp, eng) == 0) {
			printf("\nGreat! That is the correct answer!\n");
            printf("\nWORD\t\tTYPE\t\tMEANING\n");
            display(heads[hashFunct(eng)]); 
			printf("\n");
			point++;
			system("pause");
			continue;
		}

        DictNode *r = NULL;
		if (findData(heads, temp, r) == 0) {
			printf("\nNice! That is correct!\n");
			printf("\nWORD\t\tTYPE\t\tMEANING\n");
			display(r);
			printf("\n");
			point++;
			system("pause");
			continue;
		}

		break;
	}while(1);

	printf("\nOh no, that is the wrong answer!");
	printf("\n\nThe answer must be: %s", eng);
    printf("\nWORD\t\tTYPE\t\tMEANING\n");
    display(heads[hashFunct(eng)]);
	printf("\nYou have got %d points!\n", point);
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

    DictNode *r = NULL;
    if(findData(heads, w.english, r) == 0){
        printf("\nOh no! This word has been in the dictionary!\n");
        return;
    }else{
        printf("Enter its type: ");
        fgets(w.type, 255, stdin);
        toLower(w.type);
        printf("Enter its meaning: ");
        fgets(w.meaning, 255, stdin);
        toLower(w.meaning);

        addData(heads, w);
        printf("\nSuccessfully added!\n");
    }
}

/*MENU 5*/
void editWord(DictNode *heads[]){
    Vocab w;    //luu tu moi

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

        //xoa tu cu ra khoi tu dien
        deleteData(heads, eng);

        //sua
        char choice;
        printf("\nPress:\n");
        printf("1. To edit word.\n2. To edit type.\n3. To edit meaning.\nAny key to exit.\n");
        printf("Your choice: ");
        scanf("%c", &choice);
        getchar();

        switch(choice){
            case '1':{
                printf("\nEnter new English word: ");
                fgets(w.english, 255, stdin);
                toLower(w.english);
                printf("\nSuccessfully edited!\n");
                break;
            }
            case '2':{
                printf("\nEnter new type: ");
                fgets(w.type, 255, stdin);
                toLower(w.type);
                printf("\nSuccessfully edited!\n");
                break;
            }
            case '3':{
                printf("\nEnter new meaning: ");
                fgets(w.meaning, 255, stdin);
                toLower(w.meaning);
                printf("\nSuccessfully edited!\n");
                break;
            }
            default:{
                break;
            }
        }

        //them tu moi sua vao tu dien
        addData(heads, w);
        return;
    }else{
        printf("\nOh no! This word is not in the dictionary!\n");
    }
}

/*MENU 6*/
void deleteWord(DictNode *heads[]){
    char eng[256];
    printf("Enter the word you want to delete: ");
    fgets(eng, 255, stdin);
    toLower(eng);
    printf("\nIntput word: %s", eng);

    if(deleteData(heads, eng) == 0){
        printf("\nSuccessfully deleted!\n");
        return;
    }else{
        printf("\nOh no! This word is not in the dictionary!\n");
    }
}
