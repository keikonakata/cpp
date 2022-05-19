// queque based on a linked list

#include <memory>
#include <mutex>
#include <utility>

template <typename T>
class LinkedList {
private:
  struct Node {
    std::unique_ptr<Node> next;
    std::unique_ptr<T> data;
    Node(){}
    //Node(const T& _data): data(std::make_unique<T>(_data)) {}
    //Node(T&& _data): data(std::make_unique<T>(std::move(_data))) {}
  };
  std::unique_ptr<Node> head;
  Node* tail;
  std::mutex head_mutex;
  std::mutex tail_mutex;
  void push(std::unique_ptr<T> data){
    auto node = std::make_unique<Node>();
    std::unique_lock<std::mutex> tail_lock(tail_mutex);
    tail->next = std::move(node);
    tail->data = std::move(data);
  }
public:
  using value_t = T;
  LinkedList(): head(std::make_unique<Node>()), tail(head.get()) {}
  void push(const value_t& v){
    auto data = std::make_unique<T>(v);
    push(std::move(data));
  }
  void push(value_t&& v){
    auto data = std::make_unique<T>(std::move(v));
    push(std::move(data));
  }
  std::unique_ptr<value_t> pop(){
    std::unique_lock<std::mutex> head_lock(head_mutex);
    auto head_ptr = head.get();
    {
      std::unique_lock<std::mutex> tail_lock(tail_mutex);
      if (head_ptr == tail)
      return std::unique_ptr<T>();
    }
    auto ret = std::move(head->data);
    head = std::move(head->next);
    return ret;
  }
};
