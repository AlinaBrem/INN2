
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

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
    Node *start = nullptr;

public:
    class Iterator
    {
    private:
        Node *fake_start_node;
        Node *current_node;

    public:
        ~Iterator()
        {
            delete (fake_start_node);
        }

        bool has_next()
        {
            if (current_node->next != nullptr)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        T *get_next()
        {
            if (current_node->next != nullptr)
            {
                current_node = current_node->next;
                return &current_node->value;
            }
            else
            {
                return nullptr;
            }
        }

        static Iterator new_iterator(Node *n)
        {
            Iterator it;
            it.fake_start_node = Node::new_node(n->value); //value of fake_node doesnt matter but needs to be of type t
            it.fake_start_node->next = n;
            it.current_node = it.fake_start_node;
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
        {
            temp = temp->next;
        }

        if (temp != nullptr)
        {
            return &temp->value;
        }

        return nullptr;
    }

    //delete function gets element and iterates through list to delete it, so that we dont have to use indizes in a linked list
    // (if the exact same T occurs more than once in list only the first one is deleted)
    bool delete_element(T element)
    {
        if (start == nullptr)
        {
            return false;
        }

        Node *temp = start;

        if (start->value == element)
        {
            start = start->next;
            delete (temp);
            return true;
        }

        while (temp->next != nullptr)
        {
            if (element == temp->next->value)
            {
                Node *temp2 = temp->next;
                temp->next = temp->next->next;
                delete (temp2);
                return true;
            }

            temp = temp->next;
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

#endif //LINKEDLIST_H
