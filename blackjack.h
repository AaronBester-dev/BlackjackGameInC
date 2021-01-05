
struct Card{
    int value;
    char suit;
    struct Card * nextCard;
    struct Card * prevCard;
};

struct Hand{
    struct Card * headOfHand;
    int numberOfCards;
    int pointValueOfAllCards;
    int gamePoints;
};

struct Card * makeNewCard(int value, char suit);
struct Card * makeDeck();
struct Card * push(struct Card * head, struct Card * newCard);
struct Card * deal(struct Card * headYouTakeFrom, struct Hand * headYouGiveTo);
void printDeck(struct Card * head);
void freeDeck(struct Card * head);
void printUI(struct Hand * playerHand, struct Hand * enemyHand);
void calculateHandScore(struct Hand * hand);
int continueOrNot();
int playerTurn(struct Card ** deckHead,struct Hand * playerHand, struct Hand * enemyHand);
int yesOrNo();
void checkForWin(struct Hand * playerHand, struct Hand * enemyHand);
void shuffle(struct Card * deckHead);
int didIBlackJack(struct Hand * playerHand);
int didIBust(struct Hand * playerHand);
void returnCardsBackToDeck(struct Card * deckHead, struct Hand * playerHand);
int enemyTurn(struct Card ** deckHead, struct Hand * enemyHand, struct Hand * playerHand, int difficulty);
int easyEnemyYesOrNo(struct Hand * enemyHand);
int hardEnemyYesOrNo(struct Hand * enemyHand, struct Card * deckHead);