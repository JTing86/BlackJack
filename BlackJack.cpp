#include <iostream>
#include <vector>
#include <cstdlib> // for std::and() and std::srand()
#include <ctime> // for std::time()
#include <string>
#include <sstream>

using namespace std;


int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (RAND_MAX + 1.0);
    return min + static_cast<int>((max - min + 1) * (rand() * fraction));
}

using namespace std;

class Card
{
private:
    char suit;
    int value;
public:
    Card(char suitIn,int valIn)
    {
        suit = suitIn;
        value = valIn;
    }
    char getSuit() {return suit;}
    int getVal()
    {
        if (value>10) //for blackjack, value larger than 10 counts as ten
            return 10;
        else
            return value;
    }

    string to_string() {
        stringstream string_builder;
        string_builder << "Card: " << suit << value;
        return string_builder.str();
    }
};


class Deck
{
private:

    vector<Card> Cards{};

public:

    void shuffle()
    {
        //cout<<"being shuffling"<<"\n";
        for(int i= Cards.size()-1; i>0;i--)
        {
            //cout<<"getting random number"<<"\n";
            const int k = getRandomNumber(0,i);
            //cout<<"got random number, is: "<<k<<"\n";
            swap(Cards.at(k), Cards.at(i));
            //cout<<"swaping"<<"\n";
        }
        //cout<<"done shuffling"<<"\n";
    }

    void print()
    {
        for(int i = 0;i<Cards.size();i++)
        {
            cout << Cards[i].to_string() << "\n";
        }
    }
    void addCard(Card a)
    {
        Cards.push_back(a);
    }

    Card getCard() //get the first card of the deck
    {
        return Cards.back(); // return the last element
    }
    void popCard()
    {
        Cards.pop_back(); //remove the last element
    }

    int getLength(){return Cards.size();}


    void creatFullDeck()
    {
        // heart
        //cout<<"starting to creat new deck"<<"\n";
        for(int i=1;i<14;i++)
        {
            Card c('h',i);
            Cards.push_back(c);
            //cout<<"make heart"<<"\n";
        }
        //sprade
        for(int i=1;i<14;i++)
        {
            Card c('s',i);
            Cards.push_back(c);
            //cout<<"make Sprader"<<"\n";
        }
        //diamond
        for(int i=1;i<14;i++)
        {
            Card c('d',i);
            Cards.push_back(c);
            //cout<<"make Diamond"<<"\n";
        }
        //clubs
        for(int i=1;i<14;i++)
        {
            Card c('c',i);
            Cards.push_back(c);
            //cout<<"make club"<<"\n";
        }
    }
    Deck getFullDeck()
    {
        Deck a;
        a.creatFullDeck();
        return a;
    }
};

class Game
{
private:
    Deck dealerDeck;

    Deck dealerCards;
    Deck myCards;
    Deck player1Cards;
    Deck player2Cards;
    Deck player3Cards;

    int runningCount;
    float trueCount;
    int handVal;
    int threshold;
    int bustCount;
    int turnCount;

public:

    Game(int thresholdIN)
    {
        dealerDeck.creatFullDeck();
        dealerCards={};
        myCards={};
        player1Cards={};
        player2Cards={};
        player3Cards={};

        dealerDeck.shuffle();
        //cout<<"game starts\n";
        //dealerDeck.print();
        runningCount = 0;
        trueCount = 0;
        handVal = 0;
        threshold = thresholdIN;
        bustCount = 0;
        turnCount = 0;
    }

    void deal()
    {
        int val =  dealerDeck.getCard().getVal();
        handVal += val;
        //cout<<dealerDeck.getCard().to_string()<<"\n"; // print out the dealed card
        //dealerDeck.popCard();
    }

    void printResult()
    {
        cout<< "Threshold: "<<threshold<<". Bust Fraction: "<<(float)bustCount / (float)10000<<"\n";
    }

    void printProcess()
    {
        //cout<<"handVal: "<<handVal<<"dealerDeck: "<<"\n";
        dealerDeck.print();
    }

    void printLength()
    {
        int i= dealerDeck.getLength();
        cout<<i<<"\n";
    }
    void CardCounting()
    //step one, assign values to each card
    //step two, calculate the sum of value of revealed Cards, this is called the running count
    //step three, divide the running count by the number of deck remaining, this is called the true count
    //step four, the greater the conversion, the more you should bet
    {
        int val =  dealerDeck.getCard().getVal();

        if(val >= 10 || val == 1) //or
            trueCount -= 1;
        else if(val >= 2 && val <= 6)//and
            trueCount += 1;
        trueCount = (float)runningCount / (float) dealerDeck.getLength();
    }
    void helpme()
    {
        if (trueCount >0)
            cout<<"You should bet high."<<"\n";
        else if(trueCount<0)
            cout<<"You should bet low."<<"\n";
        else
            cout<<"Don't bet!"<<"\n";
    }

    void initialSetup()
    {
        Game(20);
        dealerSetup();
        runningCount = 0;
        trueCount = 0;
        for(int i = 1;i<=3;i++)
        {
            playerSetup(i);
        }
    }
    void setPoint()
    {
        int count =  dealerDeck.getCard().getVal();
        runningCount += count;
    }
    void dealerSetup()
    {
        dealerCards.addCard(dealerDeck.getCard());
        dealerDeck.popCard();
    }
    void playerSetup(int i)
    {
        //int count =  dealerDeck.getCard().getVal();
        //runningCount += count;
        if(i == 1)
            player1Cards.addCard(dealerDeck.getCard());
        else if(i==2)
            player2Cards.addCard(dealerDeck.getCard());
        else if(i==3)
            player3Cards.addCard(dealerDeck.getCard());
        else if(i==4)
            myCards.addCard(dealerDeck.getCard());
        dealerDeck.popCard();
    }
    void play()
    {
        initialSetup();
        while(turnCount < 10000)
        {
            if(dealerDeck.getLength()<=0)
            {
                dealerDeck.creatFullDeck();
                dealerDeck.shuffle();

            }
            else
                deal();
                while (dealerDeck.getLength()>0)
                {
                    if(dealerDeck.getCard().to_string() == "c10") //is blackJack
                    {

                    }
                }
        }

    }
    void findBustFreq()
    {
        turnCount = 0;
        while(turnCount < 10000)
        {
            if(dealerDeck.getLength()<=0)
            {
                //cout<<"dealer deck length before: "<<dealerDeck.getLength()<<"\n";
                dealerDeck.creatFullDeck();

                dealerDeck.shuffle();
                //dealerDeck.print();

                //cout<<"handVal: "<<handVal<<"getting new cards\n";
                //cout<<"dealer deck length after: "<<dealerDeck.getLength()<<"\n";
            }
            else
                deal();
                while (dealerDeck.getLength()>0)
                {
                    if(dealerDeck.getCard().to_string() == "c10") //is blackJack
                    {
                        turnCount +=1;
                        dealerDeck.popCard();
                        //cout<<"turnCount: "<<turnCount<<"\n";
                        //cout<<"handVal: "<<handVal<<"blackJack\n";
                        //cout<<"dealer deck length: "<<dealerDeck.getLength()<<"\n";
                        handVal = 0;
                        break;
                    }
                    else if(handVal > threshold) //bust
                    {
                        bustCount +=1;
                        turnCount += 1;
                        dealerDeck.popCard();
                        //cout<<"turnCount: "<<turnCount<<"\n";
                        //cout<<"handVal: "<<handVal<<" busted!\n";
                        //cout<<"dealer deck length: "<<dealerDeck.getLength()<<"\n";
                        handVal = 0;
                        break;

                    }
                    else if(handVal == threshold) //reach threshold
                    {
                        turnCount +=1;
                        dealerDeck.popCard();
                        //cout<<"turnCount: "<<turnCount<<"\n";
                        //cout<<"handVal: "<<handVal<<"reach threshold!\n";
                        //cout<<"dealer deck length: "<<dealerDeck.getLength()<<"\n";
                        handVal = 0;
                        break;
                    }
                    else
                        dealerDeck.popCard();
                        break;
                }

        }

    }
};
int main()

{
    srand(static_cast<unsigned int>(std::time(0)));
    cout<<"Question 4"<<'\n';
    for(int i=10;i<21;i++)
    {
        Game g(i);
        g.findBustFreq();
        g.printResult();
        g.play();
    }
    return 0;
}
