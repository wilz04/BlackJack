#ifndef Hand_cpp
#define Hand_cpp

#include "Card.cpp"

namespace blackjack {

class Hand {
  
  private: Card *first;
  
  public: Hand() {
    first = NULL;
  }
  
  public: int getValue() {
    Card *temp = first;
    int i = 0;
    while (temp != NULL) {
      i += temp->getValue();
      temp = temp->getNext();
    }
    temp = first;
    while ((i <= 11) && (temp != NULL)) {
      while (temp != NULL) {
        if (!strcmp(temp->getCaption(), "A")) {
          i += 10;
          break;
        }
        temp = temp->getNext();
      }
    }
    return i;
  }
  
  public: void add(Card *card) {
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
  
  public: int length() {
    Card *temp = first;
    int i = 0;
    while (temp != NULL) {
      i++;
      temp = temp->getNext();
    }
    return i;
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
