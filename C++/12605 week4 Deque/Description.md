# week4 Deque

Deque is an ADT which allows insertions and deletions on both sides of a sequence of objects.
Implement the following class Dequeue using inheritance:

```
typedef int T;
class Deque : private list<T>{
public:
   Deque():list<T>(){};
   bool empty() const;
   int size()const;
   void pop_front();
   void pop_rear();
   void push_front(const T &item);
   void push_rear(const T &item);
   const T & front() const;
   const T & rear() const;
   T & front() ;
   T & rear() ;
};

```


请提交你的外部实现，不包含以上定义。
