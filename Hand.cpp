#include "Hand.h"
using namespace std;


void Hand::PrintCards (){
    for (std::vector<Card>::iterator it = cards.begin() ; it != cards.end(); ++it){
        Card card = (*it);
        cout << "\t" << card.Rank << " of " << card.Suit << endl;
    }
}

void Hand::AddCard(Card card){
    cards.push_back(card);
    handValues[0] = handValues[0] + card.Value;
    if(card.Rank == "Ace" && handValues[1] < 11)
        handValues[1] = handValues[1] + 11;
    else
        handValues[1] = handValues[1] + card.Value;
}

string Hand::GetValue(){
    if(!hasSoftHand() || (GetHandValue() <= 21 && GetSoftHandValue() >21)){
        return to_string(GetHandValue());
    }

    if(GetSoftHandValue() <= 21 && GetHandValue() >21){
        return to_string(GetSoftHandValue());
    }
    return to_string(GetHandValue()) + " (Soft hand: " + to_string(GetSoftHandValue()) + ") ";
}

int Hand::GetHandValue(){
    return handValues[0];
}

int Hand::GetSoftHandValue(){
    return handValues[1];
}

bool Hand::hasSoftHand(){
    return GetHandValue() != GetSoftHandValue();
}

int Hand::GetHandValueCloseTo21(){
    if(GetHandValue()<=21 && GetHandValue() >= GetSoftHandValue())
        return GetHandValue();
    if(GetSoftHandValue()<=21 && GetSoftHandValue() >= GetHandValue())
        return GetSoftHandValue();
    return 0;
}

bool Hand::CanHit(){
    return GetHandValue() < 21 || GetSoftHandValue() < 21;
}

bool Hand::IsHandBust(){
    return GetHandValue() > 21 && GetSoftHandValue() > 21;
}

//Rule - Dealer must hit on soft 17
bool Hand::CanDealerHit(){
    if(hasSoftHand())
        return GetSoftHandValue() < 18;
    return GetHandValue() < 17;
}

bool Hand::IsBlackjack(){
    return GetHandValue() == 21 || GetSoftHandValue() == 21;
}

void Hand::Clear(){
    cards.clear();
    handValues[0] = 0;
    handValues[1] = 0;
}