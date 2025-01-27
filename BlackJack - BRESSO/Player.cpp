#include "stdafx.h"

#ifndef Player_cpp
#define Player_cpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hand.cpp"

namespace blackjack {

class Player {
  
  private: FILE *users;
  private: char *nick;
  private: char *password;
  private: int passive;
  private: int active;
  private: Hand hand;
  
  public: Player(char *nick, char *password) {
    try {
      users = fopen("Users.dat", "a+");
      bool exist = false;
      char *_nick = new char[STR_SIZE];
      char *_password = new char[STR_SIZE];
      char *_passive = new char[STR_SIZE];
      do {
        fscanf(users, "%s", _nick);
        fscanf(users, "%s", _password);
        fscanf(users, "%s", _passive);
        if (!strcmp(_nick, nick) && !strcmp(_password, password)) {
          exist = true;
          break;
        }
      } while (!feof(users));
      if (exist) {
        this->nick = _nick;
        this->password = _password;
        this->passive = atoi(_passive);
        this->active = 0;
      } else {
        fprintf(users, "%s ", nick);
        fprintf(users, "%s ", password);
        fprintf(users, "%s\n", "20000");
        this->nick = nick;
        this->password = password;
        this->passive = 20000;
        this->active = 0;
      }
      //printf("\n¡Tu capital es de $%i!\n", this->passive);
    } catch(int e) {
      exit(0);
    }
  }
  
  public: int getMoney(int result) {
    int active = this->active*result;
    if (result) {
      passive += active;
    }
    this->active = 0;
    if (active < 0) {
      active *= -1;
    }
    save();
    return active;
  }

  public: int getPassive() {
    return passive;
  }
  
  public: bool bet(int active) {
    if (!this->active && passive && (active > 0)) {
      if (active <= passive) {
        passive -= active;
        this->active = active;
      } else {
        this->active = passive;
        passive = 0;
      }
      save();
      //printf("¡Tu capital es de $%i!\n", passive);
      return true;
    } else {
      return false;
    }
  }
  
  public: bool deal(Card *one, Card *two) {
    if (active && !hand.length()) {
      hand.add(one);
      hand.add(two);
      show();
      return true;
    } else {
      return false;
    }
  }
  
  public: bool bend(Card *plus) {
    if ((hand.length() == 2) && (passive >= active)) {
      passive -= active;
      active *= 2;
      hit(plus);
      save();
      //printf("¡Tu capital es de $%i!\n\n", passive);
      return true;
    } else {
      return false;
    }
  }
  
  public: bool hit(Card *plus) {
    if (hand.length()) {
      hand.add(plus);
      show();
      return true;
    } else {
      return false;
    }
  }
  
  public: bool stand() {
    return hand.length();
  }
  
  public: int getValue() {
    return hand.getValue();
  }
  
  private: int intlen(int n) {
    int i = 0;
    while (n >= 1) {
      n /= 10;
      i++;
    }
    return i;
  }
  
  public: bool save() {
    try {
      rewind(users);
      char *nick = new char[STR_SIZE];
      char *password = new char[STR_SIZE];
      char *passive = new char[STR_SIZE];
      char *data = new char[256];
      data[0] = '\0';
      do {
        fscanf(users, "%s", nick);
        fscanf(users, "%s", password);
        fscanf(users, "%s", passive);
        if (!feof(users)) {
          if ((strcmp(nick, this->nick) || strcmp(password, this->password)) && (strcmp(passive, "0"))) {
            strcat(data, nick);
            strcat(data, " ");
            strcat(data, password);
            strcat(data, " ");
            strcat(data, passive);
            strcat(data, "\n");
          }
        }
      } while (!feof(users));
      fclose(users);
      remove("Users.dat");
      
      users = fopen("Users.dat", "a+");
      if (this->passive > 0) {
        fprintf(users, "%s ", this->nick);
        fprintf(users, "%s ", this->password);
        fprintf(users, "%s\n", gcvt(this->passive, intlen(this->passive), passive));
      }  
      fprintf(users, "%s", data);
      return true;
    } catch (int e) {
      return false;
    }
  }
  
  public: char *getStrHand() {
    return hand.toString();
  }

  private: void show() {
    //printf("Cartas de %s:\n", nick);
    hand.show();
  }
  
  public: ~Player() {
    fclose(users);
  }
  
};

}

#endif
