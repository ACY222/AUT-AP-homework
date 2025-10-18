#include "cappuccino.h"
#include "espresso_based.h"
#include "sub_ingredients.h"

Cappuccino::Cappuccino() {
  // add its default sub_ingredients
  ingredients.push_back(new Espresso(2));
  ingredients.push_back(new Milk(2));
  ingredients.push_back(new MilkFoam(1));
}

Cappuccino::Cappuccino(const Cappuccino& cap)
  : EspressoBased(cap), side_items(cap.side_items) {}

Cappuccino::~Cappuccino() {
  for (const auto& side : side_items) {
    delete side;
  }
  side_items.clear();
}

void Cappuccino::operator=(const Cappuccino& cap) {
  if (this == &cap) {
    return;
  }
  ingredients = cap.ingredients;
  side_items = cap.side_items;
  name = cap.name;
}

std::string Cappuccino::get_name() const {
  return name;
}

double Cappuccino::price() const {
  double price = 0;
  for (const auto& ingredient_ptr : ingredients) {
    price += ingredient_ptr->price();
  }
  for (const auto& ingredient_ptr : side_items) {
    price += ingredient_ptr->price();
  }
  return price;
}

void Cappuccino::add_side_item(Ingredient* side) {
  side_items.push_back(side);
}

std::vector<Ingredient*>& Cappuccino::get_side_items() {
  return side_items;
}
