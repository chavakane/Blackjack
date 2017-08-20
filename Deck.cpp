#include "Deck.h"
using namespace std;

string cardSuits[] = {"Clubs ♣", "Diamonds ♦", "Hearts ♥","Spades ♠"};
string cardRanks [] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};

Deck::Deck(){
    drawIndex = 0;
}

// A utility function to print an array
void printArray (Card arr[], int n)
{
    for (int i = 0; i < n; i++){
        Card card = arr[i];
        cout << card.Rank << " of " << card.Suit << endl;
    }
}


void Deck::BuildDeck(){
    for(int s = 0; s < 4; s++){
        string suit = cardSuits[s];
        for(int r = 0; r < 13; r++){
            //determine card value and rank
            int value = r % 13;
            string rank = cardRanks[value];
            if(value >= 10) value = 9;

            //create card
            Card card;
            card.Suit = suit;
            card.Rank = rank;
            card.Value = value + 1;
            
            //insert card into deck
            int cardIndex = r + (s * 13);
            cards[cardIndex] = card;
        }
    }
}  


void switchCards (Card *a, Card *b)
{
    Card temp = *a;
    *a = *b;
    *b = temp;
}

void Deck::ShuffleCards() {
    cout << "<< Shuffling cards ... >>>" << endl;
    drawIndex = 0;
    srand (time(NULL));
    for (int i = 51; i > 0; i--)
    {
        int j = rand() % (i+1);
        switchCards(&cards[i], &cards[j]);
    }
}

Card Deck::DrawCard(){
    if(drawIndex >= 52) {
        cout << "<< Last card in deck was drawn ... >>>" << endl;
        ShuffleCards();
    }
    return cards[drawIndex++];
}
