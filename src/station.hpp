#pragma once

#include <algorithm>
#include <ranges>
#include <tuple>
#include <vector>

#include "car.hpp"

namespace RideShare
{

/// @brief Class station manages cars
class Station
{
 public:
  /// @brief DELETED; force instatiation with a number
  Station() = delete;

  /// @brief Constructor for a station
  /// @param id the ID of the station
  Station(int id) noexcept;

  /// @brief Gets the ID of the station
  /// @return the ID
  int get_id() const noexcept;

  /// @brief locks all cars; prevents them from moving
  void lock_all() noexcept;

  /// @brief frees all cars and allows them to move
  void free_all() noexcept;

  /// @brief unloads all freed cars and returns passengers arrived at the correct destination.
  /// if the passenger is not at its destination but the car has arrived,
  /// @return a vector of the
  std::vector<Passenger> unload_all() noexcept;

  /// @brief transfers all possible cars (freed and in the right direction) to the next station
  /// @param other
  void transfer(Station& other) noexcept;

  /// @brief adds a car; default locked
  /// @param c a car to add
  void add_car(Car c) noexcept;

  /// @brief removes all cars that have arrived
  void clean_all() noexcept;

 private:
  enum class STATUS : int { FREED = 0, LOCKED = 1, MOVED = 2 };

  int m_id;

  std::vector<std::tuple<Car, STATUS>> m_cars;
  std::vector<Passenger>               m_waiting;
};

}  // namespace RideShare