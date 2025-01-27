#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dealer.cpp"
#include "Player.cpp"

#pragma once

namespace blackjackbresso {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
  using namespace blackjack;

	public __gc class Form1 : public System::Windows::Forms::Form {	

    private: AxInterop::ShockwaveFlashObjects::AxShockwaveFlash* swf;
    private: System::ComponentModel::Container* components;
    private: Dealer* dealer;
    private: Player* player;
    private: char* nick;
    private: char* password;

	  public: Form1() {
		  InitializeComponent();

      dealer = new Dealer();
      player = NULL;
      nick = NULL;
      password = NULL;

      swf->SetVariable("sDeck", ctos(dealer->getStrDeck()));
	  }
    
	  protected: void Dispose(Boolean disposing) {
      if (player != NULL) {
        player->save();
      }

		  if (disposing && components) {
			  components->Dispose();
		  }
		  __super::Dispose(disposing);
	  }

		void InitializeComponent(void) {
      System::Resources::ResourceManager* resources = new System::Resources::ResourceManager(__typeof(blackjackbresso::Form1));
      this->swf = new AxInterop::ShockwaveFlashObjects::AxShockwaveFlash();
      (__try_cast<System::ComponentModel::ISupportInitialize* >(this->swf))->BeginInit();
      this->SuspendLayout();
      // 
      // swf
      // 
      this->swf->Dock = System::Windows::Forms::DockStyle::Fill;
      this->swf->Enabled = true;
      this->swf->Location = System::Drawing::Point(0, 0);
      this->swf->Name = S"swf";
      this->swf->OcxState = (__try_cast<System::Windows::Forms::AxHost::State* >(resources->GetObject(S"swf.OcxState")));
      this->swf->Size = System::Drawing::Size(802, 402);
      this->swf->TabIndex = 0;
      this->swf->FSCommand += new AxInterop::ShockwaveFlashObjects::_IShockwaveFlashEvents_FSCommandEventHandler(this, swf_FSCommand);
      // 
      // Form1
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(6, 13);
      this->ClientSize = System::Drawing::Size(802, 402);
      this->Controls->Add(this->swf);
      this->Font = new System::Drawing::Font(S"Verdana", 8);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
      this->Icon = (__try_cast<System::Drawing::Icon* >(resources->GetObject(S"$this.Icon")));
      this->MaximizeBox = false;
      this->Name = S"Form1";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = S"BlackJack - BRESSO";
      (__try_cast<System::ComponentModel::ISupportInitialize* >(this->swf))->EndInit();
      this->ResumeLayout(false);

    }	
  
    private: char* stoc(String* str) {
      char* newStr = new char[str->Length+1];
      for (int i=0; i<str->Length; i++) {
        newStr[i] = str->Chars[i];
      }
      newStr[i] = '\0';
      return newStr;
    }

    private: String* ctos(char* str) {
      return str;
    }

    private: void reset() {
      if (player != NULL) {
        delete dealer;
        dealer = new Dealer();
        player->save();
        delete player;
        swf->SetVariable("sDeck", ctos(dealer->getStrDeck()));
      }
      player = new Player(nick, password);
    }

    private: int login(char* data) {
      char* temp = new char[STR_SIZE];
      int j = 0;
      int k = 0;
      for (unsigned int i=0; i<=strlen(data); i++) {
        if (data[i] == ',') {
          temp[j] = '\0';
          nick = temp;
          temp = new char[STR_SIZE];
          j = 0;
        } else if (i == strlen(data)) {
          temp[j] = '\0';
          password = temp;
        } else {
          temp[j] = data[i];
          j++;
        }
      }
      reset();
      return player->getPassive();
    }

    private: System::Void swf_FSCommand(System::Object* sender, AxInterop::ShockwaveFlashObjects::_IShockwaveFlashEvents_FSCommandEvent* e) {
      int result;
      bool success = true;
      if (e->command->Equals("Login")) {
        swf->SetVariable("passive", login(stoc(e->args)).ToString());
      } else if (e->command->Equals("Bet")) {
        success = player->bet(atoi(stoc(e->args)));
      } else if (e->command->Equals("Deal")) {
        if (player->deal(dealer->getCard(), dealer->getCard())) {
          int hits = dealer->deal();
          if (hits == -1) {
            success = false;
          } else {
            swf->SetVariable("hits", hits.ToString());
            success = true;
          }
        } else {
          success = false;
        }
      } else if (e->command->Equals("Double")) {
        success = player->bend(dealer->getCard());
        swf->SetVariable("passive", player->getPassive().ToString());
      } else if (e->command->Equals("Hit")) {
        success = player->hit(dealer->getCard());
      } else if (e->command->Equals("Save")) {
        success = player->save();
      } else if (e->command->Equals("Exit")) {
        success = player->save();
        Close();
        exit(0);
      } else {
        success = false;
      }
      if (e->command->Equals("Stand")) {
        success = player->stand();
        if (success) {
          result = dealer->stand(player->getValue());
          dealer->show();
          char* msg = new char[STR_SIZE*2];
          if (result == 1) {
            //printf("Has ganado $%i\n", player->getMoney(2));
            strcpy(msg, "Has ganado $");
            strcat(msg, stoc(player->getMoney(2).ToString()));
          }
          if (result == -1) {
            //printf("Has empatado\n", player->getMoney(1));
            player->getMoney(1);
            strcpy(msg, "Has empatado");
          }
          if (result == 0) {
            //printf("Has perdido $%i\n", player->getMoney(-1));
            strcpy(msg, "Has perdido $");
            strcat(msg, stoc(player->getMoney(-1).ToString()));
          }
          swf->SetVariable("passive", player->getPassive().ToString());
          swf->SetVariable("msg", ctos(msg));
          reset();
        }
      }
    }

  };

}
