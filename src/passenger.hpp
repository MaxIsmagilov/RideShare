#pragma once

#include <string>

namespace RideShare
{

/// @brief Passenger manages one passenger. This passenger has a station that it wants to go to
class Passenger
{
 public:
  /// @brief DELETED; force construction with a destination
  Passenger() = delete;

  /// @brief constructor for Passenger
  /// @param destination
  Passenger(int destination) noexcept;

  /// @brief gets the destination for the passenger
  /// @return the intended destination
  int get_destination() const noexcept;

  /// @brief string representation of the passenger
  /// @return the address and the destination
  std::string to_str() const noexcept;

 private:
  int m_destination;
};
}  // namespace RideShare