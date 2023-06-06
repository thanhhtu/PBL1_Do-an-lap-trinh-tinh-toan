#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

#include "title.h"
#include "menu.h"
#include "funct.h"


int main(){
	title();
	getch();
	while (true){
		break;
	}

	// START PROGRAM
	DictNode *Dict[M];
	init(Dict);
	readDict(Dict);

	int user_choice;
	int is_continue;
	int not_null[M];
	int number_of_not_null = index(Dict, not_null);

MENU:
	system("cls");
	user_choice = menu();

	switch(user_choice){
		case 1:{
		VIEW:
			system("cls");
			printf("------------- VIEW DICTIONARY -------------\n\n");

			fflush(stdin);	//tranh dau cach nhung lan nhap lai
			viewDict(Dict);

			is_continue = toContinue();
			if(is_continue == 1){
				goto VIEW;
			}
			else if(is_continue == 2){
				goto MENU;
			}
			break;
		}

		case 2:{
		GAME:
			system("cls");
	
	 		playGame(Dict, not_null, number_of_not_null);
	 		
	 		fflush(stdin);
			is_continue = toContinue();
			if(is_continue == 1){
				goto GAME;
			}
			else if (is_continue == 2){
				goto MENU;
			}
			break;
		}

		case 3:{
		SEARCH:
			system("cls");
			printf("------------- SEARCH WORD -------------\n\n");

			fflush(stdin);
			searchWord(Dict);

			is_continue = toContinue();
			if(is_continue == 1){
				goto SEARCH;
			}
			else if (is_continue == 2){
				goto MENU;
			}
			break;
		}

		case 4:{
		ADD:
			system("cls");
			printf("------------- ADD WORD -------------\n\n");

			fflush(stdin);
			addWord(Dict);

			is_continue = toContinue();
			if(is_continue == 1){
				goto ADD;
			}
			else if(is_continue == 2){
				goto MENU;
			}
			break;
		}

		case 5:{
		EDIT:
			system("cls");
			printf("------------- EDIT WORD -------------\n\n");

			fflush(stdin);
			editWord(Dict);

			is_continue = toContinue();
			if(is_continue == 1){
				goto EDIT;
			}
			else if(is_continue == 2){
				goto MENU;
			}
			break;
		}

		case 6:{
		DELETE:
			system("cls");
			printf("------------- DELETE WORD -------------\n\n");

			fflush(stdin);
			deleteWord(Dict);

			is_continue = toContinue();
			if(is_continue == 1){
				goto DELETE;
			}
			else if(is_continue == 2){
				goto MENU;
			}
			break;
		}
		default:{
			break;
		}
	}

	updateDict(Dict);
	printf("\nGOODBYE AND SEE YOU AGAIN!!");
	return 0;
}