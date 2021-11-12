#pragma once

struct KeyPressEvent { int action, key; };
struct MouseClickEvent { int button, action; };
struct MouseMoveEvent { double xpos, ypos; };

template <class T>
class EventQueue
{
public:

	void Enqueue(T item)
	{
		if ((tail_ + 1) % MAX_PENDING != head_)
		{
			pending_[tail_] = item;
			tail_ = (tail_ + 1) % MAX_PENDING;
			numPending += 1;
		}
	}

	T Dequeue()
	{
		T item = pending_[head_];
		head_ = (head_ + 1) % MAX_PENDING;
		numPending -= 1;

		return item;
	}

	bool IsEmpty()
	{
		return head_ == tail_;
	}

	int NumberPending() { return numPending; }

	/*//for testing purposes
	void PrintQueue()
	{
		if (head_ < tail_)
		{
			for (int currentIndex = head_; currentIndex < tail_; currentIndex++) {
				std::cout << (char)pending_[currentIndex].key << " ";
			}
		}
		else if (head_ > tail_)
		{
			for (int currentIndex = head_; currentIndex < MAX_PENDING; currentIndex++) {
				std::cout << (char)pending_[currentIndex].key << " ";
			}

			for (int currentIndex = 0; currentIndex < tail_; currentIndex++) {
				std::cout << (char)pending_[currentIndex].key << " ";
			}
		}
		else {
			std::cout << "Queue Empty!";
		}

		std::cout << std::endl;
	}*/

private:
	T pending_[20];
	int head_ = 0; 
	int tail_ = 0; 
	int MAX_PENDING = 20;

	int numPending = 0;
};