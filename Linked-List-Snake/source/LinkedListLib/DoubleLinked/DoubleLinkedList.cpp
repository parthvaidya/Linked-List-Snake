#include "LinkedListLib/DoubleLinked/DoubleLinkedList.h"
#include "LinkedListLib/DoubleLinked/DoubleNode.h"
#include "Level/LevelView.h"
#include "Global/Config.h"
#include <iostream>

namespace LinkedListLib
{
    namespace DoubleLinked
    {
        Node* DoubleLinkedList::createNode()
        {
            return new DoubleNode();
        }

        DoubleLinkedList::DoubleLinkedList() = default;

        DoubleLinkedList::~DoubleLinkedList() = default;



        void DoubleLinkedList::insertNodeAtHead()
        {
            linked_list_size++;
            Node* new_node = createNode();

            if (head_node == nullptr)
            {
                head_node = new_node;
                static_cast<DoubleNode*>(new_node)->previous = nullptr;
                initializeNode(new_node, nullptr, Operation::HEAD);
                return;
            }

            initializeNode(new_node, head_node, Operation::HEAD);

            new_node->next = head_node;
            static_cast<DoubleNode*>(head_node)->previous = new_node;

            head_node = new_node;
        }


        void DoubleLinkedList::insertNodeAtTail()
        {
            linked_list_size++;
            Node* new_node = createNode();
            Node* cur_node = head_node;

            if (cur_node == nullptr)
            {
                head_node = new_node;
                static_cast<DoubleNode*>(new_node)->previous = nullptr;
                initializeNode(new_node, nullptr, Operation::TAIL);
                return;
            }

            while (cur_node->next != nullptr)
            {
                cur_node = cur_node->next;
            }

            cur_node->next = new_node;
            static_cast<DoubleNode*>(new_node)->previous = cur_node;
            initializeNode(new_node, cur_node, Operation::TAIL);
        }

        void DoubleLinkedList::insertNodeAtMiddle()
        {
            if (head_node == nullptr) {
                insertNodeAtHead();             // If the list is empty, insert at the head.
                return;
            }

            int midIndex = findMiddleNode();    // Use the existing function to find the middle index
            insertNodeAtIndex(midIndex);             // Use the existing function to insert the node at the found index             
        }

        void DoubleLinkedList::removeNodeAtHead() {
            linked_list_size--;

            Node* cur_node = head_node;
            head_node = head_node->next;

            if (head_node != nullptr) {
                static_cast<DoubleNode*>(head_node)->previous = nullptr;
            }

            cur_node->next = nullptr;
            delete cur_node;
        }

        void DoubleLinkedList::removeNodeAtTail()
        {
            if (head_node == nullptr) return;
            linked_list_size--;

            Node* cur_node = head_node;

            if (cur_node->next == nullptr)
            {
                removeNodeAtHead();
                return;
            }

            while (cur_node->next != nullptr)
            {
                cur_node = cur_node->next;
            }

            Node* previous = static_cast<DoubleNode*>(cur_node)->previous;
            previous->next = nullptr;
            delete (cur_node);
        }

        void DoubleLinkedList::removeNodeAtMiddle()
        {
            if (head_node == nullptr) return; // If the list is empty, there's nothing to remove

            int midIndex = findMiddleNode();  // Use the existing function to find the middle index
            removeNodeAt(midIndex);           // Use the existing function to remove the node at the found index
        }

    }
}