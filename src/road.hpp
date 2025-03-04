#pragma once

#include <numeric>

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

 private:
  std::vector<Station> m_stations{};

  int miles_travelled{0};
  int passenger_miles{0};
};

}  // namespace RideShare
