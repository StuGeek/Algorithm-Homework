typedef int Stack_entry;

class Stack {
  public:
    // Standard Stack methods
    Stack();
    bool empty() const;
    /* Returns true if the stack is empty, otherwise, returns false.
    */
    int size() const;
    /* Returns the number of elements in the stack.
    */
    void push(const Stack_entry &item);
    /*item is pushed into the stack and it becomes the new top element.
    */
    void pop();
    /*The top item is removed if the stack is not empty.
    Otherwise, nothing happens.
    */

     const Stack_entry & top() const;
    /* The top element is returned by item if the stack is not empty,
        and the stack remains unchanged.
        Nothing happens if the stack is empty.
    */
    // Safety features
    ~Stack();
    Stack(const Stack &original);
    void operator =(const Stack &original);
    private:
    //using a static array of size 100.   
};


