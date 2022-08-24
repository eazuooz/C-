#pragma once
#include "yaPair.h"


namespace ya
{
	enum Color
	{
		RED,
		BLACK
	};

	//int 기준만 구현
	template <typename kT, typename vT>
	class map
	{
	public:
		class Node
		{
		public:
			kT key;
			vT value;
			Color color;
			Node* parent;
			Node* left;
			Node* right;

			Node() 
				: key(NULL)
				, value(NULL)
				, color(Color::BLACK)
				, parent(nullptr)
				, left(nullptr)
				, right(nullptr)
			{

			}
		};

	public:
		map()
		{
			mLeafNode = new Node();
			mRoot = mLeafNode;
		}
		~map()
		{

		}

	public:
		void insert(std::pair<kT, vT> pair)
		{
			Node* buf = mRoot;
			Node* to_addnode_parent = nullptr;
			Node* to_addnode = new Node();
			to_addnode->key = pair.first;
			to_addnode->value = pair.second;
			to_addnode->color = Color::RED;
			to_addnode->parent = nullptr;
			to_addnode->left = mLeafNode;
			to_addnode->right = mLeafNode;


			while (buf != mLeafNode)
			{
				to_addnode_parent = buf;
				if (buf->key < pair.first)
					buf = buf->right;
				else
					buf = buf->left;
			}
			to_addnode->parent = to_addnode_parent;

			if (to_addnode_parent == nullptr)
				mRoot = to_addnode;
			else if (to_addnode->key > to_addnode_parent->key)
				to_addnode_parent->right = to_addnode;
			else
				to_addnode_parent->left = to_addnode;

			//z가 root노드라면
			if (to_addnode->parent == nullptr)
			{
				to_addnode->color = BLACK;
				return;
			}
			// z의 부모노드가 root노드라면 Fix Up 필요없이 red컬러로 붙여주면 된다.
			if (to_addnode->parent->parent == nullptr)
			{
				return;
			}
			insertFixUp(to_addnode);

			return;
		}

		void insertFixUp(Node* node)
		{
			//root 노드가 아니고 부모색이 red 라면
			while (node != mRoot && node->parent->color == Color::RED)
			{
				Node* grandParent = node->parent->parent;
				Node* uncle = (node->parent == grandParent->left) ? grandParent->right : grandParent->left;
				bool side = (node->parent == grandParent->left) ? true : false;

				if (uncle && uncle->color == Color::RED)
				{
					//Coloring
					node->parent->color = Color::BLACK;
					uncle->color = Color::BLACK;
					grandParent->color = Color::RED;
					node = grandParent;
				}
				else
				{
					//case 2
					//side == true ) 왼쪽 자식 인 경우이다.
					//side == false ) 오른쪽 자식 인 경우이다. 
					if (node == (side ? node->parent->right : node->parent->left))
					{
						node = node->parent;
						side ? RotateLeft(node) : RotateRight(node);
					}

					node->parent->color = Color::BLACK;
					grandParent->color = Color::RED;
					side ? RotateRight(node) : RotateLeft(node);
				}
			}
			mRoot->color = Color::BLACK;
		}
		//dest 에 소스를 이식
		void Transplant(Node* dest, Node* source)
		{
			if (dest->parent == nullptr)
				mRoot = source;
			else if (dest == dest->parent->left)
				dest->parent->left = source;
			else
				dest->parent->right = source;

			source->parent = dest->parent;
		}
		
		void RotateLeft(Node* node)
		{
			Node* buf;
			buf = node->right;

			node->right = buf->left;
			if (buf->left != mLeafNode)
			{
				buf->left->parent = node;
			}
			buf->parent = node->parent;

			if (!node->parent)
			{
				mRoot = node;
			}
			else if (node == node->parent->left)
			{
				node->parent->left = node;
			}
			else
			{
				node->parent->right = node;
			}
			node->parent = buf;
			buf->left = node;
		}

		void RotateRight(Node* node)
		{
			Node* buf;

			buf = node->left;
			node->left = buf->right;
			if (buf->right != leafNode)
			{
				buf->right->parent = node;
			}
			buf->parent = node->parent;

			if (!node->parent)
			{
				root = buf;
			}
			else if (node == node->parent->left)
			{
				node->parent->left = buf;
			}
			else
			{
				node->parent->right = buf;
			}
			node->parent = buf;
			buf->right = node;
		}


	private:
		Node* mRoot;
		Node* mLeafNode;;
	};


}