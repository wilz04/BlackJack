#include "stdafx.h"

#ifndef Deck_cpp
#define Deck_cpp

#include <time.h>
#include "Card.cpp"

namespace blackjack {

class Deck {
  
  private: Card *first;
  
  public: Deck() {
    first = NULL;
    srand(time(NULL));
    Card *temp;
    int i = 0;
    while (i < 52) {
      temp = new Card();
      if (!have(temp)) {
        add(temp);
        i++;
      }
    }
  }   
  
  private: bool have(Card *card) {
    bool result = false;
    Card *temp = first;
    while (temp != NULL) {
      if (card->eq(temp)) {
        result = true;
        break;
      }
      temp = temp->getNext();
    }
    return result;
  }
  
  private: void add(Card *card) {
    if (first == NULL) {
      first = card;
    } else {
      Card *temp = first;
      while (temp->getNext() != NULL) {
        temp = temp->getNext();
      }
      temp->setNext(card);
    }
  }
  
  public: Card *pop() {
    Card *temp = first;
    while (temp->getNext()->getNext() != NULL) {
      temp = temp->getNext();
    }
    Card *card = temp->getNext();
    temp->setNext(NULL);
    return card;
  }

  public: char *toString() {
    Card *temp = first;
    char *deck = new char[STR_SIZE*52];
    strcpy(deck, "\0");
    while (temp != NULL) {
      strcat(deck, temp->toString());
      strcat(deck, ",");
      temp = temp->getNext();
    }
    return deck;
  }
  
  public: void show() {
    Card *temp = first;
    while (temp != NULL) {
      temp->show();
      temp = temp->getNext();
    }
  }
  
};

}

#endif
