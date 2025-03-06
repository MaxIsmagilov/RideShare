#pragma once

#include <iostream>
#include <numeric>
#include <random>

#include "car.hpp"
#include "passenger.hpp"
#include "station.hpp"

namespace RideShare
{

class Road
{
 public:
  enum class OUTPUT_TYPE : int { SUPPRESS, MINIMAL, VERBOSE, EXCESSIVE };

  Road() = delete;

  /// @brief constructor for class Road
  /// @param size the number of stations
  Road(int size) noexcept;

  /// @brief applies one iteration of the process
  /// @param output the type of output wanted
  void move(OUTPUT_TYPE output) noexcept;

  /// @brief adds a car to the road
  /// @param pos the station to start at
  /// @param c the car to add
  void add_car(int pos, Car c) noexcept;

  /// @brief adds a passenger waiting at a station
  /// @param pos the station to start at
  /// @param dest the station to try to get to
  void add_waiting(int pos, int dest) noexcept;

  /// @brief finds if there are no cars left
  /// @return if there are no cars left
  bool is_done() const noexcept;

  /// @brief describes the passenger information (miles, passenger-miles, avg)
  /// @return a string
  std::string pass_info() const noexcept;

  /// @brief string representation of the road
  /// @return a string
  std::string to_str() const noexcept;

  /// @brief clean all stations; removing unecessary cars
  void clean() noexcept;

  /// @brief gets the number of cars on the road
  /// @return an unsigned 64 bit int
  uint64_t car_count() const noexcept;

  /// @brief generates a random passenger
  /// @param len the maximum station
  /// @return a passenger
  static Passenger random_passenger(int len) noexcept;

  /// @brief generates a random car
  /// @param len the maximum station
  /// @return a car
  static Car random_car(int len) noexcept;

 private:
  std::vector<Station> m_stations{};

  uint64_t m_miles_travelled{0};
  uint64_t m_passenger_miles{0};
};

}  // namespace RideShare
