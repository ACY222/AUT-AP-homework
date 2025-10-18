#include "cappuccino.h"
#include "espresso_based.h"
#include "sub_ingredients.h"

Cappuccino::Cappuccino() {
  // add its default sub_ingredients
  ingredients.emplace_back(new Espresso(2));
  ingredients.emplace_back(new Milk(2));
  ingredients.emplace_back(new MilkFoam(1));
}

Cappuccino::Cappuccino(const Cappuccino& cap)
  : EspressoBased(cap), side_items(cap.side_items) {}

Cappuccino::~Cappuccino() {
  for (const auto& i : side_items) {
    delete i;
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

std::string Cappuccino::get_name() {
  return name;
}

double Cappuccino::price() {
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
