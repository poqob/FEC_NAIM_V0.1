#ifndef LINKEDLIST
#define LINKEDLIST
#include "Arduino.h"
template <typename T>
class LinkedList
{
private:
    // Node structure
    struct Node
    {
        T data;
        Node *next;
    };

    Node *head; // Pointer to the first node
    int size;   // Size of the list

public:
    // Constructor
    LinkedList() : head(nullptr), size(0) {}

    // Destructor to clear memory
    ~LinkedList()
    {
        clear();
    }

    // Add a new element to the front
    void addFront(T value)
    {
        Node *newNode = new Node(); // Create new node
        newNode->data = value;
        newNode->next = head; // Point to current head
        head = newNode;       // Update head
        size++;
    }

    // Add a new element to the back
    void addBack(T value)
    {
        Node *newNode = new Node(); // Create new node
        newNode->data = value;
        newNode->next = nullptr; // Last node points to null

        if (head == nullptr)
        {
            head = newNode; // If list is empty, new node is the head
        }
        else
        {
            Node *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next; // Traverse to the last node
            }
            temp->next = newNode; // Link last node to new node
        }
        size++;
    }

    // Remove the first element
    void removeFront()
    {
        if (head != nullptr)
        {
            Node *temp = head; // Store the current head
            head = head->next; // Move the head to the next node
            delete temp;       // Free memory
            size--;
        }
    }

    // Get the value at a specific index
    T get(int index)
    {
        if (index < 0 || index >= size)
        {
            return T(); // Return default value if index is invalid
        }
        Node *temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next; // Traverse to the desired index
        }
        return temp->data;
    }

    // Get the size of the list
    int getSize() const
    {
        return size;
    }

    // Check if the list is empty
    bool isEmpty() const
    {
        return head == nullptr;
    }

    // Clear the entire list
    void clear()
    {
        while (head != nullptr)
        {
            removeFront(); // Continuously remove the front element
        }
    }

    // Print the linked list elements (for debugging purposes)
    void printList() const
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            Serial.print(temp->data);
            Serial.print(" -> ");
            temp = temp->next;
        }
        Serial.println("NULL");
    }
};
#endif