#include "road.hpp"

namespace RideShare
{

Road::Road(int size) noexcept : m_stations{} {
  std::vector<int> indeces(size);
  std::iota(indeces.begin(), indeces.end(), 0);
  std::ranges::for_each(indeces, [&](int i) { m_stations.push_back(Station(i)); });
}

void Road::move(OUTPUT_TYPE output) noexcept {}

void Road::add_car(int pos, Car c) noexcept { m_stations[pos].add_car(c); }

void Road::add_waiting(int pos, int dest) noexcept { m_stations[pos].add_waiting(dest); }

}  // namespace RideShare