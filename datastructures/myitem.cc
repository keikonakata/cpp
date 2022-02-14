#include <iostream>
#include "myitem.hpp"

MyItem::MyItem(MyItem&& m) : data(m.data) {
  std::cout << "MyItem(&&): " << data  << std::endl;
}
MyItem::MyItem(const MyItem& m) : data(m.data) {
  std::cout << "MyItem(const&): " << data  << std::endl;
}
MyItem& MyItem::operator=(const MyItem& m) {
  data = m.data;
  std::cout << "MyItem=(const&): " << data  << std::endl;
  return *this;
}
MyItem& MyItem::operator=(MyItem&& m) {
  data = m.data;
  std::cout << "MyItem=(&&): " << data  << std::endl;
  return *this;
}
MyItem::MyItem(int _data) : data(_data) {
  std::cout << "MyItem " << data << " created." << std::endl;
}
MyItem::MyItem() {
  std::cout << "MyItem is created." << std::endl;
}
MyItem::~MyItem() {
  std::cout << "MyItem " << data << " deleted." << std::endl;
}

void MyItem::hello(){
  std::cout << "Hello@" << data << std::endl;
}
