#include <algorithm>
#include <ranges>

#include "car.hpp"

namespace RideShare
{

Car::Car(int destination) noexcept : m_destination{destination} {}

int Car::get_destination() const noexcept { return m_destination; }

bool Car::space_available() const noexcept { return m_seats.size() < CarUtils::MAX_SEATS; }

void Car::add_passenger(Passenger p) noexcept { m_seats.push_back(p); }

std::vector<Passenger> Car::drop_off() noexcept {
  std::vector<Passenger> dropped_off;
  std::ranges::copy(m_seats, std::back_inserter(dropped_off));
  m_seats.clear();
  return dropped_off;
}

std::vector<Passenger> Car::drop_off(int station_number) noexcept {
  std::vector<Passenger> dropped_off{};
  auto arrive_lambda = [station_number](Passenger& p) -> bool { return p.get_destination() == station_number; };
  std::ranges::copy_if(m_seats, std::back_inserter(dropped_off), arrive_lambda);
  std::ranges::remove_if(m_seats, arrive_lambda);
  return dropped_off;
}

void Car::log_move() noexcept { passenger_miles += static_cast<int>(m_seats.size()); }

int Car::get_revenue() noexcept { return passenger_miles; }

int Car::get_driven() noexcept { return miles_driven; }

double Car::get_avg_revenue() noexcept { return static_cast<double>(passenger_miles) / miles_driven; }

}  // namespace RideShare
