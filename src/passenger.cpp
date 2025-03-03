#include "passenger.hpp"

namespace RideShare
{

Passenger::Passenger(int destination) noexcept : m_destination{destination} {}

int Passenger::get_destination() const noexcept { return m_destination; }

}  // namespace RideShare