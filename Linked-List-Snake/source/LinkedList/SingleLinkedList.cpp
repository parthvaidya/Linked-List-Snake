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