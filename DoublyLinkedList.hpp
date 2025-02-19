#ifndef MY_DOUBLY_LINKED_LIST_HPP
#define MY_DOUBLY_LINKED_LIST_HPP


/**
 * TODO: Implement DoublyLinkedList, its Node, and its Iterator!
 * 
 * I've left some methods filled out for you,
 * 	and stubbed out some structure, to reduce difficulty.
 * 
 * You may add helper methods as you see fit,
 * 	as long as you can still pass all unit tests.
 * 
 * Notice we're inside a namespace here.
 * The DLL is inside a namespace called DoublyLinkedList,
 * 	which is itself inside a namespace called CPSC131
 * This means, if you'd like to play around with your class later,
 * 	you'll need to access it like so:
 * ::CPSC131::DoublyLinkedList::DoublyLinkedList<int> list;
 * 
 * Look into main.cpp and CPP_Tests.cpp for examples of using
 * 	the DLL and your BookStore. But don't worry too much, as you
 * 	only need to implement these classes
 * (main and tests are already done for you)
 * name: Anderson Pham
 * CWID: 884815002
 * Email: ahpham123@csu.fullerton.edu
 */


//
#include <iostream>
#include <stdlib.h>
#include <stdexcept>


/**
 * Namespace for our classroom and DLL !
 */
namespace CPSC131::DoublyLinkedList
{
	/**
	 * Implement our DoublyLinkedList class !
	 */
	template <class T>
	class DoublyLinkedList
	{
		public:
			
			/**
			 * Node class, representing a single item in our linked list
			 */
			// TODO: Complete all class methods
			class Node
			{
				public:
					
					/// CTORS
					/// Member initialization lists?
					Node() : prev_(nullptr), next_(nullptr) {}
					Node(T element) : element_(element), prev_(nullptr), next_(nullptr) {}
					Node(T element, Node* prev, Node* next) : element_(element), prev_(prev), next_(next) {}
					
					/// Set the pointer to the previous element
					void setPrevious(Node* prev) { prev_ = prev; }
					
					/// Set the pointer to the previous element
					void setPrev(Node* prev) { prev_ = prev;}
					
					/// Get a pointer to the previous element
					Node* getPrevious() { return prev_;}
					
					/// Get a pointer to the previous element
					Node* getPrev() { return prev_	;}
					
					/// Set the pointer to the next node
					void setNext(Node* next) { next_ = next; }
					
					/// Get a pointer to the next node
					Node* getNext() { return next_; }
					
					/// Set the element this node holds
					void setElement(T element) { element_ = element;}
					
					/// Get the element this node  holds
					///	YOUR WELCOME
					T& getElement() { return this->element_; }
					
					/// Return a reference to the element
					///	YOUR WELCOME
					T& operator*() { return this->element_; }
					
				private:
					T element_;
					Node* prev_;
					Node* next_;
			};
			
			/**
			 * Nested Iterator class.
			 * This allows user code to refer to the Iterator's type as:
			 * 
			 * CPSC131::DoublyLinkedList::DoublyLinkedList<int>::Iterator
			 * 
			 * (as opposed to specifying the template argument two times)
			 */
			class Iterator
			{
				public:
					
					///	Constructor that does nothing; YOUR WELCOME
					Iterator()
					{
						/// yw
						head_ = nullptr;
						tail_ = nullptr;
						cursor_ = nullptr;
					}
					
					///	Constructor taking a head and tail pointer; YOUR WELCOME
					Iterator(Node* head, Node* tail) : head_(head), tail_(tail)
					{
						//this->cursor_ = this->end();	/// yw
						cursor_ = nullptr;
					}
					
					///	Constructor taking a head, tail, and cursor pointer; YOUR WELCOME
					Iterator(Node* head, Node* tail, Node* cursor) : head_(head), tail_(tail), cursor_(cursor) {}
					
					///	Get a pointer to the head node, or end() if this list is empty
					Node* begin()
					{
						return this->head_;
					}
					
					///	Get a node pointer representing "end" (aka "depleted"). Probably want to just use nullptr.
					Node* end()
					{
						return nullptr;
					}
					
					///	Get the node to which this iterator is currently pointing
					Node* getCursor()
					{
						return cursor_;
					}
					
					///	Return true if this iterator has hit its end; false otherwise
					/// YOUR WELCOME
					bool isAtEnd()
					{
						return (this->cursor_ == nullptr);
					}
					
					/**
					 * Assignment operator
					 * Return a copy of this Iterator, after modification
					 */
					Iterator& operator=(const Iterator& other)
					{
						head_ = other.head_;
						tail_ = other.tail_;
						cursor_ = other.cursor_;
						return *this;
					}
					
					///	Comparison operator
					bool operator==(const Iterator& other)
					{
						if ((this->tail_ == other.tail_) && (this->head_ == other.head_) && (this->cursor_ == other.cursor_))
						{
							return true;
						}
						return false;
					}
					///	Inequality comparison operator
					bool operator!=(const Iterator& other)
					{
						if ((this->head_ == other.head_) && (this->tail_ == other.tail_) && (this->cursor_ == other.cursor_))
						{
							return false;
						}
						return true;
					}
					
					/**
					 * Addition operator
					 */
					Iterator operator +(size_t add)
					{
						//std::cout << "a? " << std::endl;
						Iterator it = Iterator (this->head_, this->tail_, this->cursor_);	
						for (size_t i = 0 ; i < add ; i++)
						{
							if (it.getCursor() == nullptr)
							{
								return it;
							}
							it.cursor_ = it.getCursor()->getNext();
						}
						return it;

					}
					
					
					/**
					 * Subtraction operator
					 */
					Iterator operator -(size_t subtract)
					{
						Iterator it = Iterator (this->head_, this->tail_, this->cursor_);
						for (size_t i = 0 ; i < subtract ; i++)
						{
							if (it.cursor_ == nullptr)
							{
								return it;
							}
							it.cursor_ = it.cursor_->getPrev();
						}
						return it;
					}
					
					/**
					 * Prefix increment operator
					 * Return a copy of this Iterator, after modification
					 */
					Iterator& operator++()
					{
						if (cursor_ == nullptr)
						{
							return *this;
						}
						cursor_ = cursor_->getNext();
						return *this;
					}
					
					/**
					 * Postfix increment
					 * Return a copy of this Iterator, BEFORE it was modified
					 */
					Iterator operator++(int)
					{
						//std::cout << "Running Iterator operator++(int)" << std::endl;
						Iterator it = Iterator(head_, tail_, cursor_);
						if (cursor_ == nullptr)
						{
							return it;
						}
						cursor_ = cursor_->getNext();
						return it;
					}
					
					/**
					 * Prefix decrement operator
					 * Return a copy of this Iterator, after modification
					 */
					Iterator& operator--()
					{
						//std::cout << "Running Iterator operator--()" << std::endl;
						cursor_ = cursor_->getPrev();
						return *this;
					}
					
					/**
					 * Postfix decrement operator
					 * Return a copy of this Iterator BEFORE it was modified
					 */
					Iterator operator--(int)
					{
						//std::cout << "Running Iterator operator--(int)" << std::endl;
						Iterator it = Iterator(head_, tail_, cursor_);
						cursor_ = cursor_->getPrev();
						return it;
					}
					
					/**
					 * AdditionAssignment operator
					 * Return a copy of the current iterator, after modification
					*/
					Iterator operator +=(size_t add)
					{
						//std::cout << "Running Iterator operator +=(size_t add)" << std::endl;
						Iterator it = Iterator(head_, tail_, cursor_);
						for (size_t i = 0 ; i < add ; i++) 
						{
							if (cursor_->getNext() == nullptr)
							{
								return it;
							}
							cursor_ = cursor_->getNext();
						}
						return it;
					}
					/**
					 * SubtractionAssignment operator
					 * Return a copy of the current iterator, after modification
					 */
					
					Iterator operator -=(size_t add)
					{
						//std::cout << "Running operator -=(size_t add)" << std::endl;
						for (size_t i = 0 ; i < add ; i++) 
						{
							//cursor_ = cursor_->getPrev();
						}
						Iterator it = Iterator(head_, tail_, cursor_);
						return it;
					}
					
					/**
					 * AdditionAssignment operator, supporting positive or negative ints
					 */
					Iterator operator +=(int add)
					{
						//std::cout << "Running Iterator operator +=(int add)" << std::endl;
						for (int i = 0 ; i < add ; i++) 
						{
							if (cursor_ == nullptr)
							{
								return *this;
							}
							cursor_ = cursor_->getNext();
						}
						return *this;
					}
					
					/**
					 * SubtractionAssignment operator, supporting positive or negative ints
					 */
					Iterator operator -=(int subtract)
					{
						//std::cout << "Running Iterator operator -=(int subtract)" << std::endl;
						for (int i = 0 ; i < subtract ; i++) 
						{
							if (cursor_ == nullptr)
							{
								return *this;
							}
							cursor_ = cursor_->getPrev();
						}
						return *this;
					}
					
					/**
					 * Dereference operator returns a reference to the ELEMENT contained with the current node
					 */
					T& operator*()
					{
						//std::cout << "Running Iterator Dereference, operator*()" << std::endl;
						return this->cursor_->getElement();
					}
				
				private:
					
					/// Pointer to the head node
					Node* head_ = nullptr;
					
					/// Pointer to the tail node
					Node* tail_ = nullptr;
					
					/**
					 * Pointer to the cursor node.
					 */
					Node* cursor_ = nullptr;
				
				friend class DoublyLinkedList;
			};
			
			/// Default constructor
			DoublyLinkedList()
			{
				head_ = nullptr;
				tail_ = nullptr;
				size_ = 0;
			}
			
			///	Copy Constructor
			DoublyLinkedList(DoublyLinkedList& other)
			{
				for (Iterator itother = Iterator(other.head_, other.tail_, other.head_) ; size_ < other.size() ; itother++)
				{
					this->push_back(itother.getCursor()->getElement());
				}
			}
			
			/// DTOR
			~DoublyLinkedList()
			{
				
			}
			
			/**
			 * Clear the list and assign the same value, count times.
			 * 
			 * Example:
			 *   T is an int
			 *   count is 5
			 *   value = 3
			 * 
			 * Our list would become:
			 *   {3, 3, 3, 3, 3}
			 */
			void assign(size_t count, const T& value)
			{
				//AP123 main prob
				clear();
				for (size_t i = 0 ; i < count ; i++)
				{
					this->push_back(value);
				}
			}
			
			/**
			 * Clear the list and assign values from another list.
			 * The 'first' iterator points to the first item copied from the other list.
			 * The 'last' iterator points to the last item copied from the other list.
			 * 
			 * Example:
			 * 	Suppose we have a source list like {8, 4, 3, 2, 7, 1}
			 * 	Suppose first points to the 4 node
			 *	Suppose last points to the 7 node
			 * 	We should end up with our list becoming: {4, 3, 2, 7}
			 *
			 * If the user code sends out-of-order iterators,
			 * 	just copy from 'first' to the end of the source list
			 * 
			 * Example:
			 *  If we have the same source list {8, 4, 3, 2, 7, 1},
			 *  and first points to the 7 node,
			 *  and last points to the 4 node,
			 *  we would end up with: {7, 1}
			 */
			void assign(Iterator first, Iterator last)
			{
				clear();
				if (first.getCursor() != nullptr)
				{
					if (last.getCursor() != nullptr) 
					{
						bool isLastBeforeFirst = false;
						Node* temp = last.getCursor();
						while (last.getCursor() != nullptr)
						{
							if (last.getCursor() == first.getCursor())
							{
								isLastBeforeFirst = true;
							}
							last++;
						}
						last.cursor_ = temp;
						if (isLastBeforeFirst)
						{
							while (first.getCursor() != nullptr)
							{
								this->push_back(first.getCursor()->getElement());
								first++;
							}
						}
						else
						{
							while (first.getCursor() != last.getCursor()->getNext())
							{
								this->push_back(first.getCursor()->getElement());
								first++;
							}
						}
					}
					else
					{
						while (first.getCursor() != nullptr)
						{
							this->push_back(first.getCursor()->getElement());
							first++;
						}
					}
				}
			}
			
			/// Return a pointer to the head node, if any
			Node* head() const
			{
				if (head_ == nullptr)
				{
					throw std::range_error("Attempted to access null head");
				}
				return head_;
			}
			
			/// Return a pointer to the tail node, if any
			Node* tail() const
			{
				if (tail_ == nullptr)
				{
					throw std::range_error("Attempted to access null tail");
				}
				return tail_;
			}
			
			/**
			 * Return an iterator that points to the head of our list
			 */
			 //Iterator(Node* head, Node* tail, Node* cursor) : head_(head), tail_(tail), cursor_(cursor) {}
			Iterator begin() const
			{
				Iterator it = Iterator(head_, tail_, head_);
				return it;
			}
			
			/**
			 * Return an iterator that points to the last element (tail) of our list
			 */
			Iterator last() const
			{
				Iterator it = Iterator(head_, tail_, tail_);
				return it;
			}
			
			/**
			 * Should return an iterator that represents being past the end of our nodes,
			 * or just that we are finished.
			 * 
			 * You can make this a nullptr or use some other scheme of your choosing,
			 * 	as long as it works with the logic of the rest of your implementations.
			 */
			Iterator end() const
			{
				Iterator it = Iterator(head_, tail_, nullptr);
				return it;
			}
			
			/**
			 * Returns true if our list is empty
			 */
			bool empty() const
			{
				return (head_ == nullptr);
			}
			
			/**
			 * Returns the current size of the list
			 * 
			 * Should finish in constant time!
			 * (keep track of the size elsewhere)
			 */
			size_t size() const
			{
				return size_;
			}
			
			/**
			 * Clears our entire list, making it empty
			 */
			void clear()
			{
				for (size_t i = 0 ; i < size_ ; i++)
				{
					//std::cout << "Attempting pop back " << std::endl;
					this->pop_back();
					//std::cout << "Successful pop back" << std::endl;
				}
				size_ = 0;
			}
			
			/**
			 * Insert an element after the node pointed to by the pos Iterator
			 * 
			 * If the list is currently empty,
			 * 	ignore the iterator and just make the new node at the head/tail (list of length 1).
			 * 
			 * If the incoming iterator is this->end(),
			 *   insert the element as the new tail
			 * 
			 * Should return an iterator that points to the newly added node
			 */
			Iterator insert_after(Iterator pos, const T& value)
			{
				if (pos.getCursor() == nullptr)
				{ //In case of end interator
					if (head_ == nullptr)
					{ //In case of end interator on empty list
						Node* val = new Node(value);
						val->setPrev(nullptr);
						val->setNext(nullptr);
						if (size_ != 0)
						{
							throw std::range_error("Called insert_after(Iterator pos, const T& value) on empty list and size was not 0");
						}
						size_++;
						head_ = val;
						tail_ = val;
						Iterator it = Iterator (head_, tail_, val);
						return it;
					}
					else
					{ // In case of end interator on non empty list
						Node* val = new Node(value);
						val->setPrev(tail_);
						tail_->setNext(val);
						tail_ = val;
						size_++;
						Iterator it = Iterator (head_, tail_, val);
						return it;
					}
				}
				else
				{
					Node* val = new Node(value);
					val->setPrev(pos.getCursor());
					val->setNext(pos.getCursor()->getNext());

					Node *temp = pos.getCursor()->getNext();
					temp->setPrev(val);

					pos.getCursor()->setNext(val);
					Iterator it = Iterator (head_, tail_, val);
					size_++;
					return it;
				}
			}
			
			/**
			 * Insert a new element after the index pos.
			 * Should work with an empty list.
			 * 
			 * Should return an iterator pointing to the newly created node
			*/
			Iterator insert_after(size_t pos, const T& value)
			{
				if ((head_ == nullptr) && (tail_ == nullptr))
				{
					Node* val = new Node(value);
					tail_ = val;
					head_ = val;
					Iterator it = Iterator(head_, tail_, val);
					size_++;
					return it;
				}
				Iterator itprev = Iterator(head_, tail_, head_);
				Iterator itnext = Iterator(head_, tail_, head_);
				for (size_t i = 0 ; i < pos ; i++)
				{
					itprev++;
					itnext++;
				}
				itnext++;
				Node* val = new Node(value);
				//AP123: main problem here VVV
				if ((itprev.getCursor() == nullptr) || (itnext.getCursor() == nullptr))
				{
					val->setPrev(tail_);
					tail_->setNext(val);
					tail_ = val;
				}
				else {
					val->setPrev(itprev.getCursor());
					val->setNext(itnext.getCursor());
					itprev.getCursor()->setNext(val);
					itnext.getCursor()->setPrev(val);
				}
				size_++;
				Iterator it = Iterator (head_, tail_, val);
				return it;

			}
			
			/**
			 * Erase the node pointed to by the Iterator's cursor.
			 * 
			 * If the 'pos' iterator does not point to a valid node,
			 * 	throw an std::range_error
			 * 
			 * Return an iterator to the node AFTER the one we erased,
			 * 	or this->end() if we just erased the tail
			 */
			Iterator erase(Iterator pos)
			{
				if (pos.getCursor() == nullptr)
				{
					throw std::range_error("Attempted to use erase with iterator pointing to invalid node");
				}
				//Iterator it = Iterator(head_, tail_, pos.getCursor());
				if (pos.getCursor() == tail_)
				{
					Iterator it = Iterator(head_, tail_, nullptr);
					Node* prev = pos.getCursor()->getPrev();
					delete pos.getCursor();
					tail_ = prev;
					size_--;
					return it;
				}
				else if (pos.getCursor() == head_)
				{
					Node* next = pos.getCursor()->getNext();
					Iterator it = Iterator(head_, tail_, pos.getCursor()->getNext());
					delete pos.getCursor();
					head_ = next;
					size_--;
					return it;
				}
				else
				{
					Node* prev = pos.getCursor()->getPrev();
					Node* next = pos.getCursor()->getNext();
					Iterator it = Iterator(head_, tail_, pos.getCursor()->getNext());
					delete  pos.getCursor();
					prev->setNext(next);
					next->setPrev(prev);
					size_--;
					return it;
				}
				//return it;
			}
			
			/**
			 * Add an element just after the one pointed to by the 'pos' iterator
			 * 
			 * Should return an iterator pointing to the newly created node
			 */
			//Main problem here
			Iterator push_after(Iterator pos, const T& value)
			{
				if ((pos.getCursor() == tail_) || (pos.getCursor() == nullptr))
				{
					Node* val = new Node(value);
					val->setPrev(tail_);
					tail_->setNext(val);
					tail_ = val;
					size_++;
					Iterator it = Iterator (head_, tail_, val);
					return it;
				}
				Node* val = new Node(value);
				val->setPrev(pos.getCursor());
				val->setNext(pos.getCursor()->getNext());
				pos.getCursor()->setNext(val);
				size_++;
				Iterator it = Iterator (head_, tail_, val);
				return it;
			}
			
			/**
			 * Add a new element to the front of our list.
			 */
			void push_front(const T& value)
			{
				Node* val = new Node(value);
				if (head_ == nullptr)
				{
					head_ = val;
					tail_ = val;
					size_++;
				}
				else
				{
					val->setNext(head_);
					head_->setPrev(val);
					head_ = val;
					size_++;
				}
			}
			
			/**
			 * Add an element to the end of this list.
			 * 
			 * Should return an iterator pointing to the newly created node.
			 */
			Iterator push_back(const T& value)
			{
				//std::cout << "Running pushback" << std::endl;
				Node* val = new Node(value);
				if (head_ == nullptr)
				{
					if (tail_ != nullptr)
					{
						throw std::range_error("Attempted to push back, head was null but tail was not null");
					}
					if (size_ != 0)
					{
						throw std::range_error("Pushed back on empty list, size was not 0");
					}
					//std::cout << "Trying to push new node val into empty list" << std::endl;
					tail_ = val;
					head_ = val;
					size_++;
					//std::cout << "Pushing into empty list worked" << std::endl;
				}
				else
				{
					//std::cout << "Trying to push new node val into non empty list" << std::endl;
					tail_->setNext(val);
					val->setPrev(tail_);
					tail_ = val;
					size_++;
					//std::cout << "Pushback on non empty list worked" << std::endl;

				}
				Iterator it = Iterator(head_, tail_, val);
				return it;
			}
			
			/**
			 * Remove the node at the front of our list
			 * 
			 * Should throw an exception if our list is empty
			 */
			void pop_front()
			{
				//AP123: 741 pop_front, how do i call dtor on head_
				if (head_ == nullptr)
				{
					throw std::range_error("Attempted to pop_front on empty list");
				}
				Node* temp = head_->getNext();
				delete head_;
				head_ = temp;
				size_ -= 1;
			}
			
			/**
			 * Remove the node at the end of our list
			 * 
			 * Should throw an exception if our list is empty
			 */
			void pop_back()
			{
				if (head_ == nullptr)
				{
					throw std::range_error("Attempted to use pop_back on empty list");
				}
				if (head_ == tail_)
				{
					delete head_;
					head_ = nullptr;
					size_--;
				}
				else
				{
					//std::cout << "Pop back, popped " << std::to_string(tail_->getElement()) << std::endl;
					Node* temp = tail_->getPrev();
					temp->setNext(nullptr);
					delete tail_;
					tail_ = temp;
					size_--;
				}
			}
			
			/**
			 * Return a reference to the element at the front.
			 * 
			 * Throw an exception if the list is empty
			 */
			T& front()
			{
				if (head_ == nullptr)
				{
					throw std::range_error ("Used front() when list is empty");
				}
				return head_->getElement();
			}
			
			/**
			 * Return a reference to the element at the back.
			 * 
			 * Throw an exception if the list is empty
			 */
			T& back()
			{
				if (head_ == nullptr)
				{
					throw std::range_error ("Used back() when list is empty");
				}
				return tail_->getElement();
			}
			
			/**
			 * Return the element at an index
			 * 
			 * Should throw a range_error is out of bounds
			 */
			T& at(size_t index)
			{
				//std::cout << "Running at function" << std::endl;
				if ((index >= size_) || (index < 0))
				{
					throw std::range_error ("Attempted to use at for invalid index");
				}
				Iterator it = Iterator (this->head(), this->tail(), this->head());
				for (size_t i = 0 ; i < index ; i++)
				{
					//std::cout << "It is pointing to " << std::to_string(it.getCursor()->getElement()) << std::endl;
					it.cursor_ = it.getCursor()->getNext();
					//std::cout << "It is now pointing to " << std::to_string(it.getCursor()->getElement()) << std::endl;
				}
				return it.getCursor()->getElement();
			}

			//HELPER
			void Print()
			{
				int index = 0;
				std::cout << "Printing list of size " << this->size() << " head pointer is " << std::to_string(this->head_->getElement()) << std::endl << std::endl;
				//Seg fault before for loop even iterates
				for (Iterator it = this->begin() ; !(it.isAtEnd()) ; it++)
				{
					std::cout << "Index " << std::to_string(index) << " Element " << std::to_string(it.getCursor()->getElement()) << ", " << std::endl;
					index++;
				}
				std::cout << std::endl;
				std::cout << "FINISHED PRINTING" << std::endl;
				std::cout << std::endl;
			}
			
			/**
			 * Reverse the current list
			 */
			void reverse()
			{
				Iterator it = Iterator(head_, tail_, tail_);
				for (size_t i = size_ ; i > 0 ; i--)
				{
					it.getCursor()->setNext(it.getCursor()->getPrev());
					it.cursor_ = it.getCursor()->getPrev();
				}
			}
			
			/**
			 * I bet you're happy I'm not making you do this.
			 * No tests will be run against this function,
			 * 	but fesel free to try it out, as a challenge!
			 * 
			 * If I were doing this and didn't care too much for efficiency,
			 * 	I would probably create an extra helper function to swap two
			 * 	positions in the current list.
			 * Then I would simply sweep through the list and perform
			 *  the bubble-sort algorithm. Perhaps selection sort.
			 * 
			 * If you want a huge challenge, try implementing quicksort.
			 * 
			 * (but again, don't worry about this method; it will not be tested)
			 */
			void sort()
			{
				//	TODO: Your code here
			}
			
			/**
			 * Assignment operator
			 * 
			 * Clear this list and fill it with the others' values
			 * (by value, not by reference)
			 * 
			 * Return a reference to this list
			 */

			DoublyLinkedList<T>& operator =(DoublyLinkedList<T>& other)
			{
				//std::cout << "Running overload = " << std::endl;
				//std::cout << "Other's size is " << std::to_string(other.size()) << std::endl;
				clear();
				for (Iterator itother = other.begin() ; !(itother.isAtEnd()) ; itother++)
				{
					//std::cout << "Attempt pushback in operator =" << std::endl;
					//std::cout << itother.getCursor() << std::endl;
					this->push_back(itother.getCursor()->getElement());
					//std::cout << "Iterator cursor is pointing to " << std::to_string(itother.getCursor()->getElement()) << std::endl << std::endl;
				}
				return *this;
			}
			
			/**
			 * Return true if the lists are "equal"
			 * 
			 * "Equal" here is defined as:
			 * - Same size
			 * - Elements at the same indexes would return true for their own comparison operators
			 * 
			 * In other words: "They contain all the same values"
			 * (no need for their pointers or addresses to be the same)
			 */
			bool operator ==(DoublyLinkedList<T>& other)
			{
				if (size_ != other.size())
				{
					return false;
				}
				Iterator itother = Iterator(other.head_, other.tail_, other.head_);
				for (Iterator it = Iterator(head_, tail_, head_) ; it.getCursor() == nullptr ; it++)
				{
					if (it.getCursor()->getElement() != itother.getCursor()->getElement())
					{
						return false;
					}
					itother++;
				}
				return true;

			}
			
			/**
			 * Return true if the lists are "not equal"
			 * 
			 * See the operator== stub for definition of "equal"
			 */
			bool operator !=(DoublyLinkedList<T>& other)
			{
				if (size_ != other.size())
				{
					return true;
				}
				Iterator itother = Iterator(other.head_, other.tail_, other.head_);
				for (Iterator it = Iterator(head_, tail_, head_) ; it.getCursor() == nullptr ; it++)
				{
					if (it.getCursor()->getElement() != itother.getCursor()->getElement())
					{
						return true;
					}
					itother++;
				}
				return false;

			}
		private:
			
			Node* head_ = nullptr;
			Node* tail_ = nullptr;
			size_t size_ = 0;
	};
}

#endif
