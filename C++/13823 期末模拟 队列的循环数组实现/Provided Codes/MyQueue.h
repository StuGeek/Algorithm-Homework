template <typename T> class Queue {
public:
	Queue(){
		front = 0;
		rear = 0;
	}

	~Queue(){}

	Queue(const Queue &rhs){
		front = rhs.front;
		rear = rhs.rear;
		int i = front;
		while (i != rear){
			arr[i] = rhs.arr[i];
			i = (i + 1) % 100;
		}
	}

	const Queue & operator = (const Queue &rhs){
		front = rhs.front;
		rear = rhs.rear;
		int i = front;
		while (i != rear){
			arr[i] = rhs.arr[i];
			i = (i + 1) % 100;
		}
	}

	bool empty()const{
		return front == rear;
	}

	bool full()const{
		return front == (rear + 1) % 100;
	}

	int size()const{
		return (rear + 100 - front) % 100;
	}

	bool push(const T &x){
		if (full()) return false;
		else{
			arr[rear] = x;
			rear = (rear + 1) % 100;
			return true;
		}
	}

	bool pop(){
		if (empty()) return false;
		else{
			front = (front + 1) % 100;
			return true;
		}
	}

	const T & front()const{
		return arr[front];
	}

private:
	T arr[100];
	int front;
	int rear;
};