
#ifndef LINKEDLIST
#define LINKEDLIST
template <class T>
class LinkedList
{
private:
    class Node
    {
    public:
        Node *next;
        T value;

        static Node *new_node(T t)
        {
            Node *new_node = new Node();
            new_node->value = t;
            new_node->next = nullptr;
            return new_node;
        }
    };

    Node *end = nullptr;

public:
    Node *start = nullptr;
    class Iterator
    {
    private:
        Node *current_node;

    public:
        bool has_next()
        {
            if (current_node != nullptr)
                return true;
            else
                return false;
        }
        T *get_next()
        {
            if (current_node != nullptr)
            {
                T *temp;
                temp = &current_node->value;
                current_node = current_node->next;
                return temp;
            }
            else
                return nullptr;
        }

        static Iterator new_iterator(Node *n)
        {
            Iterator it;
            it.current_node = n;
            return it;
        }
    };

    // Fügt einen neuen Wert am Anfang hinzu.
    void push_value(T t)
    {
        Node *new_node = Node::new_node(t);
        if (start == nullptr)
        {
            start = new_node;
            end = new_node;
        }
        else
        {
            new_node->next = start;
            start = new_node;
        }
    }

    //Fügt einen neuen Wert am Ende hinzu.
    void append_value(T t)
    {
        Node *new_node = Node::new_node(t);
        if (start == nullptr)
        {
            start = new_node;
            end = new_node;
        }
        else
        {
            end->next = new_node;
            end = new_node;
        }
    }

    T *get_reference(int i)
    {
        Node *temp = start;
        for (int y = i; y > 0 && temp != nullptr; y--)
            temp = temp->next;
        if (temp != nullptr)
            return &temp->value;
        return nullptr;
    }

    //Versucht einen Wert an der Stelle i zu löschen, wenn das nicht geht wird false zurückgegeben.
    bool try_delete(int i)
    {
        if (i == 0 && start != nullptr)
        {
            Node *temp = start->next;
            delete (start);
            start = temp;
            return true;
        }

        Node *temp1 = start;
        Node *temp2 = start;

        int y = i;
        while (y > 0 && temp2->next != nullptr)
        {
            temp1 = temp2;
            temp2 = temp2->next;
            y--;
        }
        if (y == 0)
        {
            if (temp1 == end)
            {
                end = temp1;
                delete (temp2);
            }
            else
            {
                Node *temp = temp1->next;
                temp1->next = temp2->next;
                delete (temp);
            }
            return true;
        }
        return false;
    }

    //Gibt einen neuen Iterator zurück der nacheinander einen Pointer zu jedem Wert in der Listr zurückgibt.
    Iterator get_Iterator()
    {
        return Iterator::new_iterator(start);
    }
    void delete_list()
    {
        while (start != nullptr)
        {
            Node *temp = start;
            start = start->next;
            delete (temp);
        }
    }
    ~LinkedList()
    {
        delete_list();
    }
};
#endif
