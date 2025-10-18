#include "espresso_based.h"
#include <algorithm>
#include <iostream>

void EspressoBased::brew() {
  for (const auto& ingredient_ptr : ingredients) {
    std::cout << "Add " << ingredient_ptr->get_name()
      << " for " << ingredient_ptr->get_units() << " units\n";
  }
}

std::vector<Ingredient*>& EspressoBased::get_ingredients() {
  return ingredients;
}

EspressoBased::~EspressoBased() {
  for (const auto ingredient_ptr : ingredients) {
    delete ingredient_ptr;
  }
}

EspressoBased::EspressoBased() = default;

EspressoBased::EspressoBased(const EspressoBased& esp) {
  std::copy(esp.ingredients.begin(), esp.ingredients.end(), ingredients.begin());
  name = esp.name;
}

void EspressoBased::operator=(const EspressoBased& esp) {
  if (this == &esp) {
    return;
  }
  name = esp.name;
  std::copy(esp.ingredients.begin(), esp.ingredients.end(), ingredients.begin());
}
