#include <iostream>
#include <iomanip>
#include <ctime>
#include "card.h"
#include "myCards.h"

using namespace std;

int experiments = 1000000;

int main()
{
    time_t started = clock();

    //initialize myCards object
    myCards my_cards(experiments);

    //check what combinations those cards have
    for(int exp=0; exp<experiments; exp++) {
        my_cards.fillRandom();
        my_cards.checkForCombinations();
    }

    //output the probabilities
    cout << setw(27) << "prob." << setw(20) << "cumulative prob." << endl;
    cout << setprecision(3);
    cout << setw(16) << "none:" << setw(10) << my_cards.getNoneProb() << "%" << setw(10) << my_cards.getNoneProbCum() << "%" << endl;
    cout << setw(16) << "pair:" << setw(10) << my_cards.getPairProb() << "%" << setw(10) << my_cards.getPairProbCum() << "%" << endl;
    cout << setw(16) << "two pair:" << setw(10) << my_cards.getTwoPairProb() << "%" << setw(10) << my_cards.getTwoPairProbCum() << "%" << endl;
    cout << setw(16) << "three of a kind:" << setw(10) << my_cards.getThreeOfAKindProb() << "%" << setw(10) << my_cards.getThreeOfAKindProbCum() << "%" << endl;
    cout << setw(16) << "straight:" << setw(10) << my_cards.getStraightProb() << "%" << setw(10) << my_cards.getStraightProbCum() << "%" << endl;
    cout << setw(16) << "flush:" << setw(10) << my_cards.getFlushProb() << "%" << setw(10) << my_cards.getFlushProbCum() << "%" << endl;
    cout << setw(16) << "full:" << setw(10) << my_cards.getFullProb() << "%" << setw(10) << my_cards.getFullProbCum() << "%" << endl;
    cout << setw(16) << "four of a kind:" << setw(10) << my_cards.getFourOfAKindProb() << "%" << setw(10) << my_cards.getFourOfAKindProbCum() << "%" << endl;
    cout << setw(16) << "straight flush:" << setw(10) << my_cards.getStraightFlushProb() << "%" << setw(10) << my_cards.getStraightFlushProbCum() << "%" << endl;
    cout << setw(16) << "royal flush:" << setw(10) << my_cards.getRoyalFlushProb() << "%" << setw(10) << my_cards.getRoyalFlushProbCum() << "%" << endl << endl;

    time_t ended = clock();
    time_t totalTime = ended - started;
    cout << setprecision(3);
    cout << experiments << " experiments done in " << (double)(totalTime)/CLOCKS_PER_SEC << " seconds, of which:" << endl;
    cout << setw(27) << "choosing random cards: " << setw(5) << (double)(my_cards.gotRandomCards)/totalTime*100 << "%" << endl;
    cout << setw(27) << "flush detection: " << setw(5) << (double)(my_cards.flushDetected)/totalTime*100 << "%" << endl;
    cout << setw(27) << "straight detection: " << setw(5) << (double)(my_cards.straightDetected)/totalTime*100 << "%" << endl;
    cout << setw(27) << "pair detection: " << setw(5) << (double)(my_cards.pairDetected)/totalTime*100 << "%" << endl;
    cout << setw(27) << "straight flush detection: " << setw(5) << (double)(my_cards.straightFlushDetected)/totalTime*100 << "%" << endl;
    cout << setw(27) << "royal flush detection: " << setw(5) << (double)(my_cards.royalFlushDetected)/totalTime*100 << "%" << endl;

    return 0;
}
