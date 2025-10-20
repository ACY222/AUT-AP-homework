#include "mocha.h"
#include "sub_ingredients.h"

namespace {
  void delete_side_items(std::vector<Ingredient*>& side_items) {
    for (auto& side_item : side_items) {
      delete side_item;
    }
    side_items.clear();
  }

  void deep_copy(std::vector<Ingredient*>& side_items,
                const std::vector<Ingredient*>& other) {
    delete_side_items(side_items);
    side_items.reserve(other.size());
    for (const auto& side_item : other) {
      side_items.push_back(side_item->clone());
    }
  }
}

Mocha::Mocha() : EspressoBased("Mocha") {
  ingredients.push_back(new Espresso(2));
  ingredients.push_back(new Milk(2));
  ingredients.push_back(new MilkFoam(1));
  ingredients.push_back(new Chocolate(1));
}

Mocha::Mocha(const Mocha& cap) : EspressoBased(cap) {
  name = cap.name;
  deep_copy(side_items, cap.side_items);
}

Mocha::~Mocha() {
  delete_side_items(side_items);
}

Mocha& Mocha::operator=(const Mocha& cap) {
  if (this == &cap) {
    return *this;
  }

  name = cap.name;
  deep_copy(side_items, cap.side_items);
  return *this;
}

std::string Mocha::get_name() const { return name; }

// ingredients' price + side_items' price
double Mocha::price() const {
  double ing_price = 0, side_price = 0;

  for (const auto& ing : ingredients) {
    ing_price += ing->price();
  }
  for (const auto& side_item : side_items) {
    side_price += side_item->price();
  }

  return ing_price + side_price;
}

void Mocha::add_side_item(Ingredient* side) {
  side_items.push_back(side);
}

std::vector<Ingredient*>& Mocha::get_side_items() {
  return side_items;
}
