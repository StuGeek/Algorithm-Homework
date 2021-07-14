template <typename T> class Queue {
public:
     Queue();   // construct an empty queue
      ~Queue(); // destructor
      Queue(const Queue &rhs);
      const Queue & operator = (const Queue &rhs);
      bool empty()const;
      bool full()const;
      int size()const;
      bool push(const T &x);//enqueue
      bool pop();//dequeue
      const T & front()const;//returns a reference to the front element
private:
 //using a static array of size 100.   

};

