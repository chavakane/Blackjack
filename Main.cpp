#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cctype>
#include <cstdlib> 
#include <vector>
#include "Deck.cpp"
#include "Hand.cpp"
#include "InputHelper.cpp"
using namespace std;

Deck myDeck;
int roundNumber = 0;
int playerWinCount = 0;
int dealerWinCount = 0;
int tieCount = 0;
Hand playerHand;
Hand dealerHand;

void StartRound();
void Play();
void DrawCard(string owner, Hand &hand,  bool faceDown);
bool CheckWinner(bool end);
void Hit();
void Stand();
void DisplayStats();
void Exit();

vector<Command> hitOrStandCommands;
Command hitCommand = {"h", *Hit};
Command standCommand = {"s", *Stand};

vector<Command> playYesOrNoCommands;
Command playYesCommand = {"y", *Play};
Command playNoCommand = {"n", *Exit};

Command displayStatsCommand = {"-stats", *DisplayStats};
Command exitCommand = {"-quit", *Exit};

void SetupCommands(){
    globalCommands.push_back(displayStatsCommand);
    globalCommands.push_back(exitCommand);
    hitOrStandCommands.push_back(hitCommand);
    hitOrStandCommands.push_back(standCommand);
    playYesOrNoCommands.push_back(playYesCommand);
    playYesOrNoCommands.push_back(playNoCommand);
}

int main()
{
    SetupCommands();
    myDeck.BuildDeck();
    StartRound();
}

void Play(){
    //Shuffle deck every 6 rounds
    if(roundNumber % 6 == 0)
        myDeck.ShuffleCards();

    cout << "<< Starting round " << (++roundNumber) << " >> " << endl <<endl;
    
    DrawCard("player", playerHand, false);
    DrawCard("player", playerHand, false);
    cout << endl;
    DrawCard("himself", dealerHand, false);
    DrawCard("himself", dealerHand, true);
    cout << endl << endl;

    if(!CheckWinner(false)){
        cout << "== Hand value is: " << playerHand.GetValue() << endl;
        questionDialog("Hit or Stand? (H/S)\n", hitOrStandCommands);
    }
    StartRound();
}

// Returns true if a winner is found
bool CheckWinner(bool end){

    bool dealerWins = false;
    bool playerWins = false;
    bool blackjack = false;

    if(dealerHand.IsBlackjack()){
        dealerWins = true;
        blackjack = true;
    }

    if(playerHand.IsBlackjack()){
        playerWins = true;
        blackjack = true;
    }

    if(playerHand.IsOverflow())
        dealerWins = true;
    
    if(dealerHand.IsOverflow())
        playerWins = true;

    if(blackjack)
        cout << endl << endl << "****** BLACKJACK!!! *****";
    
    if(end && !(playerWins || dealerWins))
    {
        if(dealerHand.GetHandValueCloseTo21() == playerHand.GetHandValueCloseTo21())
        {
                playerWins = true;
                dealerWins = true;
        }
        else
        {
            dealerWins = dealerHand.GetHandValueCloseTo21() > playerHand.GetHandValueCloseTo21();
            playerWins = !dealerWins;
        }    
    }

    if(dealerWins && playerWins){
        tieCount++;
        cout << "Its a TIE!!:" << endl;
    }
    else
    if(dealerWins){
        dealerWinCount++;
        cout << endl << "===== DEALER WINS!! =====" << endl <<endl;
    }
    else
    if(playerWins){
        playerWinCount++;
        cout << endl << "===== PLAYER WINS!! =====" << endl <<endl;
    }

    if(playerWins || dealerWins){
        cout << "Dealer's Hand Value:" << dealerHand.GetValue() << endl;
        dealerHand.PrintCards();
        cout << endl;
        cout << "Player's Hand Value:" << playerHand.GetValue() << endl;
        playerHand.PrintCards();
        cout << endl << endl;
        return true;
    }
    return false;
}

void DrawCard(string owner, Hand &hand,  bool faceDown){
    cout << "Dealer draws card for " << owner << ":  ";
    Card card = myDeck.DrawCard();
    hand.AddCard(card);

    if(faceDown)
        cout << "Card is faced down" << endl;
    else
        cout << "Card is " << card.Fullname() << endl;
}

//Players turn
void Hit() {
    DrawCard("player", playerHand, false);
    if(playerHand.CanHit())
    {
        cout << "== Hand value is: " << playerHand.GetValue() << endl;
        questionDialog("Hit or Stand? (H/S)\n", hitOrStandCommands);
    }
    else
        CheckWinner(false);
}

void Stand(){
    //Dealers turn
    cout << "Dealer's turn. Dealer shows cards:"<<endl;
    dealerHand.PrintCards();
    while(dealerHand.CanDealerHit()){
        DrawCard("himself", dealerHand, false);
    }
    CheckWinner(true);
}

void ClearHands(){
    playerHand.Clear();
    dealerHand.Clear();
}

void StartRound(){
    ClearHands();
    cout << endl << endl;
    questionDialog("=== Do you want to play a round of blackjack? (Y/N)", playYesOrNoCommands);
}

void DisplayStats(){
    cout << endl << endl;
    cout << "=============== Statistics ==================" << endl;
    cout << "     Rounds played: " << roundNumber << endl;
    cout << "     Player win percentage: "<< setprecision(2) << (roundNumber > 0?(((float)playerWinCount / (float)roundNumber) * 100) : 0)<< "%" << endl;
    cout << "     Player wins: " << playerWinCount << endl;
    cout << "     Dealer wins: " << dealerWinCount << endl;
    cout << "     Draws: " << tieCount << endl;
    cout << "=============================================" << endl << endl << endl;
}

void DisplayWelcomeMessage(){

}

void Exit(){
    cout << "See ya later!" << endl;
    exit(0);
}