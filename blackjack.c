#include <stdio.h>
#include <stdlib.h>
#include "blackjack.h"

int main(){
    struct Card * deckHead = makeDeck();
    struct Hand * playerHand = malloc(sizeof(struct Hand));
    struct Hand * enemyHand = malloc(sizeof(struct Hand));
    int exitOrContinue = 1;
    int bustBlackjackOrNo = 0;
    int easyOrHard = 0;
    
    shuffle(deckHead);
    
    while(exitOrContinue == 1){
        printf("Do you want to play? Y(Yes) or N(No)\n");
        exitOrContinue = yesOrNo();
        
        if(exitOrContinue == 1){
            printf("Easy or Hard mode? Y(Easy) or N(Hard)");
            easyOrHard = yesOrNo();
            shuffle(deckHead);
            bustBlackjackOrNo = playerTurn(&deckHead, playerHand, enemyHand);
            if(bustBlackjackOrNo == 0){
               bustBlackjackOrNo = enemyTurn(&deckHead,enemyHand, playerHand, easyOrHard);
               if(bustBlackjackOrNo == 0){
                    checkForWin(playerHand,enemyHand);
                    returnCardsBackToDeck(deckHead,playerHand);
                    returnCardsBackToDeck(deckHead,enemyHand);
               }
               else if(bustBlackjackOrNo == 1){
                    printf("Enemy Busted!\n");
                    playerHand->gamePoints++;
                    returnCardsBackToDeck(deckHead,playerHand);
                    returnCardsBackToDeck(deckHead,enemyHand);
               }
               else{
                    printf("Enemy Blackjack!\n");
                    enemyHand->gamePoints++;
                    returnCardsBackToDeck(deckHead,playerHand);
                    returnCardsBackToDeck(deckHead,enemyHand);
               }
            } else if(bustBlackjackOrNo == 1){
                printf("You busted!\n");
                enemyHand->gamePoints++;
                returnCardsBackToDeck(deckHead,playerHand);
            } else{
                printf("Blackjack you win!\n");
                playerHand->gamePoints++;
                returnCardsBackToDeck(deckHead,playerHand);
            }
        }
    }
    freeDeck(deckHead);
    free(playerHand);
    free(enemyHand);
}