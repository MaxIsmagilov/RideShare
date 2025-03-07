#pragma once

#include <shared_mutex>

#include "road.hpp"
#include "thread_pool.hpp"

namespace RideShare
{

class ThreadedRoadChunk
{
 public:
  ThreadedRoadChunk() = delete;

  /// @brief constructor for class Road
  /// @param size the number of stations
  ThreadedRoadChunk(int size, int id_start) noexcept;

  /// @brief applies one iteration of the process
  void move_unclean() noexcept;

  /// @brief unloads all passengers and deletes arrived cars
  /// @note this is split off to allow for multithreading and better communication
  /// between edge stations
  void unload_and_clean() noexcept;

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

  /// @brief gets the leftmost station
  /// @return a reference to the station
  Station& left() noexcept;

  /// @brief gets the rightmost station
  /// @return a reference to the station
  Station& right() noexcept;

  /// @brief gets the number of cars on the road
  /// @return an unsigned 64 bit int
  uint64_t car_count() const noexcept;

  /// @brief gets the number of loaded passengers
  /// @return an unsigned 64 bit int
  uint64_t loaded_passenger_count() const noexcept;

  /// @brief gets the size of the chunk
  /// @return an int
  int get_size() const noexcept;

 private:
  std::vector<Station> m_stations{};
  std::shared_mutex    m_lock;
  int                  m_size;
};

}  // namespace RideShare