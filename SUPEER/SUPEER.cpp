// SUPEER.cpp : Defines the entry point for the console application.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

unsigned char cardsLeft = 52;

struct cardNode {
	cardNode *next;
	unsigned char value = 0;
	unsigned char* cardsLeft = NULL;
};

unsigned char cardValue[] = {
	2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
};

cardNode* generateCardDeck();
unsigned char takeRandomCard(cardNode *card);

unsigned char getCardGameValue(unsigned char value);
void destroyCardDeck(cardNode* cardDeck);

void printPlayerLose(unsigned char playerDeck, unsigned char dividersDeck);
void printPlayerWin(unsigned char playerDeck, unsigned char dividersDeck);
void printGameState(unsigned char playerDeck, unsigned char dividersDeck);


int main()
{	
	srand(time(NULL));
	char c;
	while (1) {
		cardNode *cardDeck = generateCardDeck();
		unsigned char playerDeck = 0;
		unsigned char dividersDeck = 0;

		playerDeck = getCardGameValue(takeRandomCard(cardDeck));
		dividersDeck = getCardGameValue(takeRandomCard(cardDeck));
		printGameState(playerDeck, dividersDeck);

		for (;;) {
			if (kbhit()) {
				c = getch();
				if (c == 'h') {
					playerDeck += getCardGameValue(takeRandomCard(cardDeck));
					if (playerDeck > 21) {
						printPlayerLose(playerDeck, dividersDeck);
						break;
					}
					printGameState(playerDeck, dividersDeck);
				}
				else if (c == 's') {
					while (dividersDeck < 17) dividersDeck += getCardGameValue(takeRandomCard(cardDeck));
					if (dividersDeck > 21) {
						printPlayerWin(playerDeck, dividersDeck);
					}
					else if (21 - dividersDeck < 21 - playerDeck) {
						printPlayerLose(playerDeck, dividersDeck);
					}
					else {
						printPlayerWin(playerDeck, dividersDeck);
					}
					break;
				}
			}
		}
	}

	system("pause");
    return 0;
}

void printPlayerLose(unsigned char playerDeck, unsigned char dividersDeck) {
	printf("---------------------\n");
	printf("Pelaajan hävisi pakkalla: %d\n", playerDeck);
	printf("Jakajan voitti pakkalla: %d\n", dividersDeck);
	printf("---------------------\n");
}

void printPlayerWin(unsigned char playerDeck, unsigned char dividersDeck) {
	printf("---------------------\n");
	printf("Pelaajan voitti pakkalla: %d\n", playerDeck);
	printf("Jakajan hävisi pakkalla: %d\n", dividersDeck);
	printf("---------------------\n");
}

void printGameState(unsigned char playerDeck, unsigned char dividersDeck) {
	printf("---------------------\n");
	printf("Pelaajan pakka: %d\n", playerDeck);
	printf("Jakajan pakka: %d\n", dividersDeck);
	printf("---------------------\n");
}

cardNode* generateCardDeck() {
	cardNode *firstCard = (cardNode*)malloc(sizeof(cardNode));
	cardNode *currentCard = firstCard;
	unsigned char* cardsLeft = (unsigned char*)malloc(sizeof(unsigned char));
	*cardsLeft = 52;
	for (int i = 0; i < 52; i++) {
		currentCard->value = cardValue[i];
		currentCard->next = (cardNode*)malloc(sizeof(cardNode));
		currentCard->cardsLeft = cardsLeft;
		currentCard = currentCard->next;
	}
	return firstCard;
}

void destroyCardDeck(cardNode* cardDeck) {

}

unsigned char takeRandomCard(cardNode* cardDeck) {
	unsigned char number = rand() % *cardDeck->cardsLeft + 1;
	if (number == 1) {
		cardNode * next = cardDeck->next;
		char value = cardDeck->value;
		cardDeck->value = cardDeck->next->value;
		cardDeck->next = next->next;	
		free(next);
		*cardDeck->cardsLeft = *cardDeck->cardsLeft - 1;
		return value;
	} else {
		cardNode* currentCard = cardDeck;
		for (int i = 0; i < number - 1; i++) currentCard = currentCard->next;
		cardNode *toBeReturned = currentCard->next;
		if (number < cardsLeft) {
			currentCard->next = toBeReturned->next;
		}
		char value = toBeReturned->value;
		free(toBeReturned);
		*cardDeck->cardsLeft = *cardDeck->cardsLeft -1;
		return value;
	}
}

unsigned char getCardGameValue(unsigned char value) {
	if (value > 1 && value < 10) return value;
	else if (value > 9 && value < 14) return 10;
	else return 1;
}