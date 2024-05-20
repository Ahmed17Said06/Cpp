#include<iostream>
#include<cassert>
using namespace std;

struct Node
{
    int data {};
    Node* next {};
    Node* prev {};

    Node(int data) : data(data) {}

    void set(Node *next, Node *prev)
    {
        this->next = next;
        this->prev = prev;
    }

    ~Node()
    {
        cout << "Destroy value: " << data <<" at addess " << this <<"\n";
    }
};

class DoubleLinkedList
{
    private:
        Node *head {};
        Node *tail {};
        int length = 0;

    public:
        // Below 2 deletes prevent copy and assign to avoid this mistake
        // LinkedList() {
        // }
        // LinkedList(const LinkedList&) = delete;
        // LinkedList &operator=(const LinkedList &another) = delete;

        void print()
        {
            // DON'T change head itself.
            // you will lose it

            for (Node *cur = head; cur; cur = cur->next)
            {
                cout << cur->data << " ";
            }
            cout << "\n";
        }

        void add_node(Node* node) {
		++length;
	    }

        void link(Node *first, Node *second)
        {
            if(first)
            {
                first->next = second;
            }
            if(second)
            {
                second->prev = first;
            }
        }
        void insert_end (int value)
        {
            Node *item = new Node(value);
            add_node(item);

            if (!head)
            {
                head = tail = item;
            }
            else
            {
                link (tail, item);
                tail = item;
            }
        }

        void insert_front(int val) //O(1) time - O(1) memory
        {
            Node *item = new Node(val);

            add_node(item);

            link(item, head);

            head = item;

            if(length == 1)
            {
                tail = head;
            }
        }

        Node *get_nth (int n) //O(n) time - O(1) memory
        {
            int cnt = 0;

            for(Node *cur = head; cur; cur = cur->next)
            {
                if(++cnt == n)
                {
                    return cur;
                }
            }
            return nullptr;
        }

        Node *get_nth_back(int n) //o(n) time O(1) memory
        {
            if(length < n)
            {
                return nullptr;
            }
            return get_nth(length - n + 1);
        }

        int search (int val)
        {
            int idx = 0;
            for(Node *cur = head; cur; cur = cur->next, idx++)
            {
                if(cur->data == val)
                {
                    return idx; 
                }
            }
            return -1;
        }

        int search_improved (int val)
        {
            int idx = 0;
            Node* prev = nullptr;

            for(Node *cur = head; cur; cur = cur->next, idx++)
            {
                if(cur->data == val)
                {
                    if(!prev)
                    {
                        return idx;
                    }
                    swap(prev->data, cur->data);
                    return idx - 1;
                }
                prev = cur;
            }
            return -1;
        }

        void delete_node(Node* node) //O(1) time - O(1) memory
        {
            --length;
            delete node;
	    }

        void delete_front() //O(1) time - O(1) memory
        {

            if(!head)
            {
                return;
            }

            Node *cur = head->next;
            delete_node(head);
            head = cur;

            if(head)
            {
                head->prev = nullptr;
            }
            else if(!length)
            {
                tail = nullptr;
            }	
        }

        void delete_end()
        {
            if(length <= 1)
            {
                delete_first();
                return;
            }
            else
            {
                Node *cur = tail->prev;
                delete_node(tail);
                tail = cur;

                if(tail)
                {
                    tail->next = nullptr;
                }
                else if (!length)
                {
                    head = nullptr;
                }
            }
        }

        void delete_first()
        {
            if(head)
            {
               Node *cur = head;
               head = head->next;
               delete_node(head);

                if(!head)
                {
                    tail = nullptr;
                } 
            }
        }


        void delete_nth_node(int n)
        {
            if(n < 1 || n > length)
            {
                cout << "Error. No such node.\n";
            }
            else if (n == 1)
            {
                delete_first();
                return;
            }
            else if(n == length)
            {
                delete_end();
                return;
            }
            else
            {
                Node *prev_n = get_nth(n - 1);
                Node *cur_n = prev_n->next;

                prev_n->next = cur_n->next;
                delete_node(cur_n);
            }
        }
        ~DoubleLinkedList() // O(n) time - O(1) memory
        {
            while(head)
            {
                Node *current = head->next;
                delete head;
                head = current;
            }
        }    
};


