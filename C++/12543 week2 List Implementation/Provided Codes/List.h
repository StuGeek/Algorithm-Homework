template <typename T>
class List {
 public:
 struct Node {
       T data;
        Node *next;
       Node(const T & x, Node * p =NULL):data(x),next(p){ };
    };

   typedef Node* Ptr;
//  methods of the List ADT
   List();//construct an empty list
   ~List();
   List(const List &l);
   const List & operator=(const List &l); 
   int size() const{return theSize;};
   bool empty() const{return (theSize==0);};
   void clear();
   Ptr find( T &x) const; //find the first occurrence of x and returns a pointer that points to the node if search is successful, returns NULL otherwise.

   Ptr insert(Ptr position, const T &x);
  //inserts x at position and returns a pointer to the inserted node.
   void push_front(const T &x);//put x before the first item
   void push_back(const T &x);//put x after the last item 
   T & front(); // returns the reference to the first node if it is not empty
   T & back();//returns the reference to the last  node if it is not empty

   Ptr begin(){return head;};
   Ptr end(){return NULL;};
   void traverse(void (*visit)(T &));
   Ptr advance(Ptr p); // move the pointer to the next position
    Ptr erase(Ptr position);

    //it removes the node at postion and returns the position of the successor of the reomoved node.
private:
  Ptr head;
  int theSize;
};