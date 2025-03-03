#include <iostream>

#include "car.hpp"

int main() {
  RideShare::Car c{3};

  c.add_passenger(RideShare::Passenger{5});
  c.add_passenger(RideShare::Passenger{2});
  c.add_passenger(RideShare::Passenger{2});

  auto q = c.drop_off(2);

  std::cout << "here\n";

  for (auto&& a : q) {
    std::cout << &a << '\n';
  }
}
