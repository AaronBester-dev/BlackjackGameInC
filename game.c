#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "blackjack.h"

void printUI(struct Hand * playerHand, struct Hand * enemyHand){
    system("clear");
    printf("Player Score:%d                                 Enemy Score:%d\n",playerHand->gamePoints,enemyHand->gamePoints);
    printf("Current Player Hand Score:%d                   Current Enemy Hand Score:%d\n",playerHand->pointValueOfAllCards,enemyHand->pointValueOfAllCards);
    printf("Player Hand:                                   Enemy Hand:\n");
    printDeck(playerHand->headOfHand);
    printf("                                      ");
    printDeck(enemyHand->headOfHand);
    printf("\n");
}

void calculateHandScore(struct Hand * hand){
    struct Card * node = hand->headOfHand;
    hand->pointValueOfAllCards = 0;
    while(node != NULL){
        hand->pointValueOfAllCards += node->value;
        node = node->nextCard;
    }
}

int continueOrNot(){
    char playerAnswer;
    int returnNumber = -1;
    printf("Do you want to keep playing?\nY(Yes) or N(No)\n");
    while(returnNumber == -1){
        playerAnswer = getchar();
        playerAnswer = tolower(playerAnswer);
        if(playerAnswer == 'y'){
            returnNumber = 1;
        }else if(playerAnswer == 'n'){
            returnNumber = 0;
        }else{
            returnNumber = -1;
        }
    }
    return returnNumber;
}

int playerTurn(struct Card ** deckHead,struct Hand * playerHand, struct Hand * enemyHand){
    int playerAnswer = 1;
    int bust = 0;
    int blackjack = 0;

    while(playerAnswer == 1 && bust == 0 && blackjack == 0){
        calculateHandScore(playerHand);
        
        if(playerAnswer == 1){
            *deckHead = deal(*deckHead,playerHand);
            calculateHandScore(playerHand);
            bust = didIBust(playerHand);
            blackjack = didIBlackJack(playerHand);
            printUI(playerHand, enemyHand);
        }
        printf("Hit?\nY(Yes) or N(No)\n");
        playerAnswer = yesOrNo();
    }

    if(bust == 1){
        return 1;
    }
    else if(blackjack == 1){
        return 2;
    } else{
        return 0;
    }
}

int enemyTurn(struct Card ** deckHead, struct Hand * enemyHand, struct Hand * playerHand, int difficulty){
    int enemyAnswer = 1;
    int bust = 0;
    int blackjack = 0;
    
    while(enemyAnswer == 1 && bust == 0 && blackjack == 0){
        calculateHandScore(enemyHand);
        if(enemyAnswer == 1){
            *deckHead = deal(*deckHead,enemyHand);
            calculateHandScore(enemyHand);
            bust = didIBust(enemyHand);
            blackjack = didIBlackJack(enemyHand);
            printUI(playerHand, enemyHand);
        }
        if(difficulty == 1){
            enemyAnswer = easyEnemyYesOrNo(enemyHand);
        } else if(difficulty == 0){
            enemyAnswer = hardEnemyYesOrNo(enemyHand, *deckHead);
        }
        
    }

    if(bust == 1){
        return 1;
    }
    else if(blackjack == 1){
        return 2;
    } else{
        return 0;
    }
}

int easyEnemyYesOrNo(struct Hand * enemyHand){
    if(enemyHand->pointValueOfAllCards > 16){
        return 0;
    } else{
        return 1;
    }
}

int hardEnemyYesOrNo(struct Hand * enemyHand, struct Card * deckHead){
    if(deckHead->value + enemyHand->pointValueOfAllCards > 21){
        return 0;
    } else{
        return 1;
    }
}

void returnCardsBackToDeck(struct Card * deckHead, struct Hand * playerHand){
    struct Card * lastCard = deckHead;
    while(lastCard->nextCard != NULL){
       lastCard = lastCard->nextCard;
    }
   
    lastCard->nextCard = playerHand->headOfHand;
    playerHand->headOfHand->prevCard = lastCard;
    playerHand->headOfHand = NULL;
    
}

int didIBlackJack(struct Hand * playerHand){
    if(playerHand->pointValueOfAllCards == 21){
        return 1;
    } else{
        return 0;
    }
}

int didIBust(struct Hand * playerHand){
    if(playerHand->pointValueOfAllCards > 21){
        return 1;
    } else{
        return 0;
    }
}

int yesOrNo(){
    char playerAnswer;
    int returnNumber = -1;
    while(returnNumber == -1){
        playerAnswer = getchar();
        playerAnswer = tolower(playerAnswer);
        if(playerAnswer == 'y'){
            returnNumber = 1;
        }else if(playerAnswer == 'n'){
            returnNumber = 0;
        }else{
            returnNumber = -1;
        }
    }
    return returnNumber;
}

void checkForWin(struct Hand * playerHand, struct Hand * enemyHand){
    if(playerHand->pointValueOfAllCards > enemyHand->pointValueOfAllCards){
        playerHand->gamePoints++;
        printf("Player Wins!\n");
    } else if(playerHand->pointValueOfAllCards < enemyHand->pointValueOfAllCards){
        enemyHand->gamePoints++;
        printf("Enemy Wins!\n");
    } else{
        printf("Tied no one wins!\n");
    }
}