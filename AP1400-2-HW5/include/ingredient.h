#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
public:
  // return the price per unit
  double get_price_unit() const { return price_unit; }
  // show how many of this ingredient is needed
  size_t get_units() const { return units; }
  // make get_name() a pure virtual function and so the class an abstract class
  // the name of the ingredients, like Milk
  virtual std::string get_name() const = 0;
  double price() { return price_unit * units; }
  virtual ~Ingredient() = default;

protected:
  // the following members are accessible for Ingredient and its subclass
  Ingredient(double price_unit, size_t units)
    : price_unit(price_unit), units(units) {}

  double price_unit;
  size_t units;
  std::string name;
};

#endif // INGREDIENT_H
