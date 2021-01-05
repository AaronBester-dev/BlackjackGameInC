#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"


struct Card * makeNewCard(int value, char suit) {
    struct Card * newCard = malloc(sizeof(struct Card));
    newCard->value = value;
    newCard->suit = suit;
    newCard->nextCard = NULL;
    newCard->prevCard = NULL;
    return newCard;
}

struct Card * makeDeck(){
    int i = 0;
    int k = 0;
    struct Card * head = NULL;
    struct Card * newCard = NULL;
    char suit;
    for(i = 0; i < 4; i++){
        suit = 65+i;
        for(k = 1; k < 10; k++){
            newCard = makeNewCard(k,suit);
            head = push(head,newCard);
        }
        for(k = 0; k < 4; k++){
            newCard = makeNewCard(10,suit);
            head = push(head,newCard);
        }
    }
    return head;
}

struct Card * push(struct Card * head, struct Card * newCard){
    if(head == NULL){
        newCard->nextCard = NULL;
        newCard->prevCard = NULL;
        return newCard;
    } else{
        newCard->nextCard = head;
        head->prevCard = newCard;
        newCard->prevCard = NULL;   
        return newCard;
    }
}

void pushAtSpecificPoint(struct Card * head, struct Card * newCard, int locationOfCard){
    int i = 0;
    struct Card * node = head;
    struct Card * nextCard;
    for(i = 0; i < locationOfCard; i++){
        node = node->nextCard;
    }
    nextCard = node->nextCard;
    node->nextCard = newCard;
    nextCard->prevCard = newCard;
    newCard->prevCard = node;
    newCard->nextCard = nextCard;
}

struct Card * popAtSpecificPoint(struct Card * head, int locationOfCard){
    int i = 0;
    struct Card * node = head;
    struct Card * nextCard;
    struct Card * prevCard;
    for(i = 0; i < locationOfCard; i++){
        node = node->nextCard;
    }
    nextCard = node->nextCard;
    prevCard = node->prevCard;
    prevCard->nextCard = nextCard;
    nextCard->prevCard = prevCard;
    node->nextCard = NULL;
    node->prevCard = NULL;
    return node;
}

void shuffle(struct Card * deckHead){
    int i = 0;
    struct Card * cardToAdd = NULL;
    int cardLocation = 0;
    srand(time(NULL));
    for(i = 0; i < 100; i++){
        cardLocation = (rand() % (49-1+1)) + 1;
        cardToAdd = popAtSpecificPoint(deckHead, cardLocation);
        cardLocation = (rand() % (49-1+1)) + 1;
        pushAtSpecificPoint(deckHead,cardToAdd,cardLocation);
        
    }
}

struct Card * deal(struct Card * headYouTakeFrom, struct Hand * headYouGiveTo){
    struct Card * newHead = NULL;
    if(headYouTakeFrom->nextCard != NULL){
        newHead = headYouTakeFrom->nextCard;
        newHead->prevCard = NULL;
    }
    
    headYouGiveTo->headOfHand = push(headYouGiveTo->headOfHand,headYouTakeFrom);
    return newHead;
}

void printDeck(struct Card * head){
    struct Card * node = head;
    while(node != NULL){
        printf("%d,%c ",node->value,node->suit);
        node = node->nextCard;
    }
    
}

void freeDeck(struct Card * head){
    struct Card * nodeToFree = head;
    struct Card * nextNode = nodeToFree->nextCard;
    while(nextNode != NULL && nodeToFree != NULL){
        free(nodeToFree);
        nodeToFree = nextNode;
        nextNode = nextNode->nextCard;
    }
    free(nodeToFree);
}

