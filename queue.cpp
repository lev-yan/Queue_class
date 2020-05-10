#include <iostream>

template <class T>
class Queue {
public:
	struct Node {
		T data;
		Node* next;
		Node() : data(0),
					next(nullptr) {}
		Node(const T & d) : data(d),
						next(nullptr) {}
	};
public:
	Queue();
	Queue(const Queue & obj);
	Queue(Queue && obj);
	Queue & operator=(const Queue &);
	Queue & operator=(Queue &&);
	~Queue();
	void en_queue(const T &);
	void de_queue();
	Queue & swap(Queue & obj);
	bool is_empty() const;
	void print_queue();
	int size;
private:
	void destroy_queue(Node*&);
	void push_back(const T &, Node*&);
	void pop_front(Node*&);
	void print_queue(Node*);
	Node* front, *rear;
};

template <class T>
Queue<T>::Queue() : front(nullptr), 
					rear(nullptr), 
					size(0)
{}

template <class T>
Queue<T>::Queue(const Queue & obj) : front(nullptr), 
									rear(nullptr), 
									size(0)
{
	for(auto i = obj.front; i != nullptr; i = i->next){
		en_queue(i->data);
	}	
}

template <class T>
Queue<T>::Queue(Queue && obj) : front(obj.front), 
								rear(obj.rear), 
								size(obj.size)
{
	obj.front = nullptr;
	obj.rear = nullptr;
	obj.size = 0;
}

template <class T>
Queue<T> & Queue<T>::operator=(const Queue & obj)
{
	if(this == & obj){
		return *this;
	} else {
		destroy_queue(front);
		Node * temp = obj.front;
		for(int i = 0; i < obj.size; i++){
			en_queue(temp->data);
			temp = temp->next;
		}
	}
	return *this;
}

template <class T>
Queue<T> & Queue<T>::operator=(Queue && obj)
{
	if(this == & obj){
		return *this;
	} else {
		destroy_queue(front);
		front = obj.front;
		rear = obj.rear;
		size = obj.size;
		obj.front = nullptr;
		obj.rear = nullptr;
		size = 0;
	}
	return *this;
}

template <class T>
Queue<T>::~Queue()
{
	destroy_queue(front);
}

template <class T>
Queue<T> & Queue<T>::swap(Queue & obj)
{
	std::swap(front, obj.front);
	std::swap(rear, obj.rear);
	return *this;
}

template <class T>
void Queue<T>::en_queue(const T & val)
{
	push_back(val, rear);
}

template <class T>
void Queue<T>::push_back(const T &val, Node*& rear)
{
	if(nullptr == rear){
		rear = new Node(val);
		front = rear;
		size++;
	} else {
		Node* temp = new Node(val);
		rear->next = temp;
		rear = temp;
		size++;
	}
}

template <class T>
void Queue<T>::de_queue()
{
	pop_front(front);
}

template <class T>
void Queue<T>::pop_front(Node* &front)
{
	if(nullptr == front){
		std::cout << "Queue is empty " << std::endl; 
		return;
	} else {
		Node* temp = front;
		front = front->next;
		delete temp;
		--size;
	}
}

template <class T>
bool Queue<T>::is_empty() const
{
	if(nullptr == front){
		return true;
	} else {
		return false;
	}
}

template <class T>
void Queue<T>::destroy_queue(Node* &front)
{
	while(nullptr != front){
		de_queue();
	}
}

template <class T>
void Queue<T>::print_queue()
{
	print_queue(front);
}

template <class T>
void Queue<T>::print_queue(Node* front)
{
	Node* temp = front;
	while(temp){
		std::cout << temp->data << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
}

int main()
{
	Queue <float> q1;
	q1.en_queue(4.4);
	q1.print_queue();
	Queue <int> q2;
	q2.en_queue(4);
	q2.en_queue(7);
	q2.en_queue(9);
	q2.print_queue();
	Queue <int> q3;
	q3 = q2;
	q3.print_queue();
	Queue <int> q4;
	q4 = std::move(q3);
	q4.print_queue();
	return 0;
}
