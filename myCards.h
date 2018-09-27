#ifndef MYCARDS_H_INCLUDED
#define MYCARDS_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "card.h"

using namespace std;


class myCards {
private:
    card cards[7];
    int experiments;
    int nones, pairs, twoPairs, threesOfAKind, straights, flushes, fulls, foursOfAKind, straightFlushes, royalFlushes;
    int nonesCum, pairsCum, twoPairsCum, threesOfAKindCum, straightsCum, flushesCum, fullsCum, foursOfAKindCum, straightFlushesCum, royalFlushesCum;


public:
    time_t gotRandomCards=0, flushDetected=0, straightDetected=0, pairDetected=0, straightFlushDetected=0, royalFlushDetected=0;

    myCards(int experiments=1000) {
        this->experiments = experiments;
        nones=0;
        pairs=0;
        twoPairs=0;
        threesOfAKind=0;
        straights=0;
        flushes=0;
        fulls=0;
        foursOfAKind=0;
        straightFlushes=0;
        royalFlushes=0;

        nonesCum=0;
        pairsCum=0;
        twoPairsCum=0;
        threesOfAKindCum=0;
        straightsCum=0;
        flushesCum=0;
        fullsCum=0;
        foursOfAKindCum=0;
        straightFlushesCum=0;
        royalFlushesCum=0;
    }

    int getNones() {return nones;}
    int getPairs() {return pairs;}
    int getTwoPairs() {return twoPairs;}
    int getThreesOfAKind() {return threesOfAKind;}
    int getStraights() {return straights;}
    int getFlushes() {return flushes;}
    int getFulls() {return fulls;}
    int getFoursOfAKind() {return foursOfAKind;}
    int getStraightFlushes() {return straightFlushes;}
    int getRoyalFlushes() {return royalFlushes;}

    int getNonesCum() {return nonesCum;}
    int getPairsCum() {return pairsCum;}
    int getTwoPairsCum() {return twoPairsCum;}
    int getThreesOfAKindCum() {return threesOfAKindCum;}
    int getStraightsCum() {return straightsCum;}
    int getFlushesCum() {return flushesCum;}
    int getFullsCum() {return fullsCum;}
    int getFoursOfAKindCum() {return foursOfAKindCum;}
    int getStraightFlushesCum() {return straightFlushesCum;}
    int getRoyalFlushesCum() {return royalFlushesCum;}

    double getNoneProb() {return double(nones)/experiments*100;}
    double getPairProb() {return double(pairs)/experiments*100;}
    double getTwoPairProb() {return double(twoPairs)/experiments*100;}
    double getThreeOfAKindProb() {return double(threesOfAKind)/experiments*100;}
    double getStraightProb() {return double(straights)/experiments*100;}
    double getFlushProb() {return double(flushes)/experiments*100;}
    double getFullProb() {return double(fulls)/experiments*100;}
    double getFourOfAKindProb() {return double(foursOfAKind)/experiments*100;}
    double getStraightFlushProb() {return double(straightFlushes)/experiments*100;}
    double getRoyalFlushProb() {return double(royalFlushes)/experiments*100;}

    double getNoneProbCum() {return double(nonesCum)/experiments*100;}
    double getPairProbCum() {return double(pairsCum)/experiments*100;}
    double getTwoPairProbCum() {return double(twoPairsCum)/experiments*100;}
    double getThreeOfAKindProbCum() {return double(threesOfAKindCum)/experiments*100;}
    double getStraightProbCum() {return double(straightsCum)/experiments*100;}
    double getFlushProbCum() {return double(flushesCum)/experiments*100;}
    double getFullProbCum() {return double(fullsCum)/experiments*100;}
    double getFourOfAKindProbCum() {return double(foursOfAKindCum)/experiments*100;}
    double getStraightFlushProbCum() {return double(straightFlushesCum)/experiments*100;}
    double getRoyalFlushProbCum() {return double(royalFlushesCum)/experiments*100;}

    card operator[] (const int& i) {
        return cards[i];
    }

    void addRandom(int ind) {
        int number = rand()%52;
        card thisCard(number);
        while(index(*this, thisCard)!=-1) {
            number = rand()%52;
            thisCard.setNumber(number);
        }
        cards[ind] = thisCard;
    }

    void fillRandom() {
        for(int i=0; i<7; i++) {
            addRandom(i);
        }
    }

    void printCards() {
        cout << "content of myCards object:" << endl;
        for (int i=0; i<7; i++) {
            cout << cards[i].getValue() << " of " << cards[i].getSuitString() << endl;
        }
    }

    int index(myCards Cards, card Card) {
        int result = -1;
        for(int i=0; i<7; i++) {
            if (Cards[i].getNumber()==Card.getNumber()) {result = i;}
        }
        return result;
    }


    void checkForCombinations() {
        bool none=true, pair2=false, twoPair=false, threeOfAKind=false, straight=false, flush=false, full=false, fourOfAKind=false, straightFlush=false, royalFlush=false;

        //FLUSH DETECTION
        time_t flushDetectionStarted = clock();
        int diamonds=0, hearts=0, clubs=0, spades=0;
        for(int i=0; i<7; i++) {
            switch (cards[i].getSuitInt()) {
                case 0: diamonds++; break;
                case 1: hearts++; break;
                case 2: clubs++; break;
                case 3: spades++; break;
            }
        }
        if (diamonds>=5 || hearts>=5 || clubs>=5 || spades>=5) {
            flush = true;
        }
        time_t flushDetectionEnded = clock();
        flushDetected += flushDetectionEnded - flushDetectionStarted;


        //STRAIGHT DETECTION
        //sort the cards in ascending order
        time_t straightDetectionStarted = clock();
        card cardsToBeSorted[7];
        card cardsSorted[7];
        copy(cards, cards+7, cardsToBeSorted);
        int minimum; //could be anything larger than 51
        int minloc = -1; //index of card with minimum value in cardsToBeSorted
        for(int i=0; i<7; i++) {
            minimum = 100;
            for(int j=0; j<7-i; j++) {
                if (cardsToBeSorted[j].getValue() < minimum) {
                    minimum = cardsToBeSorted[j].getValue();
                    minloc = j;
                }
            }
            cardsSorted[i] = cardsToBeSorted[minloc];
            for(int j=minloc; j<6; j++) {
                cardsToBeSorted[j] = cardsToBeSorted[j+1];
            }
        }
        //straight detection using sequence counter
        int sequence = 0;
        for(int i=1; i<7; i++) {
            if (cardsSorted[i].getValue() == cardsSorted[i-1].getValue()+1) {sequence++;}
            else if (cardsSorted[i].getValue() == cardsSorted[i-1].getValue()) {continue;}
            else {sequence=0;}
            if (sequence>=4) {straight=true;}
        }
        //now account for the fact that ace, 2, 3, 4, 5 is also a straight
        for(int i=0; i<7; i++) {
            if (cardsSorted[i].getValue()==14) {
                for(int j=0; j<7; j++) {
                    if (cardsSorted[j].getValue()==2) {
                        for(int k=0; k<7; k++) {
                            if (cardsSorted[k].getValue()==3) {
                                for(int l=0; l<7; l++) {
                                    if (cardsSorted[l].getValue()==4) {
                                        for(int m=0; m<7; m++) {
                                            if (cardsSorted[m].getValue()==5) {
                                                straight = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        time_t straightDetectionEnded = clock();
        straightDetected += straightDetectionEnded - straightDetectionStarted;


//        //pair detection comparing each card to every card - the second method is probably better
//        for(int i=0; i<7; i++) {
//            for(int j=0; j<7; j++) {
//                if (i==j) {continue;}
//                if (cards[i].getValue() == cards[j].getValue()) {
//                    pair2 = true; //use pair2 variable name just because pair is already taken
//                }
//            }
//        }


        //PAIR DETECTION using the sorted cards method
        time_t pairDetectionStarted = clock();
        int pairCounter = 0, otherPairCounter = 0;
        bool countOther = false;
        for(int i=1; i<7; i++) {
            if (cardsSorted[i].getValue() == cardsSorted[i-1].getValue()) {
                pairCounter++;
            } else {
                pairCounter = 0;
                if (pairCounter>=1 || pair2) {countOther=true;}
            }
            if (pairCounter>=1) {pair2=true;}
            if (pairCounter>=2) {threeOfAKind=true;}
            if (pairCounter>=3) {fourOfAKind=true;}

            if (pair2 && pairCounter==0 || countOther) {
                if (cardsSorted[i].getValue() == cardsSorted[i-1].getValue()) {
                    otherPairCounter++;
                } else {
                    otherPairCounter = 0;
                }
                if (otherPairCounter>=1) {
                    twoPair=true;
                    if (threeOfAKind) {full=true;}
                }
//                if (otherPairCounter>=2) {full=true;} //make sure to check that you really don't need this if statement!
            }
        }
        time_t pairDetectionEnded = clock();
        pairDetected += pairDetectionEnded - pairDetectionStarted;


        //STRAIGHT FLUSH DETECTION using flushSequence counter
        time_t straightFlushDetectionStarted = clock();
        int flushSequence = 0, currentSuit = -1;
        for(int i=1; i<7; i++) {
            if (cardsSorted[i].getValue() == cardsSorted[i-1].getValue()+1) {
                if (currentSuit==-1 && cardsSorted[i].getSuitInt()==cardsSorted[i-1].getSuitInt()) {
                    flushSequence++;
                    currentSuit = cardsSorted[i].getSuitInt();
                } else if (cardsSorted[i].getSuitInt() == currentSuit) {
                    flushSequence++;
                }
            } else if (cardsSorted[i].getValue() == cardsSorted[i-1].getValue()) {
                continue;
            } else {
                flushSequence = 0;
                currentSuit = -1; //maybe you don't need to do this?
            }
            if (flushSequence>=4) {straightFlush=true;}
        }
        //now account for the fact that ace, 2, 3, 4, 5 is also a straight
        for(int i=0; i<7; i++) {
            if (cardsSorted[i].getValue()==14) {
                int currentSuit2 = cardsSorted[i].getSuitInt();
                for(int j=0; j<7; j++) {
                    if (cardsSorted[j].getValue()==2 && cardsSorted[j].getSuitInt()==currentSuit2) {
                        for(int k=0; k<7; k++) {
                            if (cardsSorted[k].getValue()==3 && cardsSorted[k].getSuitInt()==currentSuit2) {
                                for(int l=0; l<7; l++) {
                                    if (cardsSorted[l].getValue()==4 && cardsSorted[l].getSuitInt()==currentSuit2) {
                                        for(int m=0; m<7; m++) {
                                            if (cardsSorted[m].getValue()==5 && cardsSorted[m].getSuitInt()==currentSuit2) {
                                                straightFlush = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        time_t straightFlushDetectionEnded = clock();
        straightFlushDetected += straightFlushDetectionEnded - straightDetectionStarted;


        //ROYAL FLUSH DETECTION
        time_t royalFlushDetectionStarted = clock();
        int royalDiamonds = 0, royalHearts = 0, royalClubs = 0, royalSpades = 0;
        for(int i=0; i<7; i++) {
            for(int j=10; j<=14; j++) {
                if (cardsSorted[i].getValue() == j) {
                    switch (cardsSorted[i].getSuitInt()) {
                        case 0: royalDiamonds++; break;
                        case 1: royalHearts++; break;
                        case 2: royalClubs++; break;
                        case 3: royalSpades++; break;
                    }
                }
            }
        }
        if (royalDiamonds>=5 || royalHearts>=5 || royalClubs>=5 || royalSpades>=5) {royalFlush=true;}
        time_t royalFlushDetectionEnded = clock();
        royalFlushDetected += royalFlushDetectionEnded - royalFlushDetectionStarted;


        //increment combination counters
        if (royalFlush) {royalFlushes++;}
        else if (straightFlush) {straightFlushes++;}
        else if (fourOfAKind) {foursOfAKind++;}
        else if (full) {fulls++;}
        else if (flush) {flushes++;}
        else if (straight) {straights++;}
        else if (threeOfAKind) {threesOfAKind++;}
        else if (twoPair) {twoPairs++;}
        else if (pair2) {pairs++;} //use pair2 variable name just because pair is already taken
        else if (none) {nones++;}

        if (royalFlush) {royalFlushesCum++;}
        if (straightFlush) {straightFlushesCum++;}
        if (fourOfAKind) {foursOfAKindCum++;}
        if (full) {fullsCum++;}
        if (flush) {flushesCum++;}
        if (straight) {straightsCum++;}
        if (threeOfAKind) {threesOfAKindCum++;}
        if (twoPair) {twoPairsCum++;}
        if (pair2) {pairsCum++;} //use pair2 variable name just because pair is already taken
        if (none) {nonesCum++;}
    }

};


#endif // MYCARDS_H_INCLUDED
