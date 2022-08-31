#pragma once
#include "yaPair.h"

//#define REDBLACK 
using namespace std;

namespace ya
{
//#ifdef REDBLACK
//	enum Color
//	{
//		RED,
//		BLACK
//	};
//
//	//int 기준만 구현
//	template <typename kT, typename vT>
//	class map
//	{
//	public:
//		class Node
//		{
//		public:
//			kT key;
//			vT value;
//			Color color;
//			Node* parent;
//			Node* left;
//			Node* right;
//
//			Node()
//				: key(NULL)
//				, value(NULL)
//				, color(Color::BLACK)
//				, parent(nullptr)
//				, left(nullptr)
//				, right(nullptr)
//			{
//
//			}
//		};
//
//	public:
//		map()
//		{
//			mLeafNode = new Node();
//			mRoot = mLeafNode;
//		}
//		~map()
//		{
//
//		}
//
//	public:
//		void insert(std::pair<kT, vT> pair)
//		{
//			Node* buf = mRoot;
//			Node* to_addnode_parent = nullptr;
//			Node* to_addnode = new Node();
//			to_addnode->key = pair.first;
//			to_addnode->value = pair.second;
//			to_addnode->color = Color::RED;
//			to_addnode->parent = nullptr;
//			to_addnode->left = mLeafNode;
//			to_addnode->right = mLeafNode;
//
//
//			while (buf != mLeafNode)
//			{
//				to_addnode_parent = buf;
//				if (buf->key < pair.first)
//					buf = buf->right;
//				else
//					buf = buf->left;
//			}
//			to_addnode->parent = to_addnode_parent;
//
//			if (to_addnode_parent == nullptr)
//				mRoot = to_addnode;
//			else if (to_addnode->key > to_addnode_parent->key)
//				to_addnode_parent->right = to_addnode;
//			else
//				to_addnode_parent->left = to_addnode;
//
//			//z가 root노드라면
//			if (to_addnode->parent == nullptr)
//			{
//				to_addnode->color = BLACK;
//				return;
//			}
//			// z의 부모노드가 root노드라면 Fix Up 필요없이 red컬러로 붙여주면 된다.
//			if (to_addnode->parent->parent == nullptr)
//			{
//				return;
//			}
//			insertFixUp(to_addnode);
//
//			return;
//		}
//		void insertFixUp(Node* node)
//		{
//			//root 노드가 아니고 부모색이 red 라면
//			while (node != mRoot && node->parent->color == Color::RED)
//			{
//				Node* grandParent = node->parent->parent;
//				Node* uncle = (node->parent == grandParent->left) ? grandParent->right : grandParent->left;
//				bool side = (node->parent == grandParent->left) ? true : false;
//
//				if (uncle && uncle->color == Color::RED)
//				{
//					//Coloring
//					node->parent->color = Color::BLACK;
//					uncle->color = Color::BLACK;
//					grandParent->color = Color::RED;
//					node = grandParent;
//				}
//				else
//				{
//					//case 2
//					//side == true ) 왼쪽 자식 인 경우이다.
//					//side == false ) 오른쪽 자식 인 경우이다. 
//					if (node == (side ? node->parent->right : node->parent->left))
//					{
//						node = node->parent;
//						side ? RotateLeft(node) : RotateRight(node);
//					}
//
//					node->parent->color = Color::BLACK;
//					grandParent->color = Color::RED;
//					side ? RotateRight(node) : RotateLeft(node);
//				}
//			}
//			mRoot->color = Color::BLACK;
//		}
//		void Transplant(Node* dest, Node* source)
//		{
//			if (dest->parent == nullptr)
//				mRoot = source;
//			else if (dest == dest->parent->left)
//				dest->parent->left = source;
//			else
//				dest->parent->right = source;
//
//			source->parent = dest->parent;
//		}
//		void RotateLeft(Node* node)
//		{
//			Node* buf;
//			buf = node->right;
//
//			node->right = buf->left;
//			if (buf->left != mLeafNode)
//			{
//				buf->left->parent = node;
//			}
//			buf->parent = node->parent;
//
//			if (!node->parent)
//			{
//				mRoot = node;
//			}
//			else if (node == node->parent->left)
//			{
//				node->parent->left = node;
//			}
//			else
//			{
//				node->parent->right = node;
//			}
//			node->parent = buf;
//			buf->left = node;
//		}
//		void RotateRight(Node* node)
//		{
//			Node* buf;
//
//			buf = node->left;
//			node->left = buf->right;
//			if (buf->right != leafNode)
//			{
//				buf->right->parent = node;
//			}
//			buf->parent = node->parent;
//
//			if (!node->parent)
//			{
//				root = buf;
//			}
//			else if (node == node->parent->left)
//			{
//				node->parent->left = buf;
//			}
//			else
//			{
//				node->parent->right = buf;
//			}
//			node->parent = buf;
//			buf->right = node;
//		}
//
//	private:
//		Node* mRoot;
//		Node* mLeafNode;;
//	};
//
//#else
//
//
//	template <typename kT, typename vT>
//	class map
//	{
//	public:
//		class Node
//		{
//		public:
//			kT key;
//			vT value;
//			int height;
//			Node* left;
//			Node* right;
//
//		public:
//			Node()
//				: key(NULL)
//				, value(NULL)
//				, height(0)
//				, left(nullptr)
//				, right(nullptr)
//			{
//
//			}
//			Node(kT& key, vT& value)
//				: key(key)
//				, value(value)
//				, height(0)
//				, left(nullptr)
//				, right(nullptr)
//			{
//
//			}
//			~Node() = default;
//		};
//
//	public:
//		map()
//		{
//
//		}
//		~map()
//		{
//
//		}
//
//		void insert(std::pair<kT, vT> pair)
//		{
//			if (mRoot == nullptr)
//			{
//				mRoot = newNode(pair);
//				return;
//			}
//			insert(pair, mRoot, 0);
//			
//
//			if (!(mRoot && mRoot->left && mRoot->right))
//				return;
//
//			int rootHeight = mRoot->height;
//			int leftHeight = mRoot->left->height;
//			int rightHeight = mRoot->right->height;
//
//			if ((rootHeight - rightHeight) > 2)
//			{
//				//LL_Rotation();
//				LR_Rotation();
//				
//				updateHeight(mRoot, rootHeight - 1);
//			}
//			if ((rootHeight - leftHeight) > 2)
//			{
//				RR_Rotation();
//				updateHeight(mRoot, rootHeight - 1);
//			}
//		}
//
//	private:
//		Node* newNode(std::pair<kT, vT> pair)
//		{
//			Node* node = new Node(pair.first, pair.second);
//			return node;
//		}
//
//		void updateHeight(Node* curNode, int height)
//		{
//			if (curNode == nullptr)
//				return;
//
//			updateHeight(curNode->left, height - 1);
//			curNode->height = height;
//
//			updateHeight(curNode->right, height - 1);
//			curNode->height = height;
//
//		}
//
//		Node* findLeafNode()
//		{
//
//		}
//
//		void insert(std::pair<kT, vT> pair, Node* curNode, size_t height)
//		{
//			if (pair.first < curNode->key)
//			{
//				if (curNode->left != nullptr)
//					insert(pair, curNode->left, height + 1);
//				else
//					curNode->left = newNode(pair);
//
//				curNode->height = curNode->left->height + 1;
//			}
//			else
//			{
//				if (curNode->right != nullptr)
//					insert(pair, curNode->right, height + 1);
//				else
//					curNode->right = newNode(pair);
//
//				curNode->height = curNode->right->height + 1;
//			}
//		}
//		void insertNode(Node* addNode, Node* curNode)
//		{
//			if (curNode->value < addNode->value)
//			{
//				if (curNode->left != nullptr)
//					insertNode(addNode, curNode->left);
//				else
//					curNode->left = addNode;
//			}
//			else
//			{
//				if (curNode->right != nullptr)
//					insertNode(addNode, curNode->right);
//				else
//					curNode->right = addNode;
//			}
//		}
//
//		void LL_Rotation()
//		{
//			Node* prevRoot = mRoot;
//			Node* leftRight = mRoot->left->right;
//			mRoot = mRoot->left;
//			mRoot->right = prevRoot;
//			prevRoot->left = nullptr;
//			insertNode(leftRight, mRoot);
//		}
//		void RR_Rotation()
//		{
//			Node* prevRoot = mRoot;
//			Node* rightLeft = mRoot->right->left;
//			mRoot = mRoot->right;
//			mRoot->left = prevRoot;
//			prevRoot->right = nullptr;
//			insertNode(rightLeft, mRoot);
//		}
//		void LR_Rotation()
//		{
//			Node* prevRoot = mRoot;
//			Node* leftRight = mRoot->right->left;
//			mRoot = mRoot->right;
//			mRoot->left = prevRoot;
//			prevRoot->right = nullptr;
//			insertNode(rightLeft, mRoot);
//		}
//		void RL_Rotation()
//		{
//
//		}
//
//	private:
//		Node* mRoot;
//	};
//#endif // REDBLACK



	// 클래스를 정의합니다.
	template<typename kT, typename vT>
	class map
	{
	public:
		struct Node
		{
			kT key;
			vT data;
			struct Node* left;
			struct Node* right;
		};

	public:
		map()
		{
			mRoot = NULL;
		}
		// AVL 트리의 높이를 출력합니다.
		int height(Node* temp)
		{
			int h = 0;
			if (temp != NULL)
			{
				// 재귀적으로 왼쪽 혹은 오른쪽으로 검색합니다.
				int left = height(temp->left);
				int right = height(temp->right);
				int maxHeight = max(left, right);
				h = maxHeight + 1;
			}
			return h;
		}
		// 균형인수(높이의 차이)를 반환합니다.
		int diff(Node* temp)
		{
			// 왼쪽 자식의 높이와 오른쪽 자식의 높이 차이를 반환합니다.
			int left = height(temp->left);
			int right = height(temp->right);
			int factor = left - right;
			return factor;
		}
		// 회전 함수입니다.
		Node* rr(Node* parent)
		{
			// 말이 회전이지 그냥 부모 노드의 오른쪽 자식노드와 데이터를 교환하는 것입니다.
			Node* temp;
			temp = parent->right;
			parent->right = temp->left;
			temp->left = parent;
			return temp;
		}
		Node* ll(Node* parent)
		{
			// RR 회전과 반대입니다.
			Node* temp;
			temp = parent->left;
			parent->left = temp->right;
			temp->right = parent;
			return temp;
		}
		Node* lr(Node* parent)
		{
			// LR 회전은 왼쪽 자식을 기준으로 RR, 본인을 기준으로 LL회전합니다.
			Node* temp;
			temp = parent->left;
			parent->left = rr(temp);
			return ll(parent);
		}
		Node* rl(Node* parent)
		{
			// LR 회전과 반대입니다.
			Node* temp;
			temp = parent->right;
			parent->right = ll(temp);
			return rr(parent);
		}
		Node* balance(Node* temp)
		{
			int factor = diff(temp);
			// 왼쪽 서브트리쪽으로 삽입이 되어 균형이 깨진 경우입니다.
			if (factor > 1)
			{
				// 그 왼쪽 자식노드에 문제가 발생했습니다.
				if (diff(temp->left) > 0)
				{
					temp = ll(temp);
				}
				// 그 오른쪽 자식 노드에 문제가 발생했습니다.
				else
				{
					temp = lr(temp);
				}
			}
			else if (factor < -1)
			{
				if (diff(temp->right) > 0)
				{
					temp = rl(temp);
				}
				else
				{
					temp = rr(temp);
				}
			}
			return temp;
		}
		
		void insert(std::pair<kT, vT> pair)
		{
			mRoot = insert(mRoot, pair);
		}

		Node* insert(Node* node, std::pair<kT, vT> pair)
		{
			// 현재 트리가 비었을 때
			if (node == NULL)
			{
				node = new Node;
				node->key = pair.first;
				node->data = pair.second;
				node->left = NULL;
				node->right = NULL;

				if(mRoot == nullptr)
					mRoot = node;

				return node;
			}
			else if (pair.first < node->key)
			{
				node->left = insert(node->left, pair);
				node = balance(node);
			}
			// 크거나 같은 경우 오른쪽 서브트리에 삽입합니다.
			else if (pair.first >= node->key)
			{
				node->right = insert(node->right, pair);
				node = balance(node);
			}

			return node;
		}

		//void display(Node* ptr, int level)
		//{
		//	int i;
		//	// 현재 트리가 비어있지 않은 경우입니다.
		//	if (ptr != NULL)
		//	{
		//		display(ptr->right, level + 1);
		//		printf("\n");
		//		// 현재 루트 노드인 경우입니다.
		//		if (ptr == mRoot)
		//		{
		//			cout << "Root -> ";
		//		}
		//		// i가 현레벨보다 낮고 루트가 아닌 경우일 때까지 입니다.
		//		for (i = 0; i < level && ptr != mRoot; i++)
		//		{
		//			cout << "        ";
		//		}
		//		// 자신의 위치에 데이터를 출력합니다.
		//		cout << ptr->data;
		//		// 왼쪽 노드도 출력해줍니다.
		//		display(ptr->left, level + 1);
		//	}
		//}

		void circulateMap()
		{
			preorder(mRoot);
		}

		void preorder(Node* node)
		{
			if (node == NULL)
				return;
			cout << node->key << "  ";
			preorder(node->left);
			preorder(node->right);
		}

		void inorder(Node* node)
		{
			if (node == NULL)
				return;
			inorder(node->left);
			cout << node->key << "  ";
			inorder(node->right);
		}

		void postorder(Node* node)
		{
			if (node == NULL)
				return;
			postorder(node->left);
			postorder(node->left);
			cout << node->key << "  ";
		}

	private:
		Node* mRoot;
	};


	

}