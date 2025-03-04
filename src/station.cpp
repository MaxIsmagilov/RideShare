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
                             [&](Passenger& p) -> bool { return p.get_destination() == m_id; });
        std::ranges::copy_if(passengers, std::back_inserter(m_waiting),
                             [&](Passenger& p) -> bool { return p.get_destination() != m_id; });
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
  std::ranges::remove_if(m_cars, [](std::tuple<Car, STATUS>& t) -> bool { return std::get<1>(t) == STATUS::MOVED; });
}

void Station::add_car(Car c) noexcept { m_cars.push_back(std::make_tuple<Car, STATUS>(Car(c), STATUS::LOCKED)); }

void Station::clean_all() noexcept {
  std::ranges::remove_if(m_cars,
                         [&](std::tuple<Car, STATUS>& t) -> bool { return std::get<0>(t).get_destination() == m_id; });
}

}  // namespace RideShare