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
bool dealerWins = false;
bool playerWins = false;
bool blackjack = false;

void DisplayWelcomeMessage();
void StartRound();
void Play();
void DrawCard(string owner, Hand &hand,  bool faceDown);
bool CheckWinner(bool end);
void Hit();
void Stand();
void UpdateStats();
void PrintResults();
void DisplayStats();
void ShuffleCardsIfNeeded();
void ClearGame();
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
    DisplayWelcomeMessage();
    SetupCommands();
    myDeck.BuildDeck();
    StartRound();
}

void DisplayWelcomeMessage(){
    cout << endl << endl << 
    "╔╗ ┬  ┌─┐┌─┐┬┌─ ┬┌─┐┌─┐┬┌─" << endl <<
    "╠╩╗│  ├─┤│  ├┴┐ │├─┤│  ├┴┐" << endl << 
    "╚═╝┴─┘┴ ┴└─┘┴ ┴└┘┴ ┴└─┘┴ ┴" << endl;
    cout << "Welcome to CLI Blackjack" << endl;
    cout << "Created by: Salvador Soberanes" << endl;

}

void StartRound(){
    ClearGame();
    cout << endl << endl;
    questionDialog("=== Do you want to play a round of blackjack? (Y/N)", playYesOrNoCommands);
}

void Play(){
    ShuffleCardsIfNeeded();

    cout << "<< Starting ROUND " << (++roundNumber) << " >> " << endl <<endl;
    
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

    PrintResults();
    UpdateStats();
    StartRound();
}

//Rule is to shuffle every 6 rounds
void ShuffleCardsIfNeeded(){
    if(roundNumber % 6 == 0)
    myDeck.ShuffleCards();
}

// Returns true if a winner is found
bool CheckWinner(bool end){
    if(dealerHand.IsBlackjack())
        dealerWins = true;
    
    if(playerHand.IsBlackjack())
        playerWins = true;

    if(playerHand.IsHandBust())
        dealerWins = true;
    
    if(dealerHand.IsHandBust())
        playerWins = true;

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
    return (playerWins || dealerWins);
}

void UpdateStats(){
    if(playerWins || dealerWins){
        if(dealerWins && playerWins)
        {
            tieCount++;
        }
        else
        {
            if(dealerWins)
                dealerWinCount++;
            else
                playerWinCount++;
        }
    }
}

void PrintBlackjack(){
    if(playerHand.IsBlackjack() || dealerHand.IsBlackjack()){
        cout << endl << 
        "╔╗ ┬  ┌─┐┌─┐┬┌─ ┬┌─┐┌─┐┬┌─" << endl <<
        "╠╩╗│  ├─┤│  ├┴┐ │├─┤│  ├┴┐" << endl << 
        "╚═╝┴─┘┴ ┴└─┘┴ ┴└┘┴ ┴└─┘┴ ┴" << endl;
    }
}

void PrintResults(){
    if(playerWins || dealerWins){
        cout << endl;
        PrintBlackjack();
        if(dealerWins && playerWins)
        {
            cout << "===== TIE GAME !!! =====" << endl;
        }
        else
        {
            if(dealerWins)
                cout << endl << "===== DEALER WINS!! =====" << endl <<endl;
            else
                cout << endl << "===== PLAYER WINS!! =====" << endl <<endl;
        }

        cout << "Dealer's Hand Value:" << dealerHand.GetValue() << endl;
        dealerHand.PrintCards();
        cout << endl;
        cout << "Player's Hand Value:" << playerHand.GetValue() << endl;
        playerHand.PrintCards();
        cout << endl << endl;
    }
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
        Stand();
}

//Dealers turn
void Stand(){
    CheckWinner(false);
    if(dealerWins)
        return;

    cout << "Dealer's turn. Dealer shows cards:"<<endl;
    dealerHand.PrintCards();
    while(dealerHand.CanDealerHit()) {
        DrawCard("himself", dealerHand, false);
    }
    CheckWinner(true);
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

void ClearGame(){
    playerHand.Clear();
    dealerHand.Clear();
    dealerWins = false;
    playerWins = false;
    blackjack = false;
}

void Exit(){
    cout << "Thanks for playing CLI Blackjack!" << endl;
    DisplayStats();
    cout << "See ya later!" << endl;
    exit(0);
}