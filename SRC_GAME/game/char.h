// FIND // ZNAJDŹ //

}
ESex GET_SEX(LPCHARACTER ch);


// ADD ABOVE // DODAJ NAD //

public:
        struct S_CARD
        {
            DWORD    type;
            DWORD    value;
        };


        struct CARDS_INFO
        {
            S_CARD cards_in_hand[5];
            S_CARD cards_in_field[3];
            DWORD    cards_left;
            DWORD    field_points;
            DWORD    points;
        };
    
        void            Cards_open(DWORD safemode);
        void            Cards_clean_list();
        DWORD            GetEmptySpaceInHand();
        void            Cards_pullout();
        void            RandomizeCards();
        bool            CardWasRandomized(DWORD type, DWORD value);
        void            SendUpdatedInformations();
        void            SendReward();
        void            CardsDestroy(DWORD reject_index);
        void            CardsAccept(DWORD accept_index);
        void            CardsRestore(DWORD restore_index);
        DWORD            GetEmptySpaceInField();
        DWORD            GetAllCardsCount();
        bool            TypesAreSame();
        bool            ValuesAreSame();
        bool            CardsMatch();
        DWORD            GetLowestCard();
        bool            CheckReward();
        void            CheckCards();
        void            RestoreField();
        void            ResetField();
        void            CardsEnd();
        void            GetGlobalRank(char * buffer, size_t buflen);
        void            GetRundRank(char * buffer, size_t buflen);
    protected:
        CARDS_INFO    character_cards;
        S_CARD    randomized_cards[24];
