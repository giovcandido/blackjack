#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define MAX_GAMBLERS 7
#define MAX_TIME 2000

void displayMenu();
void startGame();
void displayRules();

void callGambler(int points, int sum, char card, int i, int score[]);
void callDealer(int points, int sum, char card, int i, int score[]); 

void saveScore(int sum, int i, int score[]);
void displayScore(int score[], int gamblers);

void dealCard(char *card, int *points, int *sum);
void chooseCardSuit(char *suit);

void clearScreen();

int main(){
	srand(time(NULL));
	
	displayMenu();
	
	return 0;
}

void displayMenu(){
	char option, answer;
	int valid;
	
	clearScreen();
			
	printf("# Blackjack # \n\n");
	
	printf("1) Start\n");
	printf("2) Rules\n");
	printf("3) Exit\n\n");
	
	do{
		valid = 1;
		
		option = getch();
		
		if(option != '1' && option != '2' && option != '3')
			valid = 0;
	}while(!valid);
	
	switch(option){
		case '1':
			startGame();
			Sleep(MAX_TIME);
			
			printf("\nPRESS ENTER TO RETURN TO THE MENU");
	
			do{
				answer = getch();
			}while(answer != 13);
	
			displayMenu();
			break;
		case '2':
			displayRules();
			break;
		case '3':
			exit(0);
	}	
}

void startGame(){
	int points, sum, gamblers, i, score[MAX_GAMBLERS+1];
	char option, card;
	
	clearScreen();

	do{
		printf("Enter the total number of gamblers to join the table (max. %d): ", MAX_GAMBLERS);
		scanf("%d", &gamblers);
		fflush(stdin);
		
		clearScreen();
	}while(gamblers < 1 || gamblers > MAX_GAMBLERS);
	
	for(i = 0; i < gamblers; i++){
		sum = 0;
		callGambler(points, sum, card, i, score);
	}

	sum = 0;
	callDealer(points, sum, card, i, score);
	
	displayScore(score, gamblers);
}

void displayRules(){
	int answer;
	
	clearScreen();
	
	printf("* The cards have the same number of points as their values (indepedent of the suit).\n");
	printf("* A (ace) has value 1, on the other hand, K (king), Q (queen) and J (jack) have value 10.\n");
	printf("* Each GAMBLER (user), as well as the DEALER (software), begin with two cards.\n");
	printf("* There is a 'Hit or Stand' option for every additional card.\n");
	printf("* If you hit, you get one more card and it goes on until: you stop (stand), lose (bust) or win (blackjack).\n");
	printf("* The goal is to get the maximum score in the table, with the upper limite of 21, 22+ points and you bust.\n");
	printf("* At the end, the player with maximum score wins, however a tie can also occur.\n");
	
	printf("\nPRESS ENTER TO RETURN TO THE MENU");
	
	do{
		answer = getch();
	}while(answer != 13);
	
	displayMenu();
}

void callGambler(int points, int sum, char card, int i, int score[]){
	char answer;
	
	printf("GAMBLER %d\n\n", i+1);
	Sleep(1000);
	
	dealCard(&card, &points, &sum);	
	Sleep(MAX_TIME);
	
	while(sum < 21){
		dealCard(&card, &points, &sum);		
		Sleep(MAX_TIME);
		
		if(sum >= 21){
			if(sum > 21)
				printf("You have busted...");
			else
				printf("BLACKJACK!");
				
			Sleep(MAX_TIME);
			clearScreen();
			break;
		}
		
		printf("Hit or Stand? H/S");
		
		do{
			answer = toupper(getch());
		}while(answer != 'H' && answer != 'S');
		
		if(answer == 'S'){
			printf("\n\nYou have stood...");
			Sleep(MAX_TIME);
			clearScreen();
			break;
		}
		
		printf("\n\n");
	}
	
	saveScore(sum, i, score);
}

void callDealer(int points, int sum, char card, int i, int score[]){	
	printf("There you go, DEALER! The house can still win.\n\n");
	Sleep(1000);
	
	dealCard(&card, &points, &sum);
	Sleep(MAX_TIME);
	
	dealCard(&card, &points, &sum);
	Sleep(MAX_TIME);
	
	while(sum < 17){
		printf("They have hit!\n\n");
		Sleep(MAX_TIME);
		
		dealCard(&card, &points, &sum);
		Sleep(MAX_TIME);	
	}	
	
	if(sum >= 21){
		if(sum > 21)
			printf("DEALER have busted...");
		else
			printf("BLACKJACK!");
	}
	else{
		printf("DEALER have stood...");	
	}
	
	Sleep(MAX_TIME);
	saveScore(sum, i, score);
}

void saveScore(int sum, int i, int score[]){
	score[i] = sum;
}

void displayScore(int score[], int gamblers){	
	int i;
		
	clearScreen();
	
	printf("# Final score #\n\n");
		
	for(i = 0; i < gamblers; i++){
		if(score[i] > 21)
			printf("GAMBLER %d: %d points BUSTED\n", i+1, score[i]);
		else if(score[i] == 21)
			printf("GAMBLER %d: %d points BLACKJACK\n", i+1, score[i]);
		else 
			printf("GAMBLER %d: %d points\n", i+1, score[i]);
	}
	
	if(score[i] > 21)
		printf("DEALER   : %d points BUSTED\n\n", score[i]);	
	else if(score[i] == 21)
		printf("DEALER   : %d points BLACKJACK\n\n", score[i]);
	else 
		printf("DEALER   : %d points\n\n", score[i]);
}

void dealCard(char *card, int *points, int *sum){
	char cards[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K'}, suit[8];
	int aux;
	
	aux = rand()%13;
	
	*card = cards[aux];
	
	if(aux == 0){
		*points = 1;
	}
	else
		if(aux >= 9){
			*points = 10;
		}
		else{
			*points = aux+1;
		}
	
	*sum += *points;
	
	chooseCardSuit(suit);
	
	if(*card == '0')
		printf("10 of %s\n", suit);
	else
		printf("%c of %s\n", *card, suit);
		
	printf("Accumulated score: %i points\n\n", *sum);
}

void chooseCardSuit(char suit[]){
	char suits[] = {'d', 's', 'h', 'c'};
	int aux;
	
	aux = rand()%4;
	
	switch(suits[aux]){
		case 'd':
			strcpy(suit, "Diamonds");
			break;
		case 's':
			strcpy(suit, "Spades");
			break;
		case 'h':
			strcpy(suit, "Hearts");
			break;
		case 'c':
			strcpy(suit, "Clubs");
	}
}

void clearScreen(){
	system("cls");	
}
