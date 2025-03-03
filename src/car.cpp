#include <algorithm>
#include <ranges>

#include "car.hpp"

namespace RideShare
{
Car::Car(int destination) noexcept : m_destination{destination} {}

int Car::get_destination() const noexcept { return m_destination; }

bool Car::space_available() const noexcept { return m_seats.size() < CarUtils::MAX_SEATS; }

void Car::add_passenger(Passenger p) noexcept { m_seats.push_back(p); }

std::vector<Passenger> Car::drop_off(int station_number) noexcept {
  std::vector<Passenger> dropped_off{};
  auto arrive_lambda = [station_number](Passenger& p) -> bool { return p.get_destination() == station_number; };
  std::ranges::copy_if(m_seats, std::back_inserter(dropped_off), arrive_lambda);
  std::ranges::remove_if(m_seats, arrive_lambda);
  return dropped_off;
}

}  // namespace RideShare
