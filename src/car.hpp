#pragma once

#include <algorithm>
#include <ranges>
#include <vector>

#include "passenger.hpp"

namespace RideShare
{

namespace CarUtils
{

constexpr int MAX_SEATS = 3;

}  // namespace CarUtils

/// @brief Car is essentially a container for passengers
class Car
{
 public:
  /// @brief DELETED; make it required to set a destination
  Car() = delete;

  /// @brief constructor for Car
  /// @param destination
  Car(int destination) noexcept;

  /// @brief gets the destination of the car
  /// @return the destination
  int get_destination() const noexcept;

  /// @brief checks if there is space available left in the car
  /// @return whether or not the number of passengers exceeds the threshold
  bool space_available() const noexcept;

  /// @brief adds a passenger (moves it into the Car object)
  /// @param p a passenger
  void add_passenger(Passenger p) noexcept;

  /// @brief drops off all passengers
  /// @return a vector of all the passengers in the car
  std::vector<Passenger> drop_off() noexcept;

  /// @brief drops off all correct passengers.
  /// basically just removes all passengers with the correct station
  /// from the Car and returns them
  /// @param station_number
  /// @return a vector of passengers
  std::vector<Passenger> drop_off(int station_number) noexcept;

  /// @brief logs a move
  void log_move() noexcept;

  /// @brief gets the revenue
  /// @return the number of passenger-miles driven
  int get_revenue() noexcept;

  /// @brief gets the miles driven
  /// @return the miles driven
  int get_driven() noexcept;

  /// @brief gets the average revenue
  /// @return the average revenue in passengers
  double get_avg_revenue() noexcept;

 private:
  int                    m_destination;
  int                    passenger_miles{0};
  int                    miles_driven{0};
  std::vector<Passenger> m_seats;
};

}  // namespace RideShare
