#ifndef CAPPUCCINO
#define CAPPUCCINO

#include "espresso_based.h"
#include "ingredient.h"
#include <string>
#include <vector>
class Cappuccino : public EspressoBased {
public:
  Cappuccino();
  Cappuccino(const Cappuccino& cap);
  virtual ~Cappuccino();
  void operator=(const Cappuccino& cap);

  virtual std::string get_name() const override;
  virtual double price() const override;

  void add_side_item(Ingredient* side);
  std::vector<Ingredient*>& get_side_items();

private:
  std::vector<Ingredient*> side_items;
};

#endif // CAPPUCCINO
