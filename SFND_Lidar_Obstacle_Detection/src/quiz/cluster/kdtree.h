/* \author Aaron Brown */
// Quiz on implementing kd tree

#ifndef KD_TREE_H
#define KD_TREE_H

#include "../../render/render.h"


// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}

	~Node()
	{
		delete left;
		delete right;
	}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	~KdTree()
	{
		delete root;
	}

	void insertHelper(Node** node, uint depth, std::vector<float> point, int id)
	{
		if(*node == nullptr)
			*node = new Node(point, id);
		else
		{
			unsigned cd = depth % 3;
			if(point[cd] < (*node)->point[cd])
				insertHelper(&((*node)->left), depth+1, point, id);
			else
				insertHelper(&((*node)->right), depth+1, point, id);
		}

	}
	void insert(std::vector<float> point, int id)
	{
		// the function should create a new node and place correctly with in the root 
		insertHelper(&root, 0, point, id);
	}

	void searchHelper(std::vector<float> target, Node * node, int depth, float distannceTol, std::vector<int> &ids)
	{
		if(node!=nullptr)
		{
			if((node->point[0]>=(target[0]-distannceTol))&&(node->point[0]<=(target[0]+distannceTol))
			 &&(node->point[1]>=(target[1]-distannceTol))&&(node->point[1]<=(target[1]+distannceTol))
			 &&(node->point[2]>=(target[2]-distannceTol))&&(node->point[2]<=(target[2]+distannceTol)))
			 {
				float distance = sqrt((node->point[0]-target[0])*(node->point[0]-target[0])+ 
									  (node->point[1]-target[1])*(node->point[1]-target[1])+
									  (node->point[2]-target[2])*(node->point[2]-target[2]));
				if(distance <= distannceTol)
					ids.push_back(node->id);
			 }
			 //check across boundary
			 if((target[depth%3]-distannceTol)< node->point[depth%3])
			 	searchHelper(target, node->left, depth+1, distannceTol, ids);
			 if((target[depth%3]+distannceTol)> node->point[depth%3])
			 	searchHelper(target, node->right, depth+1, distannceTol, ids);
		}
	}
	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{
		std::vector<int> ids;
		searchHelper(target, root, 0, distanceTol, ids);
		return ids;
	}
	

};


#endif

