#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"

#define DEFCLASS(ing_name, price_unit)                        \
  class ing_name : public Ingredient {                        \
  public:                                                     \
    ing_name(size_t units) : Ingredient{price_unit, units} {  \
      this->name = #ing_name;                                 \
    }                                                         \
    virtual Ingredient* clone() override {                    \
      return new ing_name(*this);                             \
    }                                                         \
  };

DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);

#endif // SUB_INGREDIENTS_H
