#include <iostream>
#include <vector>
#include "espresso_based.h"

namespace {
  void delete_all_elements(std::vector<Ingredient*>& ingredients) {
    for (auto& ing : ingredients) {
      delete ing;
    }
  }

  void deep_copy(std::vector<Ingredient*>& ingredients,
                 const std::vector<Ingredient*>& other) {
    ingredients.reserve(other.size());
    for (const auto& ing : other) {
      ingredients.push_back(ing->clone());
    }
  }
}

std::string EspressoBased::get_name() const { return name; }

void EspressoBased::brew() const {
  std::cout << "We are brewing " << get_name() << "\n";
  for (const auto& ing : ingredients) {
    std::cout << "    Adding " << ing->get_units() << " units "
      << ing->get_name() << "\n";
  }
  std::cout << "Finish!\n";
}

std::vector<Ingredient*>& EspressoBased::get_ingredients() {
  return ingredients;
}

EspressoBased::EspressoBased() {}

EspressoBased::EspressoBased(std::string name) : name(name) {}

EspressoBased::EspressoBased(const EspressoBased& esp) {
  name = esp.name;
  // deep copy
  deep_copy(ingredients, esp.ingredients);
}

EspressoBased& EspressoBased::operator=(const EspressoBased& esp) {
  if (this == &esp) {
    return *this;
  }

  name = esp.name;
  delete_all_elements(ingredients);
  deep_copy(ingredients, esp.ingredients);
  return *this;
}
