#ifndef Card_cpp
#define Card_cpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace blackjack {

class Card {
  
  private: int value;
  private: char *caption;
  private: char *type;
  private: Card *next;
  
  public: Card() {
    caption = toCaption(rand()%13);
    value = toValue(caption);
    type = toType(rand()%4);
    next = NULL;
  }
  
  public: char *getCaption() {
    return caption;
  }
  
  public: int getValue() {
    return value;
  }
  
  public: char *getType() {
    return type;
  }
  
  public: void setNext(Card *next) {
    this->next = next;
  }
  
  public: Card *getNext() {
    return next;
  }
  
  private: char *toCaption(int value) {
    char *captions[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    return captions[value];
  }
  
  private: int toValue(char *caption) {
    char *captions[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int i;
    for (i=0; i<9; i++) {
      if (!strcmp(captions[i], caption)) {
        break;
      }
    }
    return ++i;
  }
  
  private: char *toType(int n) {
    char *types[] = {"Oros", "Copas", "Espadas", "Bastos"};
    return types[n];
  }
  
  public: bool eq(Card *card) {
    return (caption == card->getCaption()) && (!strcmp(type, card->getType()));
  }
  
  public: void show() {
    //printf("%s de %s\n", caption, type);
  }
  
};

}

#endif
