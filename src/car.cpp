#include "car.hpp"

#include <algorithm>

namespace RideShare
{

Car::Car(int destination) : m_destination{destination} {}

int Car::get_destination() const { return m_destination; }

bool Car::space_available() const { return m_seats.size() < CarUtils::MAX_SEATS; }

void Car::add_passenger(Passenger p) { m_seats.push_back(p); }

std::vector<Passenger> Car::drop_off(int station_number) {
  std::vector<Passenger> dropped_off{};
  auto arrive_lambda = [station_number](Passenger& p) -> bool { return p.get_destination() == station_number; };
  std::copy_if(m_seats.begin(), m_seats.end(), dropped_off.begin(), arrive_lambda);
  std::remove_if(m_seats.begin(), m_seats.end(), arrive_lambda);
  return dropped_off;
}

}  // namespace RideShare
