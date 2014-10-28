/* War game made by Ammar Alsibai
used for studying data structures and object oriented programming
The game is now setup for a human player to play against the computer.

code inspired from Timothy Budd "data structures in c++ using stl"
*/

#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

enum suits {diamond, club, heart, spade};

class Card {
public:
	//constructors
	Card();
	Card (suits, int);

	//data fields
	int rank; //rank of Card
	suits suit; //suit of Card
};

Card::Card ()
{
	// initializes new Card with default values (ace of spades)
	rank = 1;
	suit = spade;
}
Card::Card (suits sv, int rv)
{
	rank = rv; //rank value
	suit = sv; //suit value
}

ostream & operator << (ostream & out, Card & aCard)
// output a text representation of a Card
{
	// first output rank
	switch (aCard.rank) {
		case 1: out << "Ace"; break;
		case 11: out << "Jack"; break;
		case 12: out << "Queen"; break;
		case 13: out << "king"; break;
		default: //output numbner
		out << aCard.rank; break;
	}
	//then output suit
	switch (aCard.suit) {
		case diamond: out << " of Diamonds"; break;
		case spade: out << " of Spades"; break;
		case heart: out << " of Hearts"; break;
		case club: out << " of Clubs"; break;

	}
	return out;
}

class Deck {
public:
	//constructor
	Deck(); // initialize deck of 52 Cards;
	//Operations on the Deck
	void shuffle (); //randomly change order of Cards
	bool isEmpty (); //return true if deck is empty, false if not
	Card draw (); // return the next Card

protected:
	Card Cards[52]; // Hold Collection of Cards
	int topCard; // hold index one larger than next available Card
};

Deck::Deck ()
// initialize a deck by creating all 52 Cards
{
	topCard = 0;
	for (int i = 1; i <=13 ; i++) {
		Card c1(diamond, i), c2(spade, i), c3(heart, i), c4(club, i);
		Cards [topCard++] = c1;
		Cards [topCard++] = c2;
		Cards [topCard++] = c3;
		Cards [topCard++] = c4;
	}
}
class randomInteger {
public:
	unsigned int operator () (unsigned int);
};

randomInteger randomizer; //create global variable of type randomInteger
void Deck::shuffle ()
//randomly shuffle the Cards into an array
// using generic algorithm random shuffle
{
	random_shuffle (Cards, Cards+52, randomizer);
}



unsigned int randomInteger::operator () (unsigned int max)
{
	//rand return random integer
	//convert to unsigned to make positive
	//take remainder to put in range
	unsigned int rval = rand();
	return rval % max;
}

Card Deck::draw ()
// return one Card from the end of the deck
{
	if (! isEmpty())
		return Cards[--topCard];
	else { //otherwise return ace of spades (default)}
		Card spadeAce (spade, 1);
		return spadeAce;
		}
}

bool Deck:: isEmpty()
//return true if deck has no Cards
{ 
	return topCard <= 0;
}

class Player {
public:
	//constructor
	Player (Deck &);
	//operations
	Card draw();
	void addPoints (int);
	int Score ();
	void replaceCard (Deck &);
protected:
	Card myCards[3];
	int myScore;
	int removedCard;
};

Player::Player (Deck & aDeck)
//initialize the data fields for a player
{
	myScore = 0;
	for (int i = 0; i < 3; i++)
		myCards[i] = aDeck.draw();
	removedCard = 0;
}

Card Player::draw ()
//return a random Card from our hand
{
	removedCard = randomizer(3);
	return myCards[removedCard];
}

void Player::addPoints (int howMany)
//add the given number of points to the current Score
{
	myScore += howMany;
}

int Player::Score()
//return current Score
{
	return myScore;
}

void Player::replaceCard (Deck & aDeck)
//replace alst Card played with new Card
{
	myCards[removedCard] = aDeck.draw();
}

class HumanPlayer { 
	Card myCards[3];
	int myScore;
	int removedCard;

	public:
		HumanPlayer(Deck &);
		Card draw();
		void addPoints(int howMany) {myScore += howMany;}
		int Score() {return myScore;}
		void replaceCard (Deck &aDeck) { myCards [removedCard]= aDeck.draw();}
	};

HumanPlayer::HumanPlayer(Deck & aDeck)
{
	myScore = 0;
	for (int i = 0; i < 3; i++)
		myCards[i] = aDeck.draw();
	removedCard = 0;
}

Card HumanPlayer::draw ()

{
	cout <<"you currently hold in your hand:" << endl;
	cout <<"a) " << myCards[0] << endl;
	cout <<"b) " << myCards[1] << endl;
	cout <<"c) " << myCards[2] << endl;
	cout << " Which card do you want to play? ";
	char answer[80];
	removedCard = -1;
	while (removedCard == -1) {
		cin >> answer;
		if (answer[0] == 'a')
			removedCard = 0;
		else if (answer[0] == 'b')
			removedCard = 1;
		else if (answer[0] == 'c')
			removedCard = 2;
		if (removedCard != -1)
			return myCards[removedCard];
		cout << "please specify a b or c \n";		
	}
}


int main () {
	Deck theDeck; // create and shuffle deck
	theDeck.shuffle();

	HumanPlayer player1(theDeck); // create 2 players
	Player player2(theDeck);

	//play until deck is empty
	while (! theDeck.isEmpty() ) {
		Card Card1 = player1.draw();
		cout << " Player 1 plays " << Card1 << endl;
		Card Card2 = player2.draw();
		cout << "Player 2 plays " << Card2 << endl;

		if (Card1.rank == Card2.rank) { //tie
			player1.addPoints(1);
			player2.addPoints(1);
			cout << "players tie" << endl;
		}
		else if (Card1.rank > Card2.rank) {
			player1.addPoints(2);
			cout << "player 1 wins this round current score is "<< player1.Score() << endl;	
		}
		else {
			player2.addPoints(2);
			cout << "player 2 wins this round current score is " << player2.Score() << endl;			
		}
		//now replace Cards drawn
		player1.replaceCard(theDeck);
		player2.replaceCard(theDeck);


	}

	cout << "Total player 1 Score " << player1.Score() << endl;
	cout << "Total player 2 Score " << player2.Score() << endl;
	cout << " GAME OVER " << endl;
}