#pragma once

#include <memory>

#include "thread_pool.hpp"
#include "threaded_road_chunk.hpp"

namespace RideShare
{

class ThreadedRoad
{
 public:
  /// @brief constructor for class Road
  /// @param size the number of stations
  ThreadedRoad(int size, int thread_count) noexcept;

  /// @brief applies one iteration of the process
  void move() noexcept;

  /// @brief adds a car to the road
  /// @param pos the station to start at
  /// @param c the car to add
  void add_car(int pos, Car cr) noexcept;

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

 private:
  std::vector<std::shared_ptr<ThreadedRoadChunk>> m_chunks{};
  uint64_t                                        m_miles_travelled{0};
  uint64_t                                        m_passenger_miles{0};
  int                                             m_thread_count;
};

}  // namespace RideShare
