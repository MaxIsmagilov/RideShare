#include "road.hpp"

namespace RideShare
{

Road::Road(int size) noexcept : m_stations{} {
  std::vector<int> indeces(size);
  std::iota(indeces.begin(), indeces.end(), 0);
  std::ranges::for_each(indeces, [&](int i) { m_stations.push_back(Station(i)); });
}

void Road::move(OUTPUT_TYPE output) noexcept {
  std::ranges::for_each(m_stations, [&](Station& s) { s.free_all(); });
  std::ranges::for_each(m_stations, [&](Station& s) { s.load_all(); });
  for (uint64_t i = 0; i < m_stations.size() - 1; ++i) {
    m_stations[i].transfer(m_stations[i + 1]);
    m_stations[i + 1].transfer(m_stations[i]);
  }
  std::ranges::for_each(m_stations, [&](const Station& s) {
    m_miles_travelled += s.num_cars();
    m_passenger_miles += s.passengers_loaded();
  });
  if (output != OUTPUT_TYPE::SUPPRESS) {
    std::cout << pass_info();
  }
  std::ranges::for_each(m_stations, [&](Station& s) { s.unload_all(); });
  std::ranges::for_each(m_stations, [&](Station& s) { s.clean_all(); });
  if (output == OUTPUT_TYPE::VERBOSE || output == OUTPUT_TYPE::EXCESSIVE) {
    std::cout << to_str();
  }
}

void Road::add_car(int pos, Car c) noexcept { m_stations[pos].add_car(c); }

void Road::add_waiting(int pos, int dest) noexcept {
  if (pos != dest) m_stations[pos].add_waiting(dest);
}

bool Road::is_done() const noexcept {
  bool empt = true;
  std::ranges::for_each(m_stations, [&](const Station& s) { empt = empt && s.is_empty(); });
  return empt;
}

std::string Road::pass_info() const noexcept {
  return "Total miles driven:    " + std::to_string(m_miles_travelled) +
         "\nTotal passenger-miles: " + std::to_string(m_passenger_miles) +
         "\nAverage passengers:    " + std::to_string(static_cast<double>(m_passenger_miles) / m_miles_travelled) +
         "\n";
}

std::string Road::to_str() const noexcept {
  std::string ret{"ROAD STATUS:\n"};
  std::ranges::for_each(m_stations, [&](const Station& s) { ret += s.to_str() + "\n"; });
  return ret;
}

Passenger Road::random_passenger(int len) noexcept {
  std::random_device                                       dev;
  std::mt19937                                             rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, len - 1);
  return Passenger(dist(rng));
}

Car Road::random_car(int len) noexcept {
  std::random_device                                       dev;
  std::mt19937                                             rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, len - 1);
  return Car(dist(rng));
}

}  // namespace RideShare