#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H

#include <vector>
#include <string>
#include "ingredient.h"

class EspressoBased {
public:
  virtual std::string get_name() const = 0;
  virtual double price() const = 0;

  void brew() const;
  std::vector<Ingredient*>& get_ingredients();

  virtual ~EspressoBased() = default;

protected:
  EspressoBased();
  EspressoBased(std::string name);
  EspressoBased(const EspressoBased& esp);
  EspressoBased& operator=(const EspressoBased& esp);

  std::vector<Ingredient*> ingredients;
  std::string name;
};

#endif // ESPRESSO_BASED_H
