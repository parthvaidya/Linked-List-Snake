#include "LinkedList/SingleLinkedList.h"
#include "Player/BodyPart.h"
#include "Level/LevelView.h"

namespace LinkedList
{
	SingleLinkedList::SingleLinkedList()
	{
		head_node = nullptr;
	}
	SingleLinkedList::~SingleLinkedList() = default;
	void SingleLinkedList::initialize(float width, float height, sf::Vector2i position, Direction direction)
	{
		node_width = width;
		node_height = height;
		default_position = position;
		default_direction = direction;
	}
	void SingleLinkedList::render()
	{
		head_node->body_part.render();
	}
	void SingleLinkedList::createHeadNode()
	{
		head_node = createNode();
		head_node->body_part.initialize(node_width, node_height, default_position, default_direction);
		return;
	}
	Node* SingleLinkedList::createNode()
	{
		return new Node();
	}

	sf::Vector2i SingleLinkedList::getNewNodePosition(Node* reference_node, Operation operation)
	{
		switch (operation)
		{
		case Operation::HEAD:
			return reference_node->body_part.getNextPosition();
		case Operation::TAIL:
			return reference_node->body_part.getPrevPosition();
		}

		return default_position;
	}

	void SingleLinkedList::initializeNode(Node* new_node, Node* reference_node, Operation operation)
	{
		if (reference_node == nullptr)
		{
			new_node->body_part.initialize(node_width, node_height, default_position, default_direction);
			return;
		}

		sf::Vector2i position = getNewNodePosition(reference_node, operation);

		new_node->body_part.initialize(node_width, node_height, position, reference_node->body_part.getDirection());
	}

	void SingleLinkedList::insertNodeAtHead()
	{
		linked_list_size++;
		Node* new_node = createNode();

		if (head_node == nullptr)
		{
			head_node = new_node;
			initializeNode(new_node, nullptr, Operation::HEAD);
			return;
		}

		initializeNode(new_node, head_node, Operation::HEAD);
		new_node->next = head_node;
		head_node = new_node;
	}

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

	void SingleLinkedList::shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node)
	{
		Node* next_node = cur_node;
		cur_node = new_node;

		while (cur_node != nullptr && next_node != nullptr)
		{
			cur_node->body_part.setPosition(next_node->body_part.getPosition());
			cur_node->body_part.setDirection(next_node->body_part.getDirection());

			prev_node = cur_node;
			cur_node = next_node;
			next_node = next_node->next;
		}

		initializeNode(cur_node, prev_node, Operation::TAIL);
	}

	int SingleLinkedList::findMiddleNode()
	{
		Node* slow = head_node;
		Node* fast = head_node;
		int midIndex = 0;  // This will track the index of the middle node.

		// Move fast pointer at 2x speed and slow pointer at 1x speed.
		while (fast != nullptr && fast->next != nullptr) {
			slow = slow->next;
			fast = fast->next->next;
			midIndex++;
		}

		// Now, slow is at the middle node
		return midIndex;
	}

	void SingleLinkedList::insertNodeAtMiddle()
	{
		if (head_node == nullptr) {
			insertNodeAtHead();             // If the list is empty, insert at the head.
			return;
		}

		int midIndex = findMiddleNode();    // Use the existing function to find the middle index
		insertNodeAt(midIndex);             // Use the existing function to insert the node at the found index             
	}

	void SingleLinkedList::removeNodeAtHead()
	{
		Node* cur_node = head_node;
		head_node = head_node->next;

		cur_node->next = nullptr;
		delete (cur_node);
	}

	void SingleLinkedList::removeNodeAtTail()
	{
		if (head_node == nullptr) return;
		linked_list_size--; //Decrement linked list size when you are deleting a node

		Node* cur_node = head_node;

		if (cur_node->next == nullptr) //If there is only 1 node in the linked list
		{
			removeNodeAtHead();
			return;
		}

		while (cur_node->next->next != nullptr) //If there is more than 1 node in the linked list
		{
			cur_node = cur_node->next;
		}

		delete (cur_node->next);
		cur_node->next = nullptr; //Set the new tail node's next pointer to nullptr
	}

	void SingleLinkedList::insertNodeAtTail() {
		Node* new_node = createNode();
		Node* cur_node = head_node;

		if (cur_node == nullptr) {       // If the list is empty, set the new node as the head
			head_node = new_node;
			new_node->body_part.initialize(node_width, node_height, default_position, default_direction);
			return;
		}

		// Traverse to the end of the list 
		while (cur_node->next != nullptr) {
			cur_node = cur_node->next;
		}

		// Attach the new node at the end
		cur_node->next = new_node;
		new_node->body_part.initialize(node_width, node_height, getNewNodePosition(cur_node), cur_node->body_part.getDirection());
	}
	void SingleLinkedList::updateNodePosition()
	{
		Node* cur_node = head_node;

		while (cur_node != nullptr)
		{
			cur_node->body_part.updatePosition();
			cur_node = cur_node->next;
		}
	}

	bool SingleLinkedList::processNodeCollision()
	{
		if (head_node == nullptr) return false;

		sf::Vector2i predicted_position = head_node->body_part.getNextPosition();

		Node* cur_node = head_node->next;
		while (cur_node != nullptr)
		{
			if (cur_node->body_part.getNextPosition() == predicted_position) return true;
			cur_node = cur_node->next;
		}

		return false;
	}

	void SingleLinkedList::render() {
		Node* cur_node = head_node;

		while (cur_node != nullptr) {     // Traverse through the linked list and render each node's body part
			cur_node->body_part.render();
			cur_node = cur_node->next;
		}
	}

	void SingleLinkedList::removeAllNodes()
	{
		if (head_node == nullptr) return;

		while (head_node != nullptr)
		{
			removeNodeAtHead();
		}
	}

	void SingleLinkedList::removeNodeAtHead()
	{
		Node* cur_node = head_node;
		head_node = head_node->next;

		cur_node->next = nullptr;
		delete (cur_node);
	}
}}
}