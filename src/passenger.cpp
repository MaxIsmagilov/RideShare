#include "passenger.hpp"

namespace RideShare
{

Passenger::Passenger(int destination) : m_destination{destination} {}

int Passenger::get_destination() const { return m_destination; }

}  // namespace RideShare