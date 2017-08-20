struct Card {
    int Value;
    std::string Suit;
    std::string Rank;
    std::string Fullname() { return Rank + " of " + Suit; }
};

class Deck {
    private:
        Card cards[52];
        int drawIndex;

    public:
        Deck();
        void BuildDeck();
        void ShuffleCards();
        Card DrawCard();
};