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
  auto arrive_lambda = [station_number](const Passenger& p) -> bool { return p.get_destination() == station_number; };
  auto rem           = std::ranges::remove_if(m_seats, arrive_lambda);
  std::ranges::copy(rem, std::back_inserter(dropped_off));
  m_seats.erase(rem.begin(), rem.end());
  return dropped_off;
}

int Car::get_passenger_count() const noexcept { return m_seats.size(); }

std::string Car::to_str() const noexcept {
  std::string res = "Car[ ";
  std::ranges::for_each(m_seats, [&](const Passenger& p) { res += p.to_str() + ","; });
  return res + " ]";
}

}  // namespace RideShare
