#pragma once
#include <iostream>

namespace ya
{
	
	template <typename T>
	class Node
	{
	public:
		Node()
		{
			mData = NULL;
			mNext = nullptr;
			mPrev = nullptr;
		}
		Node(const T data)
		{
			mData = data;
			mNext = nullptr;
			mPrev = nullptr;
		}
		~Node()
		{

		}

	public:
		T mData;
		Node<T>* mNext;
		Node<T>* mPrev;
	};

	template <typename T>
	class list
	{
	public:
		class iterator
		{
		public:
			iterator()
			{
				mPtr = nullptr;
			}
			iterator(Node<T>* ptr)
			{
				mPtr = ptr;
			}
			iterator(const iterator& iter)
			{
				mPtr = iter.mPtr;
			}
			Node<T>* getPtr()
			{
				return mPtr;
			}
			T& operator*()
			{
				if (mPtr != nullptr)
					return mPtr->mData;
			}
			iterator& operator ++()
			{
				if (mPtr != nullptr 
					&& mPtr->mNext != nullptr) 
				{
					mPtr = mPtr->mNext;
				}

				return *this;
			}
			iterator& operator --()
			{
				if (mPtr != nullptr
					&& mPtr->mNext != nullptr)
				{
					mPtr = mPtr->mPrev;
				}

				return *this;
			}
			iterator operator ++(int)
			{
				iterator l_tmp(*this);
				if (mPtr != nullptr
					&& mPtr->mNext != nullptr)
				{
					mPtr = mPtr->mNext;
				}

				return l_tmp;
			}
			iterator operator --(int)
			{
				iterator l_tmp(*this);
				if (mPtr != nullptr
					&& mPtr->mNext != nullptr)
				{
					mPtr = mPtr->mPrev;
				}

				return l_tmp;
			}
			const bool operator ==(const iterator& other)
			{
				return this->mPtr == other.mPtr;
			}
			const bool operator !=(iterator& other)
			{
				return !(*this == other);
			}
			iterator& operator =(iterator& other)
			{
				mPtr = other->mPtr;

				return *this;
			}

		private:
			Node<T>* mPtr;
		};

	public:
		list()
		{
			mfirst = new Node<T>();
			mlast = new Node<T>();
			mfirst->mNext = mlast;
			mfirst->mPrev = nullptr;
			mlast->mNext = nullptr;
			mlast->mPrev = mfirst;
			mCount = 0;
		}
		list(const list& other)
		{
			mfirst = other.mfirst;
			mlast = other.mlast;
			mCount = other.mCount;
		}
		~list()
		{
			Node<T>* l_ptr;
			this->mCount = 0;
			while (mfirst != NULL)
			{
				l_ptr = mfirst;
				mfirst = mfirst->mNext;
				delete l_ptr;
			}
		}

		void swap(list<T>& other)
		{
			Node<T>* l_firstTemp, * l_lastTemp;
			l_firstTemp = mfirst;
			l_lastTemp = mlast;
			mfirst = other.mfirst;
			mlast = other.mlast;
			other.mfirst = l_firstTemp;
			other.mlast = l_lastTemp;
		}
		int size() const
		{
			return mCount;
		}
		void insert(T data)
		{
			if (mCount == 0)
			{
				mfirst->mData = data;
				mCount++;
				return;
			}

			Node<T>* to_add = new Node<T>(data);
			Node<T>* buf = mfirst->mNext;
			while (buf != mlast)
			{
				buf = buf->mNext;
			}
			buf->mPrev->mNext = to_add;
			to_add->mNext = buf;
			to_add->mPrev = buf->mPrev;
			buf->mPrev = to_add;
			mCount++;
		}
		void clear()
		{
			Node<T>* buf = mlast->mPrev;
			while (buf != mfirst)
			{
				Node<T>* to_delete = buf;
				
				buf->mPrev->mNext = mlast;
				mlast = buf->mPrev;

				buf = buf->mPrev;

				delete to_delete;
				to_delete = nullptr;
			}
		}
		bool empty()
		{
			if (mCount)
				return 1;

			return 0;
		}
		iterator begin() const
		{
			return iterator(mfirst);
		}
		iterator end() const
		{
			return iterator(mlast);
		}
		iterator erase(iterator iter)
		{
			Node<T>& l_iter = *iter.getPtr();
			Node<T>* l_temp = &l_iter;

			iter++;
			iterator to_return = iter;

			l_iter.mNext->mPrev = l_temp->mPrev;
			l_iter.mPrev->mNext = l_temp->mNext;
			mCount--;
			delete l_temp;

			return to_return;
		}
		void pop_front()
		{
			Node<T>* to_delete = mfirst;
			mfirst = mfirst->mNext;

			delete to_delete;
			to_delete = nullptr;
		}
		void pop_back()
		{
			Node<T>* to_delete = mlast;
			mlast = mlast->mPrev;

			delete to_delete;
			to_delete = nullptr;
		}


	private:
		int mCount;
		Node<T>* mfirst;
		Node<T>* mlast;
	};
}