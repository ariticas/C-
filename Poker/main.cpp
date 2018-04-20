//
//  main.cpp
//  Poker
//
//  Created by Ari Ticas on 11/14/17.
//  Copyright © 2017 Ari Ticas. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include<iostream>
#include<map>
#include <algorithm>
using namespace std;


class Player {
public:
    Player(string n1);
    void GetHand();
    vector<string> returnCard(string card);
    void rankOfHand(vector<string> values ,vector<string> suits);
    bool allSameSuit(vector<string>suits);
    void shuffle();
    void assignRank();
    int sameSuits();
    bool consecutiveValues();
    int countPairs(vector<int>num1Values);
    void winner();
    int getRank();
    void tieBreaker(int value);
private:
    
    int tiebreaker;
    int randomNumber;
    int rank = 0;
    string name;
    string finalHand;
    string hand[5];
    string randomCard;
    string card;
    vector<string> deck;
    vector<string>values;
    map<string,int>numberValues;
    vector<string>suits;
    vector<int>numValues;
   
};

Player::Player(string n1):name(n1){}

void Player::GetHand(){
    cout << "Player name: " << name << endl;
    cout << endl;
    
    
    
    shuffle();
    
    
    // each hand is passed and turned into and indivual vector
    for(int i = 0; i<5 ;i++){
       card = hand[i];
       cout << card << endl;
        
       //card as individual vector myCard
       vector<string> myCard = returnCard(card);
       
       //myCard is seperated into a vector of values and a vector of suits
       
        
       values.push_back(myCard[0]);
       suits.push_back(myCard[2]);
    }
    
    }





vector<string> Player::returnCard(string card){
    
    //takes the hand and breaks it down into a vector with three elements; the value, the word "of", and the rank
    istringstream cardStream(card);
    vector<string> splithand((istream_iterator<string>(cardStream)),istream_iterator<string>());

    return splithand;
    
}




void Player::shuffle(){
    deck = {"two of hearts","three of hearts","four of hearts","five of hearts","six of hearts","seven of hearts","eight of hearts","nine of hearts","ten of hearts","jack of hearts","queen of hearts","king of hearts","ace of hearts","two of spades","three of spades","four of spades","five of spades","six of spades","seven of spades","eight of spades","nine of spades","ten of spades","jack of spades","queen of spades","king of spades","ace of spade","two of diamonds","three of diamonds","four of diamonds","five of diamonds","six of diamonds","seven of diamonds","eight of diamonds","nine of diamonds","ten of diamonds","jack of diamonds","queen of diamonds","king of diamonds","ace of diamonds","two of clubs","three of clubs","four of clubs","five of clubs","six of clubs","seven of clubs","eight of clubs","nine of clubs","ten of clubs","jack of clubs","queen of clubs","king of clubs","ace of clubs"};
    
    
    
    
    for(int i = 0; i<=4 ;i++){
        randomNumber = rand() % 53;
        randomCard = deck[randomNumber-1];
        hand[i] = randomCard;
    }
    
    
}

void Player::assignRank(){
    numberValues = {{"two",2},{"three",3},{"four",4},{"five",5},{"six",6},{"seven",7},{"eight",8},{"nine",9},{"ten",10},{"jack",11},{"queen",12},{"king",13},{"ace",14}};
    
    vector<int> royalFlushValues = {10,11,12,13,14};
    //populate numvalues with corresponding int values of
    for(int i = 0;i<5;i++){
        numValues.push_back(numberValues[values[i]]);
    }
    
    
    
   
    
    
    sort (numValues.begin(), numValues.begin()+5);
    
    int checker = sameSuits();

    if(checker == 1){
        if(numValues == royalFlushValues){
             rank = 200;
            finalHand = "Royal Flush";
        }
        if(numValues != royalFlushValues && consecutiveValues()){
            rank = 100;
            finalHand = "Straight Flush";
            tieBreaker(numValues[4]);
            
        }
        else{
              rank = 60;
            finalHand = "Flush";
            string suitRank = suits[1];
            if (suitRank == "clubs"){
                rank = rank + 1;
            }
            if (suitRank == "diamonds"){
                rank = rank + 2;
            }
            if (suitRank == "hearts"){
                rank = rank + 3;
            }
            if (suitRank == "spades"){
                rank = rank + 4;
            }

        }
        
    }
    
    if(consecutiveValues()){
        rank = 50;
        finalHand = "Straight";
        tieBreaker(numValues[4]);
    }
    
    if ( equal(numValues.begin() + 1, numValues.end(), numValues.begin()) ){
        rank = 120;
        finalHand = "5 of a kind";
        tieBreaker(numValues[4]);
    }
    
    int pairs =  countPairs(numValues);
  
    if(pairs == 1 && checker !=1){
        rank = 15;
        finalHand = "1 Pair";
        tieBreaker(tiebreaker);
    }
    if(pairs == 2 && checker !=1){
        rank = 20;
        finalHand = "2 Pairs";
        tieBreaker(tiebreaker);
    }
    if(pairs == 3 && checker !=1){
        rank = 40;
        finalHand = "3 of a kind";
        tieBreaker(tiebreaker);
    }
    
    if(pairs >= 4 && !equal(numValues.begin() + 1, numValues.end(), numValues.begin())&& checker !=1 ){
        vector<int>first4;
        vector<int>last4;
        
        for(int i = 0; i < numValues.size();i++){
            cout << numValues[i] << endl;
        }
        cout << endl;
        
        for(int i = 0; i < 4;i++){
            first4.push_back(numValues[i]);
        }
      
        for(int i = 1; i < 5;i++){
            last4.push_back(numValues[i]);
        }
        if ( equal(first4.begin() + 1, first4.end(), first4.begin()) ||equal(last4.begin() + 1, last4.end(), last4.begin()) ){
        rank = 80;
        finalHand = "4 of a kind";
            tieBreaker(numValues[2]);
        }
        else{
            rank = 60;
            finalHand = "Full House";
            //look at the strength of the three of a kind to break a tie
            tieBreaker(numValues[2]);
        }
    }
    
    if(pairs == 0){
        rank = 0;
        finalHand = "No Pairs";
        tieBreaker(numValues[4]);
    }
    cout << endl;
    cout << finalHand << endl;
    cout << endl;
}



int Player::sameSuits(){
    
    if ( equal(suits.begin() + 1  , suits.end(), suits.begin()) ){
        return 1;
    }
    return 0;
}

bool Player::consecutiveValues(){
    int j = 1;
    for(int i = 0; i < 4 ; i++){
        
   
        if( (numValues[i]+1) != numValues[j]){
        return false;
    }
        j= j+1;
    }
    return true;
}

int Player::countPairs(vector<int>num1Values){
    
    int pairs = 0;
    for( int i = 0; i < 4 ;i++){
        for( int j = i + 1 ; j < 5 ; j++){
            if (num1Values[i] == num1Values[j]){
                pairs = pairs + 1;
                tiebreaker = numValues[i];
            }
        }
      
    }
 
    return pairs;
}

int Player::getRank(){
    
    return rank;
}

void Player::tieBreaker(int value){
    switch(value){
        case 2:
            rank = rank + 1;
            break;
        case 3:
            rank = rank + 2;
            break;
        case 4:
            rank = rank + 3;
            break;
        case 5:
            rank = rank + 4;
            break;
        case 6:
            rank = rank + 5;
            break;
        case 7:
            rank = rank + 6;
            break;
        case 8:
            rank = rank + 7;
            break;
        case 9:
            rank = rank + 8;
            break;
        case 10:
            rank = rank + 9;
            break;
        case 11:
            rank = rank + 10;
            break;
        case 12:
            rank = rank + 11;
            break;
        case 13:
            rank = rank + 12;
            break;
        case 14:
            rank = rank + 14;
            break;
    }
  
}


int main(int argc, const char * argv[]) {
        srand((unsigned)time(0));
        vector<int>players;
        string winner;
        map<string,int>playerRankings;
        string quitOrPLay;
        int numberOfPlayers = 0 ;
        cout << "Do you wish to play poker or quit (p or q)? ";
        cin >> quitOrPLay;
        cout << endl;
    if(quitOrPLay == "q"){
        exit(1);
    }

    
    while(quitOrPLay == "p"){
        
        if(quitOrPLay == "q"){
            exit(1);
        }
        
        
            cout << "How many players are playing?: ";
            cin >> numberOfPlayers;
            cout << endl;
        int temp = 0;
        
        for(int i = 0;i <= numberOfPlayers-1;i++){
            cout << "Enter players name: ";
            string name;
            cin >> name ;
            cout << endl;
            Player player = Player(name);
            player.GetHand();
            player.assignRank();
            playerRankings.insert(pair<string,int>(name,player.getRank()));
            
            
            if( player.getRank() > temp){
                winner = name;
                temp = player.getRank();
                
            }
            
    }
      
        cout << "The winner is: " << winner << endl;
        cout << "Do you wish to play poker or quit (p or q)? ";
        cin >> quitOrPLay;
        
    }
    
    return 0;
    }
    
    
    
  
    
    

  
    











