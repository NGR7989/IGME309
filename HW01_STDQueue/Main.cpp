#include "Main.h"
#include "PriorityQueue.h"

using namespace std;

template <typename T> 
void Print(PriorityQueue<T> a_queue)
{
	std::cout << "Begining of queue......." << std::endl;
	uint count = a_queue.GetSize();
	for (uint i = 0; i < count; ++i)
	{
		std::cout << a_queue[i];
		std::cout << std::endl;
	}
	std::cout << "End of queue............" << std::endl;
}

int main(void)
{
	PriorityQueue<int> myQueue;
	//Push elements
	myQueue.Push(0);
	std::cout << "	just pushed +++++" << std::endl;
	myQueue.Push(1);
	std::cout << "	just pushed +++++" << std::endl;
	myQueue.Push(2);
	std::cout << "	just pushed +++++" << std::endl;
	//Print queue
	Print<int>(myQueue);
	//pop an element
	//myQueue.Pop();
	std::cout << "		just popped -----" << std::endl;
	//add elements
	Print<int>(myQueue);

	myQueue.Push(3);
	std::cout << "	just pushed +++++" << std::endl;
	myQueue.Push(4);
	std::cout << "	just pushed +++++" << std::endl;
	myQueue.Push(5);
	std::cout << "	just pushed +++++" << std::endl;
	//Print queue
	Print<int>(myQueue);
	myQueue.Pop();
	std::cout << "		just popped -----" << std::endl;
	myQueue.Pop();
	std::cout << "		just popped -----" << std::endl;
	//Print queue
	Print<int>(myQueue);
	//clear queue
	uint count = myQueue.GetSize();
	for (uint i = 0; i < count; ++i)
	{
		myQueue.Pop();
		std::cout << "		just popped -----" << std::endl;
	}
	//Print queue
	Print<int>(myQueue);

	////Complex Data usage
	//PriorityQueue<Foo> myFooQueue;
	//for (uint i = 0; i < 10; ++i)
	//{
	//	Foo foo(i);
	//	myFooQueue.Push(foo);
	//	std::cout << "	just pushed +++++" << std::endl;
	//	if (i % 2 == 0)
	//	{
	//		myFooQueue.Pop();
	//		std::cout << "		just popped -----" << std::endl;
	//	}
	//}

	PriorityQueue<AlbertoClass> myAlbertoQueue;
	for (uint i = 30; i < 40; ++i)
	{
		AlbertoClass alberto(i);
		myAlbertoQueue.Push(alberto);
		std::cout << "	just pushed +++++" << std::endl;
	}
	std::cout << "	Content" << std::endl;
	for (uint i = 0; i < 10; ++i)
	{
		std::cout << myAlbertoQueue[i] << std::endl;
	}

	std::cout << "Press Enter to finish." << std::endl;



	getchar();
}