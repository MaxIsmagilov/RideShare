#include "station.hpp"

namespace RideShare
{

Station::Station(int id) noexcept : m_id{id} {}

int Station::get_id() const noexcept { return m_id; }

void Station::lock_all() noexcept {
  std::ranges::for_each(m_cars, [](std::tuple<Car, STATUS>& t) { std::get<1>(t) = STATUS::LOCKED; });
}

void Station::free_all() noexcept {
  std::ranges::for_each(m_cars, [](std::tuple<Car, STATUS>& t) { std::get<1>(t) = STATUS::FREED; });
}

std::vector<Passenger> Station::unload_all() noexcept {
  std::vector<Passenger> unloading;
  std::ranges::for_each(m_cars, [&](std::tuple<Car, STATUS>& t) {
    // only do anything if the car is free
    if (std::get<1>(t) == STATUS::FREED) {
      auto& c = std::get<0>(t);
      // if the car has arrived drop off ALL passengers otherwise just those at their destination
      if (c.get_destination() == m_id) {
        auto passengers = c.drop_off();
        std::ranges::copy_if(passengers, std::back_inserter(unloading),
                             [&](const Passenger& p) -> bool { return p.get_destination() == m_id; });
        std::ranges::copy_if(passengers, std::back_inserter(m_waiting),
                             [&](const Passenger& p) -> bool { return p.get_destination() != m_id; });
      } else {
        std::ranges::copy(std::get<0>(t).drop_off(m_id), std::back_inserter(unloading));
      }
    }
  });
  return unloading;
}

void Station::transfer(Station& other) noexcept {
  std::ranges::for_each(m_cars, [&](std::tuple<Car, STATUS>& t) {
    if (std::get<1>(t) == STATUS::FREED) {
      auto dest = std::get<0>(t).get_destination();
      if (abs(m_id - dest) > abs(other.m_id - dest)) {
        other.add_car(std::get<0>(t));
        std::get<1>(t) = STATUS::MOVED;
      }
    }
  });
  auto rem = std::ranges::remove_if(
      m_cars, [](const std::tuple<Car, STATUS>& t) -> bool { return std::get<1>(t) == STATUS::MOVED; });
  m_cars.erase(rem.begin(), rem.end());
}

void Station::add_car(Car c) noexcept { m_cars.push_back(std::make_tuple<Car, STATUS>(Car(c), STATUS::LOCKED)); }

void Station::add_waiting(Passenger p) noexcept { m_waiting.push_back(p); }

void Station::clean_all() noexcept {
  auto rem = std::ranges::remove_if(
      m_cars, [&](const std::tuple<Car, STATUS>& t) -> bool { return std::get<0>(t).get_destination() == m_id; });
  m_cars.erase(rem.begin(), rem.end());
}

void Station::load_all() noexcept {
  auto direction = [&](int destination) -> int {
    if (destination > m_id)
      return 1;
    else if (destination < m_id)
      return -1;
    else
      return 0;
  };
  // assign in the remove statement copy to the cars and then remove
  auto rem = std::ranges::remove_if(m_waiting, [&](const Passenger& p) -> bool {
    if (p.get_destination() == m_id) {
      return true;
    }
    for (auto&& a : m_cars) {
      auto&& c = std::get<0>(a);
      if (c.space_available() && direction(c.get_destination()) == direction(p.get_destination())) {
        c.add_passenger(p);
        return true;
      }
    }
    return false;
  });
  m_waiting.erase(rem.begin(), rem.end());
}

std::string Station::to_str() const noexcept {
  std::string ret  = "Station_" + std::to_string(m_id) + "  {\n";
  auto        stat = [&](STATUS s) -> std::string {
    switch (s) {
      case STATUS::FREED:
        return "FREED";
      case STATUS::LOCKED:
        return "LOCKED";
      case STATUS::MOVED:
        return "MOVED";
      default:
        return "No status";
    }
  };
  ret += "CARS:\n";
  std::ranges::for_each(m_cars,
                        [&](auto& a) { ret += std::get<0>(a).to_str() + " <- " + stat(std::get<1>(a)) + "\n"; });
  ret += "WAITING:\n";
  std::ranges::for_each(m_waiting, [&](auto& a) { ret += a.to_str() + "\n"; });
  return ret + "}";
}

bool Station::is_empty() const noexcept { return (m_cars.size() == 0); }

int Station::passengers_loaded() const noexcept {
  int acc{0};
  std::ranges::for_each(m_cars, [&](const std::tuple<Car, STATUS>& t) { acc += std::get<0>(t).get_passenger_count(); });
  return acc;
}

int Station::num_cars() const noexcept { return static_cast<int>(m_cars.size()); }

}  // namespace RideShare