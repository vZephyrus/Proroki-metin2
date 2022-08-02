#include "Card.h"

Card::Card(int number, bool color) {
  this->number = number;
  this->color = color;
}
Card::Card() {};

int Card::get_number() {
  return this->number;
}
bool Card::get_color() {
  return this->color;
}
void Card::delete_card() {
  this->number = 10;
}