#ifndef MYITEM_HPP_INCLUDED
#define MYITEM_HPP_INCLUDED

class MyItem {
  int data;
public:
  MyItem(MyItem&&);
  MyItem(const MyItem&);
  MyItem& operator=(const MyItem&);
  MyItem& operator=(MyItem&&);
  MyItem(int);
  MyItem();
  ~MyItem();
  void hello();
};

#endif /* MYITEM_HPP_INCLUDED */
