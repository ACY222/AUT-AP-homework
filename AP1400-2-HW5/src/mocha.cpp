#include "mocha.h"
#include "espresso_based.h"
#include "sub_ingredients.h"

Mocha::Mocha() {
  // add its default sub_ingredients
  ingredients.push_back(new Espresso(2));
  ingredients.push_back(new Milk(2));
  ingredients.push_back(new MilkFoam(1));
  ingredients.push_back(new Chocolate(1));
}

Mocha::Mocha(const Mocha& cap)
  : EspressoBased(cap), side_items(cap.side_items) {}

Mocha::~Mocha() {
  for (const auto& side : side_items) {
    delete side;
  }
  side_items.clear();
}

void Mocha::operator=(const Mocha& cap) {
  if (this == &cap) {
    return;
  }
  ingredients = cap.ingredients;
  side_items = cap.side_items;
  name = cap.name;
}

std::string Mocha::get_name() const {
  return name;
}

double Mocha::price() const {
  double price = 0;
  for (const auto& ingredient_ptr : ingredients) {
    price += ingredient_ptr->price();
  }
  for (const auto& ingredient_ptr : side_items) {
    price += ingredient_ptr->price();
  }
  return price;
}

void Mocha::add_side_item(Ingredient* side) {
  side_items.push_back(side);
}

std::vector<Ingredient*>& Mocha::get_side_items() {
  return side_items;
}
