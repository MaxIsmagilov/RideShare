#include "threaded_road.hpp"

namespace RideShare
{

ThreadedRoad::ThreadedRoad(int size, int thread_count) noexcept : m_thread_count{thread_count}, m_chunks{} {
  if (thread_count < size) m_thread_count = 1;
  std::vector<int> positions{};
  int              slice_len = size / thread_count;
  for (int i = 0; i < size && positions.size() < thread_count; ++i) {
    if (i % slice_len == 0) positions.push_back(i);
  }
  for (int i = 0; i < positions.size() - 1; ++i) {
    m_chunks.push_back(std::make_shared<ThreadedRoadChunk>(slice_len, positions[i]));
  }
  m_chunks.push_back(std::make_shared<ThreadedRoadChunk>(slice_len + (size % slice_len), positions.back()));
}

void ThreadedRoad::move() noexcept {
  ThreadPool                     t;
  std::vector<std::future<void>> results;
  std::ranges::for_each(m_chunks, [&](auto&& trc) { results.push_back(t.queue([&trc]() { trc->move_unclean(); })); });
  t.go(m_thread_count);
  std::ranges::for_each(results, [&](std::future<void>& f) { (void)f.get(); });
  for (int i = 0; i < m_chunks.size() - 1; ++i) {
    m_chunks[i]->right().transfer(m_chunks[i + 1]->left());
    m_chunks[i + 1]->left().transfer(m_chunks[i]->right());
  }
  t.abort();
  results.clear();
  std::ranges::for_each(m_chunks,
                        [&](auto&& trc) { results.push_back(t.queue([&trc]() { trc->unload_and_clean(); })); });
  t.go(m_thread_count);
  std::ranges::for_each(results, [&](std::future<void>& f) { (void)f.get(); });
}

void ThreadedRoad::add_car(int pos, Car cr) noexcept {
  int cur_pos = pos;
  for (auto&& c : m_chunks) {
    if (c->get_size() < cur_pos)
      c->add_car(cur_pos, cr);
    else
      cur_pos -= c->get_size();
  }
}

void ThreadedRoad::add_waiting(int pos, int dest) noexcept {
  int cur_pos = pos;
  for (auto&& c : m_chunks) {
    if (c->get_size() < cur_pos)
      c->add_waiting(cur_pos, dest);
    else
      cur_pos -= c->get_size();
  }
}

bool ThreadedRoad::is_done() const noexcept {
  bool done = true;
  std::ranges::for_each(m_chunks, [&done](const auto& c) { done = done && c->is_done(); });
  return done;
}

std::string ThreadedRoad::pass_info() const noexcept {
  return "Total miles driven:    " + std::to_string(m_miles_travelled) +
         "\nTotal passenger-miles: " + std::to_string(m_passenger_miles) +
         "\nAverage passengers:    " + std::to_string(static_cast<double>(m_passenger_miles) / m_miles_travelled) +
         "\n";
}

std::string ThreadedRoad::to_str() const noexcept {
  std::string ret{"ROAD STATUS:\n"};
  std::ranges::for_each(m_chunks, [&ret](const auto& s) { ret += s->to_str(); });
  return ret + "\n";
}

void ThreadedRoad::clean() noexcept {
  std::ranges::for_each(m_chunks, [](auto&& s) { s->unload_and_clean(); });
}

uint64_t ThreadedRoad::car_count() const noexcept {
  uint64_t sum{0};
  std::ranges::for_each(m_chunks, [&sum](const auto& s) { sum += s->car_count(); });
  return sum;
}

}  // namespace RideShare