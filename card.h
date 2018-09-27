#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include <cstring>

using namespace std;


class card {
private:
    int number;

public:
    card(int number=0) {
        this->number = number;
    }

    void setNumber(int number) {
        this->number = number;
      }

    void setCard(string suit, int value) {
        number = suit2int(suit)*13 + value-2;
    }

    int getNumber() {
        return number;
    }

    int getSuitInt() {
        return number/13;
    }

    string getSuitString() {
        return suit2string(number/13);
    }

    int getValue() {
        return number%13+2;
    }

    int suit2int(string suit) {
        if (suit=="diamonds") {return 0;}
        else if (suit=="hearts") {return 1;}
        else if (suit=="clubs") {return 2;}
        else if (suit=="spades") {return 3;}
        else {return -1;} //this means an error
    }

    string suit2string(int suit) {
    switch (suit) {
        case 0: {return "diamonds";}
        case 1: {return "hearts";}
        case 2: {return "clubs";}
        case 3: {return "spades";}
        default: {return "Error!";}
    }
}

};

#endif // CARD_H_INCLUDED
