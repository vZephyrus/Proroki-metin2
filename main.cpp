#include "Card.h"
#include "Tools.cpp"
#include <iostream>
#include <vector>

using namespace std;

void init_cards(vector<Card> &vec);
void wydrukuj_karty(vector<Card> &vec, PLAYER prz);
void rozlosuj_karty(vector<Card> &vec);
bool czy_koniec(vector<Card> &vec_gracz, vector<Card> &vec_przeciwnik);

void ruch_gracza(int &karta_gracza_rzucona, vector<Card> &vec_gracz);
void ruch_przeciwnika(int &karta_przeciwnika_rzucona,
                      vector<Card> &vec_przeciwnik);

int main() {
  srand(time(NULL));
  system("clear");
  vector<Card> vec_gracz, vec_przeciwnik;
  init_cards(vec_gracz);

  init_cards(vec_przeciwnik);
  rozlosuj_karty(vec_przeciwnik);

  int karta_gracza_rzucona;
  int karta_przeciwnika_rzucona;

  int pkt_gracz = 0, pkt_przeciwnik = 0;
  int a = 0;

  if ((rand() % 2) == 0) {
    cout << "Zaczyna gracz : " << endl;
    while (true) {
      if (czy_koniec(vec_gracz, vec_przeciwnik)) {
        cout << "Wpisz liczbe aby zakonczyc gre :" << endl;
        cin >> a;
        break;
      }
      wydrukuj_karty(vec_gracz, PLAYER::GRACZ);
      cout << endl;
      wydrukuj_karty(vec_przeciwnik, PLAYER::PRZECIWNIK);
      ruch_gracza(karta_gracza_rzucona, vec_gracz);
      system("clear");
      ruch_przeciwnika(karta_przeciwnika_rzucona, vec_przeciwnik);
      if (karta_gracza_rzucona > karta_przeciwnika_rzucona) {
        pkt_gracz++;
        cout << "Twoja karta jest wieksza!";
      } else if (karta_gracza_rzucona < karta_przeciwnika_rzucona) {
        pkt_przeciwnik++;
        cout << "Karta przeciwnika jest wieksza";
      } else {
        cout << "Karty sa rowne!";
      }
      cout << "   Gracz pkt :" << pkt_gracz
           << ", Przeciwnik pkt :" << pkt_przeciwnik << endl;
    }
  } else {
    cout << "Zaczyna przeciwnik : " << endl;
    ruch_przeciwnika(karta_przeciwnika_rzucona, vec_przeciwnik);
    while (true) {
      if (czy_koniec(vec_gracz, vec_przeciwnik)) {
        cout << "Wpisz liczbe aby zakonczyc gre :" << endl;
        cin >> a;
        break;
      }

      wydrukuj_karty(vec_gracz, PLAYER::GRACZ);
      cout << endl;
      wydrukuj_karty(vec_przeciwnik, PLAYER::PRZECIWNIK);
      ruch_gracza(karta_gracza_rzucona, vec_gracz);
      system("clear");
      ruch_przeciwnika(karta_przeciwnika_rzucona, vec_przeciwnik);
      if (karta_gracza_rzucona > karta_przeciwnika_rzucona) {
        pkt_gracz++;
        cout << "Twoja karta jest wieksza!";
      } else if (karta_gracza_rzucona < karta_przeciwnika_rzucona) {
        pkt_przeciwnik++;
        cout << "Karta przeciwnika jest wieksza";
      } else {
        cout << "Karty sa rowne!";
      }
      cout << "   Twoje pkt :" << pkt_gracz
           << ", pkt przeciwnika :" << pkt_przeciwnik << endl;
    }
  }
}

void init_cards(vector<Card> &vec) {
  vec = {Card(0, 0), Card(1, 1), Card(2, 0), Card(3, 1), Card(4, 0),
         Card(5, 1), Card(6, 0), Card(7, 1), Card(8, 0)};
}
void wydrukuj_karty(vector<Card> &vec, PLAYER prz) {
  cout << "===========================" << endl;
  if (prz == PLAYER::GRACZ) {
    cout << "===> Twoja talia <===" << endl;
  } else if (prz == PLAYER::PRZECIWNIK) {
    cout << "===> Talia przeciwnika <===" << endl;
  }
  cout << "[Biale]    ";
  for (Card &card : vec) {
    if (card.get_number() == 10 && card.get_color()) {
      cout << "x"
           << ",";
    } else if (card.get_color()) {
      if (prz == PLAYER::GRACZ) {
        cout << card.get_number() << ",";
      } else if (prz == PLAYER::PRZECIWNIK) {
        cout << "_"
             << ",";
      }
    }
  }
  cout << endl;
  cout << "[Czarne]  ";
  for (Card &card : vec) {
    if (card.get_number() == 10 && !card.get_color()) {
      cout << "x"
           << ",";
    } else if (!card.get_color()) {
      if (prz == PLAYER::GRACZ) {
        cout << card.get_number() << ",";
      } else if (prz == PLAYER::PRZECIWNIK) {
        cout << "_"
             << ",";
      }
    }
  }
  cout << endl << "===========================" << endl;
}

void rozlosuj_karty(vector<Card> &vec) {
  int ilosc_razy = rand() % 20 + 30;
  int index_card;
  Card temp;

  for (int i = 0; i <= ilosc_razy; i++) {
    index_card = rand() % 9;

    temp = vec[index_card];
    vec.erase(vec.begin() + index_card);
    vec.push_back(temp);
  }
}

void ruch_gracza(int &karta_gracza_rzucona, vector<Card> &vec_gracz) {
  int index;
  bool find = false;

  while (true) {
    cout << "Podaj numer karty ktora chcesz uzyc :";
    try {
      cin >> index;
    } catch (...) {
      cout << "Nie poprawne dane" << endl;
    }
    for (int i = 0; i < 9; i++) {
      if (index == vec_gracz[i].get_number() &&
          vec_gracz[i].get_number() != 10) {
        find = true;
        break;
      }
    }
    if (find) {
      cout << "Wybrales karte : " << index << endl;
      karta_gracza_rzucona = index;
      vec_gracz[index].delete_card();
      break;
    } else {
      cout << "Nie posiadasz takiej karty" << endl;
    }
  }
}

void ruch_przeciwnika(int &karta_przeciwnika_rzucona,
                      vector<Card> &vec_przeciwnik) {
  int karta;
  bool find_number = false;
  while (true) {
    karta = rand() % 9;
    if (vec_przeciwnik[karta].get_number() != 10) {
      vec_przeciwnik[karta].delete_card();
      karta_przeciwnika_rzucona = karta;
      break;
    }
    for(int i = 0; i < 9; i++) { 
      if(vec_przeciwnik[i].get_number() != 10) {
        find_number = true;
        break;
      }
    }
    if(!find_number) {
      break;
    }
  }
}
bool czy_koniec(vector<Card> &vec_gracz, vector<Card> &vec_przeciwnik) {
  bool find_number1 = false;
  bool find_number2 = false;

  for (int i = 0; i < 9; i++) {
    if (vec_gracz[i].get_number() != 10) {
      find_number1 = true;
      break;
    }
  }

  for (int i = 0; i < 9; i++) {
    if (vec_przeciwnik[i].get_number() != 10) {
      find_number2 = true;
      break;
    }
  }
  if (!find_number1 && !find_number2) {
    return true;
  }
  return false;
}
