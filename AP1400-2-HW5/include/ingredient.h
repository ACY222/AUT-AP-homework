#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
public:
  double get_price_unit() const { return price_unit; }
  size_t get_units() const { return units; }
  // since the name of the ingredient is not known yet, make it a pure virtual
  // function. Actually, I do not believe this is a reason
  std::string get_name() const { return name; }

  double price() const { return price_unit * units; }

  virtual ~Ingredient() = default;
  virtual Ingredient* clone() = 0;

protected:
  Ingredient(double price_unit, size_t units)
    : price_unit(price_unit), units(units) {}

  double price_unit;
  size_t units;
  std::string name;
};

#endif // INGREDIENT_H
