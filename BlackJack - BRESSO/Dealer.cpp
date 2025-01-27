#include "stdafx.h"

#ifndef Dealer_cpp
#define Dealer_cpp

#include "Deck.cpp"
#include "Hand.cpp"

namespace blackjack {

class Dealer {
  
  private: Deck deck;
  private: Hand hand;
  
  public: Card *getCard() {
    return deck.pop();
  }
  
  public: int deal() {
    if (hand.length() == 0) {
      hand.add(deck.pop());
      show();
      hand.add(deck.pop());
      //printf("X de Xxxxxx\n");
      return hit();
    } else {
      return -1;
    }
  }
  
  public: int hit() {
    while (hand.getValue() <= 17) {
      hand.add(deck.pop());
    }
    int i = hand.length() - 2;
    if (i == 0) {
      //printf("El dealer no pidio mas cartas\n");
    }
    if (i == 1) {
      //printf("El dealer pidio 1 carta mas\n");
    }
    if (i > 1) {
      //printf("El dealer pidio %i cartas mas\n", i);
    }
    return i;
  }
  
  public: int stand(int value) {
    int dValue = 21 - this->hand.getValue();
    int pValue = 21 - value;
    if (pValue > 0) {
      if (dValue > 0) {
        if (pValue < dValue) {
          return 1;
        }
        if (pValue > dValue) {
          return 0;
        }
        if (pValue == dValue) {
          return -1;
        }
      }
      if (dValue < 0) {
        return 1;
      }
      if (dValue == 0) {
        return 0;
      }
    }
    if (pValue < 0) {
      if (dValue > 0) {
        return 0;
      }
      if (dValue < 0) {
        pValue *= -1;
        dValue *= -1;
        if (pValue < dValue) {
          return 1;
        }
        if (pValue > dValue) {
          return 0;
        }
        if (pValue == dValue) {
          return -1;
        }
      }
      if (dValue == 0) {
        return 0;
      }
    }
    if (pValue == 0) {
      if (dValue > 0) {
        return 1;
      }
      if (dValue < 0) {
        return 1;
      }
      if (dValue == 0) {
        return -1;
      }  
    }
  }

  public: char *getStrDeck() {
    return deck.toString();
  }

  public: char *getStrHand() {
    return hand.toString();
  }
  
  public: void show() {
    //printf("Cartas del Dealer:\n");
    hand.show();
  }
  
};

}

#endif
