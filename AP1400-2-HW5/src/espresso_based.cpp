#include "espresso_based.h"
#include "ingredient.h"
#include <iostream>

void EspressoBased::brew() {
  for (const auto& ing_ptr : ingredients) {
    std::cout << "Add " << ing_ptr->get_name()
      << " for " << ing_ptr->get_units() << " units\n";
  }
}

std::vector<Ingredient*>& EspressoBased::get_ingredients() {
  return ingredients;
}

EspressoBased::~EspressoBased() {
  for (auto ing_ptr : ingredients) {
    delete ing_ptr;
  }
}

EspressoBased::EspressoBased() = default;

EspressoBased::EspressoBased(const EspressoBased& esp) {
  name = esp.name;
  for (const auto& ing_ptr : esp.ingredients) {
    ingredients.push_back(ing_ptr->clone());
  }
}

void EspressoBased::operator=(const EspressoBased& esp) {
  if (this == &esp) return;
  // clear this->ingredients
  for (auto ing_ptr : ingredients) {
    delete ing_ptr;
  }
  ingredients.clear();

  name = esp.name;
  for (const auto& ing_ptr : esp.ingredients) {
    ingredients.push_back(ing_ptr->clone());
  }
}
