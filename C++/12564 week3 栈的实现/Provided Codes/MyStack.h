typedef int Stack_entry;

class Stack {
public:
    Stack(){
        stack_top = 0;
    }

    bool empty() const{
        return stack_top == 0;
    }

    int size() const{
        return stack_top;
    }

    void push(const Stack_entry &item){
        if (stack_top == 100) return;
        else arr[stack_top++] = item;
    }

    void pop(){
        if (empty()) return;
        else stack_top--;
    }

    const Stack_entry & top() const{
    if (empty()) return -1;
    else return arr[stack_top - 1];
    }
    
    ~Stack(){}

    Stack(const Stack &original){
        for (int i = 0; i < original.stack_top; ++i){
            arr[i] = original.arr[i];
        }
    }

    void operator =(const Stack &original){
        for (int i = 0; i < original.stack_top; ++i){
            arr[i] = original.arr[i];
        }
    }

private:
    Stack_entry arr[100];
    int stack_top;
};


