#include "linked_list.hpp"

template class linked_list::LList<int>;

int main(int argc, char* argv[]){
  using namespace linked_list;
  {
    LList<int> l;
    l.push(1);
    l.push(2);
    l.pop();
  }

  return 0;
}
