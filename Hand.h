class Hand {
    private:
        std::vector<Card> cards;
        int handValues[2];

    public:
        void AddCard(Card card);
        std::string GetValue();
        int GetHandValue();
        int GetSoftHandValue();
        int GetHandValueCloseTo21();
        bool CanHit();
        bool CanDealerHit();
        bool IsBlackjack();
        bool IsOverflow();
        void PrintCards();
        void Clear();
};