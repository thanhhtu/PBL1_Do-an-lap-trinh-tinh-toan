#define Ngang 205
#define Doc 179
#define Goc_Tren_Trai 213
#define Goc_Duoi_Trai 212
#define Goc_Tren_Phai 184
#define Goc_Duoi_Phai 190

int menu(){
	float choice;
	
	do{
		printf("\t%c", Goc_Tren_Trai);
		for (int i = 0; i <= 40; i++) {
			printf("%c", Ngang);
		}
		printf("%c\t\n", Goc_Tren_Phai);
		
		printf("\t%c                                         %c\n", Doc, Doc);
		printf("\t%c           VOCABULARY PROGRAM            %c\n", Doc, Doc);
		printf("\t%c                                         %c\n", Doc, Doc);
		printf("\t%c  1. View dictionary.                    %c\n", Doc, Doc);
		printf("\t%c  2. Play game.                          %c\n", Doc, Doc);
		printf("\t%c  3. Search word.                        %c\n", Doc, Doc);
		printf("\t%c  4. Add word.                           %c\n", Doc, Doc);
		printf("\t%c  5. Edit word.                          %c\n", Doc, Doc);	
		printf("\t%c  6. Delete word.                        %c\n", Doc, Doc);	
		printf("\t%c  7. End program.                        %c\n", Doc, Doc);
		
		printf("\t%c                                         %c\n", Doc, Doc);
		printf("\t%c", Goc_Duoi_Trai);
		for (int i = 0; i <= 40; i++) {
			printf("%c", Ngang);
		}
		printf("%c", Goc_Duoi_Phai);
		printf("\n");
		
		printf("\nYour choice: ");
		scanf("%f", &choice);
		getchar();	//LAY DAU CACH
		if(!(choice == (int)choice && choice >= 1 && choice <= 7)){
			printf("Invalid input!! Please choose again.\n\n");
		}
		
	}while(!(choice == (int)choice && choice >= 1 && choice <= 7));
	
	return (int)choice;
}

int toContinue(){
	char choice;
	printf("\nPress c to continue.\nPress b to back to menu.\nPress any key to exit the program.\n");
	printf("Your choice: ");

//	scanf("\n");	//thay vi dung fflush(stdin) de xoa dau cach nhung lan nhap lai tiep theo
	scanf("%c", &choice);
	if(choice == 'c' || choice == 'C'){
		return 1;
	}else if(choice == 'b' || choice == 'B'){
		return 2;
	}else{
		return 0;
	}
}
