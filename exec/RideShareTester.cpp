#include <iostream>

#include "car.hpp"
#include "station.hpp"

int main() {
  RideShare::Car c{3};

  c.add_passenger(2);
  c.add_passenger(1);
  c.add_passenger(3);

  RideShare::Station s{1};

  s.add_car(c);
  s.free_all();

  (void)s.unload_all();

  std::cout << s.to_str() << '\n';
}
