#include <list>
using namespace std;

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



