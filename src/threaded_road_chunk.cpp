#include "threaded_road_chunk.hpp"

namespace RideShare
{

ThreadedRoadChunk::ThreadedRoadChunk(int size, int id_start) noexcept : m_stations{}, m_size{size} {
  m_lock.lock();
  std::vector<int> indeces(size);
  std::iota(indeces.begin(), indeces.end(), id_start);
  std::ranges::for_each(indeces, [&](int i) { m_stations.push_back(Station(i)); });
  m_lock.unlock();
}

void ThreadedRoadChunk::move_unclean() noexcept {
  m_lock.lock();
  std::ranges::for_each(m_stations, [&](Station& s) { s.free_all(); });
  std::ranges::for_each(m_stations, [&](Station& s) { s.load_all(); });
  for (uint64_t i = 0; i < m_stations.size() - 1; ++i) {
    m_stations[i].transfer(m_stations[i + 1]);
    m_stations[i + 1].transfer(m_stations[i]);
  }
  m_lock.unlock();
}

void ThreadedRoadChunk::unload_and_clean() noexcept {
  m_lock.lock();
  std::ranges::for_each(m_stations, [](Station& s) { s.unload_all(); });
  std::ranges::for_each(m_stations, [](Station& s) { s.clean_all(); });
  m_lock.unlock();
}

void ThreadedRoadChunk::add_car(int pos, Car c) noexcept {
  m_lock.lock();
  m_stations[pos].add_car(c);
  m_lock.unlock();
}

void ThreadedRoadChunk::add_waiting(int pos, int dest) noexcept {
  m_lock.lock();
  if (pos != dest) m_stations[pos].add_waiting(dest);
  m_lock.unlock();
}

bool ThreadedRoadChunk::is_done() const noexcept {
  bool empt = true;
  std::ranges::for_each(m_stations, [&](const Station& s) { empt = empt && s.is_empty(); });
  return empt;
}

std::string ThreadedRoadChunk::pass_info() const noexcept {
  uint64_t miles_travelled{0}, passenger_miles{0};
  std::ranges::for_each(m_stations, [&](const Station& s) {
    miles_travelled += s.num_cars();
    passenger_miles += s.passengers_loaded();
  });
  return "Total miles driven:    " + std::to_string(miles_travelled) +
         "\nTotal passenger-miles: " + std::to_string(passenger_miles) +
         "\nAverage passengers:    " + std::to_string(static_cast<double>(passenger_miles) / miles_travelled) + "\n";
}

std::string ThreadedRoadChunk::to_str() const noexcept {
  std::string ret{"ROAD CHUNK STATUS:\n"};
  std::ranges::for_each(m_stations, [&ret](const Station& s) { ret += s.to_str() + "\n"; });
  return ret;
}

Station& ThreadedRoadChunk::left() noexcept { return std::forward<Station&>(m_stations.front()); }

Station& ThreadedRoadChunk::right() noexcept { return std::forward<Station&>(m_stations.back()); }

uint64_t ThreadedRoadChunk::car_count() const noexcept {
  uint64_t ct{0};
  std::ranges::for_each(m_stations, [&ct](const Station& s) { ct += s.num_cars(); });
  return ct;
}

uint64_t ThreadedRoadChunk::loaded_passenger_count() const noexcept {
  uint64_t ct{0};
  std::ranges::for_each(m_stations, [&ct](const Station& s) { ct += s.passengers_loaded(); });
  return ct;
}

int ThreadedRoadChunk::get_size() const noexcept { return m_size; }

}  // namespace RideShare
