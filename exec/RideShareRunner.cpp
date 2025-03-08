#include <iostream>

#include "car.hpp"
#include "road.hpp"
#include "station.hpp"
#include "threaded_road.hpp"

int main() {
  constexpr uint64_t STATIONS               = 100;
  constexpr uint64_t CARS_PER_STATION       = 100;
  constexpr uint64_t PASSENGERS_PER_STATION = 100;

  std::cout << "Initiallizing Road\n";

  RideShare::ThreadedRoad r{STATIONS, 6};

  std::random_device                                       dev;
  std::mt19937                                             rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, STATIONS - 1);

  std::cout << "Populating Cars\n";

  for (uint64_t i = 0; i < STATIONS * CARS_PER_STATION; ++i) r.add_car(dist(rng), RideShare::Car(dist(rng)));

  std::cout << "Populating Passengers\n";

  for (uint64_t i = 0; i < STATIONS * PASSENGERS_PER_STATION; ++i) r.add_waiting(dist(rng), dist(rng));

  std::cout << "Cleaning Stations\n";

  r.clean();

  std::cout << "Beginning Simulation\n";

  for (uint64_t i = 0; !r.is_done(); ++i) {
    std::cout << "\titeration=" << i + 1 << "\t(with " << r.car_count() << " cars)\n";
    r.move();
  }

  std::cout << "Simulation Done\n\nInfo:\n";

  std::cout << r.pass_info();
}
