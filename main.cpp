#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#include "title.h"
#include "menu.h"
#include "funct.h"


int main(){
	// SHOW TITLE (NAME ...)
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

MENU:
	system("cls");
	user_choice = menu();

	switch (user_choice){
	case 1:{
	VIEW:
		system("cls");

		printf("------------- VIEW DICTIONARY -------------\n\n");

		fflush(stdin);	//tranh dau cach nhung lan nhap lai
		viewDict(Dict);

		is_continue = toContinue();

		if (is_continue == 1){
			goto VIEW;
		}
		else if (is_continue == 2){
			goto MENU;
		}

		break;
	}

	case 2:{
	GAME:
		system("cls");

		printf("------------- PLAY GAME -------------\n\n");

		//demo
		printf("hello");
		int i;
		scanf("%d", &i);
		getchar();
		printf("%d", i);
		//demo

		is_continue = toContinue();
		if (is_continue == 1){
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
		if (is_continue == 1){
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
		if (is_continue == 1){
			goto ADD;
		}
		else if (is_continue == 2){
			goto MENU;
		}

		break;
	}

	case 5:{
	EDIT:
		system("cls");

		printf("------------- EDIT WORD -------------\n\n");

		fflush(stdin);
		//demo
		printf("hello");
		int i;
		scanf("%d", &i);
		getchar();
		printf("%d", i);
		//demo

		is_continue = toContinue();
		if (is_continue == 1){
			goto EDIT;
		}
		else if (is_continue == 2){
			goto MENU;
		}

		break;
	}

	case 6:{
	DELETE:
		system("cls");

		printf("------------- DELETE WORD -------------\n\n");

		fflush(stdin);
		//demo
		printf("hello");
		int i;
		scanf("%d", &i);
		getchar();
		printf("%d", i);
		//demo

		is_continue = toContinue();
		if (is_continue == 1){
			goto VIEW;
		}
		else if (is_continue == 2){
			goto DELETE;
		}

		break;
	}
	default:
		break;
	}

	printf("\nGOODBYE AND SEE YOU AGAIN!!");
	return 0;
}
