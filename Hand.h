class Hand {
    private:
        std::vector<Card> cards;
        int handValues[2];
        bool hasSoftHand();

    public:
        void AddCard(Card card);
        std::string GetValue();
        int GetHandValue();
        int GetSoftHandValue();
        int GetHandValueCloseTo21();
        bool CanHit();
        bool CanDealerHit();
        bool IsHandBust();
        bool IsBlackjack();
        void PrintCards();
        void Clear();
};