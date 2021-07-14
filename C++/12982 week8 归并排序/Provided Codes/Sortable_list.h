#ifndef SORTABLE_LIST_H
#define SORTABLE_LIST_H

#include <initializer_list>
#include <string>

using namespace std;

template <class Record>
struct Node {
    Record entry;
    Node<Record> *next;
};

template <class Record>
class Sortable_list {
   public:
    Sortable_list() {
        head = nullptr;
    }

    ~Sortable_list() {
        Node<Record> *t = head;
        while (head != nullptr) {
            head = head->next;
            delete[] t;
            t = head;
        }
    }

    // 在第position个位置插入值为entry的元素，如果position为0则插入在链表头，以此类推
    // 输入数据中，position满足 0 <= position <= 链表元素数量
    void insert(int position, const Record &entry) {
        Node<Record> *new_node = new Node<Record>;
        new_node->entry = entry;
        if (position == 0) {
            new_node->next = head;
            head = new_node;
            return;
        }
        Node<Record> *temp = nullptr;
        Node<Record> *t = head;
        for (int i = 0; i < position; ++i) {
            temp = t;
            t = t->next;
        }
        temp->next = new_node;
        new_node->next = t;
    }

    // 输出链表的内容，每两个元素之间用一个空格隔开，最后一个元素之后没有空格，并且需要换行
    void print() {
        Node<Record> *t = head;
        while (t != nullptr) {
            cout << t->entry;
            t = t->next;
            if (t != nullptr) cout << " ";
        }
        cout << endl;
    }

    Node<Record> *Merge(Node<Record> *l, Node<Record> *r) {
        Node<Record> *pre = new Node<Record>;
        Node<Record> *temp = pre;
        while (l != nullptr && r != nullptr) {
            if (l->entry <= r->entry) {
                temp->next = l;
                l = l->next;
                temp = temp->next;
            }
            else {
                temp->next = r;
                r = r->next;
                temp = temp->next;
            }
        }
        if (l != nullptr) temp->next = l;
        if (r != nullptr) temp->next = r;
        temp = pre->next;
        delete pre;
        return temp;
    }

    Node<Record> *MergeSort(Node<Record> *h) {
        if (h->next == nullptr) return h;
        Node<Record> *slow = h;
        Node<Record> *fast = h;
        Node<Record> *pre = nullptr;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            pre = slow;
            slow = slow->next;
        }
        pre->next = nullptr;
        Node<Record> *newLeft = MergeSort(h);
        Node<Record> *newRight = MergeSort(slow);
        return Merge(newLeft, newRight);
    }

    // 对链表进行归并排序，你可以添加一些辅助函数，但不能改动类的成员变量
    void merge_sort() {
        head = MergeSort(head);
    }

   private:
    Node<Record> *head;  // 链表头指针
};

#endif