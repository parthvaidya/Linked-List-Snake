#include "LinkedListLib/SingleLinked/SingleLinkedList.h"
#include "LinkedListLib/SingleLinked/SingleNode.h"
#include "Level/LevelView.h"

namespace LinkedListLib
{
    namespace SingleLinked
    {
        Node* SingleLinkedList::createNode()
        {
            return new SingleNode();
        }

        SingleLinkedList::SingleLinkedList() = default;

        SingleLinkedList::~SingleLinkedList() = default;

        void SingleLinkedList::insertNodeAtTail()
        {
            linked_list_size++;
            Node* new_node = createNode();
            Node* cur_node = head_node;

            if (cur_node == nullptr)
            {
                head_node = new_node;
                initializeNode(new_node, nullptr, Operation::TAIL);
                return;
            }

            while (cur_node->next != nullptr)
            {
                cur_node = cur_node->next;
            }

            cur_node->next = new_node;
            initializeNode(new_node, cur_node, Operation::TAIL);
        }

        void SingleLinkedList::removeNodeAtHead() {
            Node* cur_node = head_node;
            head_node = head_node->next;

            cur_node->next = nullptr;
            delete cur_node;
        }


    }
}