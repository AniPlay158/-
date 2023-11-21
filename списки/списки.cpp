#include <iostream>
using namespace std;

class SinglyLinkedList
{
public:
	struct Node
	{
		int data = 0;
		Node* next = nullptr;
	};

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	int count = 0;

public:
	void AddToHead(int data)
	{
		Node* newElem = new Node();
		newElem->data = data;
		newElem->next = head;
		if (head == nullptr)
		{
			tail = newElem;
		}
		head = newElem;
		count++;
	}

	void AddToTail(int data)
	{
		Node* newElem = new Node();
		newElem->data = data;
		if (tail == nullptr)
		{
			head = newElem;
		}
		else
		{
			tail->next = newElem;
		}
		tail = newElem;
		count++;
	}

	void InsertInto(int data, int position)
	{
		if (position >= count)
		{
			AddToTail(data);
			return;
		}
		else if (position <= 0)
		{
			AddToHead(data);
			return;
		}

		Node* newElem = new Node();
		newElem->data = data;
		int i = 1;
		Node* beforeNew = head;
		while (i++ != position)
		{
			beforeNew = beforeNew->next;
		}
		newElem->next = beforeNew->next;
		beforeNew->next = newElem;

		count++;
	}

	void DeleteFromHead()
	{
		if (count == 0)
		{
			// cout << "Empty list!\n";
			return;
		}
		Node* temp = head;
		head = head->next;
		delete temp;
		count--;
		if (head == nullptr)
		{
			tail = nullptr;
		}
	}

	void DeleteFromTail()
	{
		if (count == 0) {
			// cout << "Empty list!\n";
			return;
		}
		DeleteByIndex(count - 1);
	}

	void DeleteByIndex(int position)
	{
		if (position <= 0)
		{
			DeleteFromHead();
			return;
		}

		if (position >= count)
		{
			position = count - 1;
		}

		int i = 1;
		Node* beforeDel = head;
		while (i++ != position)
		{
			beforeDel = beforeDel->next;
		}
		Node* sacrifice = beforeDel->next;
		beforeDel->next = sacrifice->next;
		delete sacrifice;
		count--;
		if (beforeDel->next == nullptr)
		{
			tail = beforeDel;
		}
	}

	void Clear()
	{
		while (head != nullptr)
		{
			DeleteFromHead();
		}
	}

	void Print() const
	{
		if (count == 0)
		{
			cout << "Empty list!\n";
			return;
		}
		Node* current = head;
		while (current != nullptr)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}

	int GetCount() const
	{
		return count;
	}

	int IndexOf(int data) const
	{
		if (count == 0)
		{
			// cout << "Empty list!\n";
			return -1;
		}
		Node* temp = head;
		int i = 0;
		while (i < count)
		{
			if (data == temp->data)
			{
				return i;
			}
			i++;
			temp = temp->next;
		}

		return -1;
	}

	///////////////////////////////DZ

	bool IsEmpty() const
	{
		if (count == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int LastIndexOf(int data) const
	{
		if (count == 0)
		{
			return -1;
		}
		else
		{
			Node* temp = head;
			int last_found_index = -1;

			for (int i = 0; i < count; ++i)
			{
				if (temp->data == data)
				{
					last_found_index = i;
				}
				temp = temp->next;
			}

			return last_found_index;
		}

	}

	void Reverse()
	{
		if (count <= 1)
		{
			return;
		}

		Node* prev = nullptr;
		Node* current = head;
		Node* next = nullptr;

		tail = head; 

		while (current != nullptr)
		{
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}

		head = prev; 
	}

	void SortAsc()
	{
		if (count <= 1)
		{
			return;
		}

		for (Node* i = head; i != nullptr; i = i->next)
		{
			for (Node* j = i->next; j != nullptr; j = j->next)
			{
				if (i->data > j->data)
				{
					int temp = i->data;
					i->data = j->data;
					j->data = temp;
				}
			}
		}
	}

	void Shuffle()
	{
		if (count <= 1)
		{
			return;
		}

		for (int i = count - 1; i > 0; --i)
		{
			int random_index = rand() % (i + 1);

			Node* node_i = head;
			Node* node_random = head;

			for (int j = 0; j < i; ++j)
			{
				node_i = node_i->next;
			}

			for (int j = 0; j < random_index; ++j)
			{
				node_random = node_random->next;
			}

			int temp = node_i->data;
			node_i->data = node_random->data;
			node_random->data = temp;
		}
	}

	int* ToArray() const
	{
		if (count == 0)
		{
			return nullptr;
		}

		int* array_copy = new int[count];
		Node* current = head;

		for (int i = 0; i < count; ++i)
		{
			array_copy[i] = current->data;
			current = current->next;
		}

		return array_copy;
	}

	void PrintArr(int* array_copy)
	{
		cout << "Array copy: ";
		for (int i = 0; i < GetCount(); ++i)
		{
			cout << array_copy[i] << " ";
		}
		cout << "\n";

		delete[] array_copy;
	}

	int& operator[](int index)
	{
		if (index < 0 || index >= count)
		{
			throw "ERROR";
		}

		Node* current = head;
		for (int i = 0; i < index; ++i)
		{
			current = current->next;
		}

		return current->data;
	}

	friend ostream& operator << (ostream& os, const SinglyLinkedList& list);



};

ostream& operator<<(ostream& os, const SinglyLinkedList& list)
{
    if (list.GetCount() == 0)
    {
        os << "Empty list!";
        return os;
    }

    SinglyLinkedList::Node* current = list.head;
    while (current != nullptr)
    {
        os << current->data << " ";
        current = current->next;
    }

    return os;
}

int main()
{
	SinglyLinkedList sll;

	srand(time(0));

	// вставка в конец списка
	sll.AddToTail(10);
	sll.AddToTail(20);
	sll.AddToTail(30);
	sll.AddToTail(40);
	sll.Print();

	// вставка в начало списка
	sll.AddToHead(50);
	sll.AddToHead(60);
	sll.AddToHead(70);
	sll.AddToHead(80);
	sll.Print();

	// количество элементов, поиск элементов
	cout << "count: " << sll.GetCount() << "\n";
	cout << "index of 70: " << sll.IndexOf(70) << ", index of 90: " << sll.IndexOf(90) << "\n";

	// вставка по позиции
	sll.InsertInto(-1, -1);
	sll.Print();
	sll.InsertInto(2, 2);
	sll.Print();
	sll.InsertInto(22, 22);
	sll.Print();

	// удаление с начала списка
	sll.DeleteFromHead();
	sll.DeleteFromHead();
	sll.DeleteFromHead();
	sll.Print();

	// удаление с конца списка
	sll.DeleteFromTail();
	sll.DeleteFromTail();
	sll.DeleteFromTail();
	sll.Print();

	// удаление по указанному индексу
	sll.DeleteByIndex(0);
	sll.DeleteByIndex(1);
	sll.DeleteByIndex(2);
	sll.Print();

	// очистка списка
	//sll.Clear();
	//sll.Print();

	///////////////////////////DZ

	//1
	cout << sll.IsEmpty()<<"\n";

	//2
	int value = 3;
	sll.AddToHead(3);
	sll.Print();
	cout << sll.LastIndexOf(value)<<"\n";

	//3
	cout << "Original list: ";
	sll.Print();
	sll.Reverse();
	cout << "Reversed list: ";
	sll.Print();

	//4
	sll.SortAsc();
	cout << "Sorted list: ";
	sll.Print();

	//5
	sll.Shuffle();
	cout << "Shuffled list: ";
	sll.Print();

	//6
	cout << "Original list: ";
	sll.Print();
	int* array_copy = sll.ToArray();
	if (array_copy != nullptr)
	{
		sll.PrintArr(array_copy);
	}
	else
	{
		cout << "Unable to create an array copy. The list is empty.\n";
	}

	//7
	cout << "Original list: ";
	sll.Print();
	int index_to_access = 2;
	cout << "Element at index " << index_to_access << ": " << sll[index_to_access] << "\n";
	sll[index_to_access] = 158;
	cout << "Updated list: ";
	sll.Print();

	//8
	cout << "Current list: " << sll << "\n";

}