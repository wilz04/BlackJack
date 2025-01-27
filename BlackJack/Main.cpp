#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blackjack/Dealer.cpp"
#include "blackjack/Player.cpp"

using namespace blackjack;

Dealer *dealer;
Player *player;
char *nick;
char *password;

void login() {
  if (player != NULL) {
    player->save();
    delete player;
  }
  printf("* Bienvenido a BlackJack *\n\n");
  if ((nick == NULL) || (password == NULL)) {
    nick = new char();
    printf("Digita tu Nick: ");
    scanf("%s", nick);
    password = new char();
    printf("Digita tu Password: ");
    scanf("%s", password);
  }
  player = new Player(nick, password);
  printf("\nTienes los siguientes comandos:\n");
  printf("-Login: Entrar al juego mediante un nombre de usuario y una contrasena\n");
  printf("-Bet: Apostar una cantidad de efectivo\n");
  printf("-Save: Guardar el juego\n");
  printf("-Exit: Salir del juego\n\n");
}

main () {
  player = NULL;
  nick = NULL;
  password = NULL;
  char *cmd = new char();
  int result;
  bool success = true;
  do {
    dealer = new Dealer();
    login();
    do {
      printf("->");
      scanf("%s", cmd);
      if (!strcmp(cmd, "Login")) {
        delete[] nick;
        delete[] password;
        nick = NULL;
        password = NULL;
        login();
      } else if (!strcmp(cmd, "Bet")) {
        scanf("%s", cmd);
        success = player->bet(atoi(cmd));
        if (success) {
          printf("Has habilitado el siguiente comando:\n");
          printf("-Deal: Iniciar el juego\n");
          printf("Has deshabilitado el comando 'Bet':\n");
        }
      } else if (!strcmp(cmd, "Deal")) {
        if (player->deal(dealer->getCard(), dealer->getCard())) {
          success = dealer->deal();
          if (success) {
            printf("Has habilitado los siguientes comandos:\n");
            printf("-Double: Doblar la apuesta\n");
            printf("-Stand: Permanecer con las cartas que tienes\n");
            printf("-Hit: Pedir una carta mas\n");
            printf("Has deshabilitado el comando 'Deal':\n");
          }
        } else {
          success = false;
        }
      } else if (!strcmp(cmd, "Double")) {
        success = player->bend(dealer->getCard());
        if (success) {
          strcpy(cmd, "Stand");
          break;
        }
      } else if (!strcmp(cmd, "Hit")) {
        success = player->hit(dealer->getCard());
        if (success) {
          printf("Has deshabilitado el comando 'Double':\n");
        }
      } else if (!strcmp(cmd, "Stand")) {
        success = player->stand();
        if (success) {
          break;
        }
      } else if (!strcmp(cmd, "Save")) {
        success = player->save();
      } else {
        success = false;
      }
      if (success) {
        printf("_ Comando terminado _\n\n");
      } else {
        printf("_ Comando no valido _\n\n");
      }
    } while (strcmp(cmd, "Exit"));
    player->save();
    if (!strcmp(cmd, "Stand")) {
      result = dealer->stand(player->getValue());
      dealer->show();
      if (result == 1) {
        printf("Has ganado $%i\n", player->getMoney(2));
      }
      if (result == -1) {
        printf("Has empatado\n", player->getMoney(1));
      }
      if (result == 0) {
        printf("Has perdido $%i\n", player->getMoney(-1));
      }
      printf("________________________________________________________________\n");
    }
    delete dealer;
  } while (strcmp(cmd, "Exit"));
}

