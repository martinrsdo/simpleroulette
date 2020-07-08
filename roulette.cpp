#include <iostream>
#include <stdlib.h>
#include <vector>
#include <bitset>
#include <ctime>


#define RED 0x01 
#define BLACK 0x02 
#define HIGH 0x04 
#define LOW 0x08 
#define EVEN 0x10 
#define ODD 0x20 

class aNumber
{
    
public: 
    aNumber()
    {
       //Random seed initialize
       srand(time(NULL));
       
       //For Winning use seed 1594172153 ;)
    }
    
    char draw()
    {
        //Draw a number 0-36
        int number = rand() % 37;
        char numberType = 0x00;
        
        //Set corresponding bits according to the number drawn
        if (number > 0) {
            if (number%2 == 0) {
                //Number is even
                numberType |= EVEN;
                
                //Ranges where even numbers are red
                if ((number > 28) or (number > 10 && number < 19)){
                    numberType |= RED; //Set Red bit
                }
                else
                {
                    numberType |= BLACK; //Set Black bit
                }
                
            }
            else
            {
                //Number is odd
                numberType |= ODD;
                
                //Ranges where odd numbers are red
                if ((number < 11) or (number > 18 && number < 29)){
                    numberType |= RED; //Set Red bit
                }
                else
                {
                    numberType |= BLACK; //Set Black bit
                }
            }
            
            if (number < 19){
                //Number is low
                numberType |= LOW;
            }
            else
            {
                //Number is high
                numberType |= HIGH;
            }
        }
        
        std::cout << "Number drawn: " << number << " Type: " << std::bitset<6>(numberType) << std::endl;
        return numberType;
    }
};

class Player
{
    std::string playerName;
    int currentBet;
    char whatBet;
    unsigned timesLost;
    std::vector <int> paper;

public:
    long balance;

public:
    Player(char wb, std::string pn)
    {
        playerName = pn;
        //Worst case scenario, player wins 4k times in a row. 
        //I wanted to avoid reallocating paper each time that a new number is added.  
        paper.reserve(4001); 
        
        // whatBet contains the bet config of the player, is then compared to the drawn number type
        whatBet = wb; 
        balance = 0;
        initPaper();
    }

    void initPaper(){
        timesLost = 0;
        paper.clear();
        paper.push_back(1);
        paper.push_back(2);
        paper.push_back(3);
        paper.push_back(4);
    }

    void printPaper(){
        //In order to help debug
        std::cout << paper[timesLost];
        for (unsigned i = timesLost + 1; i<paper.size(); i++) 
            {std::cout << "," << paper[i];}
    }

    void bets(){
        int auxBet;
        //if only one number left this is the bet.
        if (paper.size() < 2 + timesLost){
            auxBet = paper[timesLost];
        }
        else
        {
            auxBet = paper[timesLost] + paper.back();
        }
        
        // Check for the minimum bet value
        if (auxBet < 5) {
            auxBet = 5;
        }
        //Check if bet is greater than maximun alowed and restart the paper if so.
        else if (auxBet > 4000){
            initPaper();
            auxBet = 5;
        }
        currentBet = auxBet;
        
        std::cout << playerName << " Bets:" << currentBet << " Paper: ";
        printPaper();
        std::cout << std::endl;
        
    }

    void wins(){
        balance += currentBet;
        paper.push_back(currentBet);
    }
         
    void losses(){
        balance -= currentBet;
        if(paper.size() > 2 + timesLost){
            //More than 2 valid element in the array, remove first and last.
            paper.pop_back();
            //To avoid moving the paper array, I keep track and increment where is my valid first element
            timesLost++;
        }
        else
        {
            initPaper();
        }
    }

    void checkResult(char &result){
        std::cout << playerName << " ";
        //Bitwise AND
        if(result & whatBet)
        {
            wins();
            std::cout << "Won" ;
        }
        else
        {
            losses();
            std::cout << "Lost" ;
        }
        std::cout << ", Balance: " << balance << std::endl;
    }
};



int main()
{
    aNumber x;
    char numberType;
    std::vector<Player> players;
    long totalRounds = 10000;

    //Create the players
    players.reserve(6);
    players.emplace_back(RED,"A (Red)");
    players.emplace_back(BLACK,"B (Black)");
    players.emplace_back(HIGH,"C (High)");
    players.emplace_back(LOW,"D (Low)");
    players.emplace_back(EVEN,"E (Even)");
    players.emplace_back(ODD,"F (Odd)");

    for(int i=0;i < totalRounds; i++){
            //Call each player Bet method
            std::cout << "Round number: " << i + 1 <<". Place your bets..." << std::endl;
            for (Player &aPlayer: players){
                aPlayer.bets();
            }
            std::cout << std::endl;
            
            //Draw a random number and get its type
            numberType = x.draw();
            
            //Call each player to check if they won or lost
            for (Player &aPlayer: players){
                aPlayer.checkResult(numberType);
            }
            std::cout << std::endl;
            
            //...Repeat!
    }
    long teamBalance = 0;
    for (Player &aPlayer: players){
        teamBalance += aPlayer.balance;
    }
    std::cout << "Team balance after "<< totalRounds << " rounds: " << teamBalance << std::endl;
}
