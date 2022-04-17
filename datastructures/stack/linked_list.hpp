#ifndef CSTACK_HPP_INCLUDED
#define CSTACK_HPP_INCLUDED

#include <condition_variable>
#include <exception>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>

namespace linked_list {

  template <typename T>
  class LList {
    struct Item {
      using next_ptr = std::unique_ptr<Item>;
      T data;
      next_ptr next;
      Item(const T& _data, next_ptr _next) : data(_data), next(std::move(_next)) {};
      Item(T&& _data, next_ptr _next) : data(std::move(_data)), next(std::move(_next)) {};
      Item(const T& _data) : data(_data), next(nullptr) {}
    };
    std::unique_ptr<Item> head;
    mutable std::mutex m;
    std::condition_variable cv;
  public:
    LList() : head(nullptr) {}
    ~LList() {
      while (head) {
	head = std::move(head->next);
      }
    }
    void push(const T& v) {
      // Create a new node before acquiring the lock
      auto new_head = std::make_unique<Item>(v);
      const std::lock_guard<std::mutex> lock(m);
      // These assignments are noexcept
      new_head->next = std::move(head);
      head = std::move(new_head);
      cv.notify_one();
    }
    std::unique_ptr<T> pop() {
      const std::lock_guard<std::mutex> lock(m);
      if (!head)
	return nullptr;
      auto ret = std::unique_ptr<T>(new T{head->data});
      head = std::move(head->next);
      return ret;
    }
    bool pop(T& ret) {
      const std::lock_guard<std::mutex> lock(m);
      if (!head)
	return false;
      ret = head->data;
      head = std::move(head->next);
      return true;
    }
    void pop_await(T& ret) {
      std::unique_lock<std::mutex> lock(m);
      cv.wait(lock, [this]{return head != nullptr;});
      ret = head->data;
      head = std::move(head->next);
    }
    std::unique_ptr<T> pop_await() {
      std::unique_lock<std::mutex> lock(m);
      cv.wait(lock, [this]{return head != nullptr;});
      auto ret = std::unique_ptr<T>(new T{head->data});
      head = std::move(head->next);
      return ret;
    }
  };

} /* namespace cstack */

#endif /* CSTACK_HPP_INCLUDED */
