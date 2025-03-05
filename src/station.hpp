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

  /// @brief adds a passenger to wait
  /// @param p the passenger
  void add_waiting(Passenger p) noexcept;

  /// @brief removes all cars that have arrived
  void clean_all() noexcept;

  /// @brief assigns passengers to new cars
  void load_all() noexcept;

  /// @brief string representation of the station
  /// @return
  std::string to_str() const noexcept;

  /// @brief checks if the station has no cars
  /// @return whether cars are present
  bool is_empty() const noexcept;

  /// @brief gets the number of passengers loaded in all the cars
  /// @return an integer count
  int passengers_loaded() const noexcept;

  /// @brief gets the number of cars
  /// @return an integer count
  int num_cars() const noexcept;

 private:
  enum class STATUS : int { FREED = 0, LOCKED = 1, MOVED = 2 };

  int m_id{};

  std::vector<std::tuple<Car, STATUS>> m_cars;
  std::vector<Passenger>               m_waiting;
};

}  // namespace RideShare