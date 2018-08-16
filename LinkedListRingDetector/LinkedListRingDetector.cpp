// LinkedListRingDetector.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <climits>
#include <random>
#include <iostream>
using ull = unsigned long long;
struct HW_Node
{
	// "index" for debug print, useless
	ull index;
	HW_Node *next;
};
class HW_LinkedListRing
{
	HW_Node *head, *joint;
	ull count, jointIndex;
public:
	HW_LinkedListRing(ull count, ull jointIndex):count(count), jointIndex(jointIndex), head(nullptr), joint(nullptr)
	{
		this->Generate();
	}
	HW_LinkedListRing()
	{
		HW_Node *next;
		while (nullptr != head)
		{
			next = head->next;
			delete head;
			head = next;
		}
	}
	HW_Node *GetHead()
	{
		return head;
	}
	ull GetCount()
	{
		return count;
	}
private:
	void Generate()
	{
		ull tmp = 0;
		head = new HW_Node();
		HW_Node *current = head;
		while (tmp < count)
		{
			if (jointIndex == tmp)
			{
				joint = current;
			}
			current->index = tmp;
			current->next = new HW_Node();
			current = current->next;
			tmp++;
		}
		current->index = tmp;
		current->next = joint;
		this->PrintInformation();
	}
	void PrintInformation()
	{
		std::cout << "There are " << count << " nodes in the linked list. " << std::endl;
		std::cout << "The joint placed at " << joint->index << "th node in the linked list." << std::endl;
	}
};
bool isRing(HW_LinkedListRing *linkedList)
{
	HW_Node *i1 = linkedList->GetHead(), *i2 = linkedList->GetHead()->next;
	ull index = 1, current = 1;
	
	while (i1 != i2)
	{
		std::cout << i2->index << ", ";
		if (nullptr == i2)
		{
			return false;
		}		
		if (current == 2 * index)
		{
			std::cout << "Reset index from " << index << " to " << current << std::endl;
			index = current;
			i1 = i2;			
		}
		i2 = i2->next;
		current++;		
	}
	std::cout << "We compared " << current << " times to get result." << std::endl;
	std::cout << "compare times / list size = " << current / (double)linkedList->GetCount() << std::endl;
	return true;
}
int main()
{
	std::default_random_engine generator;
	// make sure n >= 1, that there at least 1 node.
	std::uniform_int_distribution<ull> distribution(1, CHAR_MAX);
	while (true)
	{		
		ull n = distribution(generator);
		// because there at least 1 node, so (n - 1 >= 0). 
		std::uniform_int_distribution<ull> distribution(0, n - 1);
		ull jointIndex = distribution(generator);

		HW_LinkedListRing *ring = new HW_LinkedListRing(n, jointIndex);
		std::cout << isRing(ring) << std::endl;
		getchar();
		delete ring;
	}

    return 0;
}

