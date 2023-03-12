#include "BVHTree.h"


BVHTree::BVHTree()
{
	root = NULL;

}

BVHTree::~BVHTree()
{
	deleteTree(root);
	root = NULL;
}

void BVHTree::addBVHMember(AABB objectArea, std::string name)
{
	BVHTreeNode* newNode = new BVHTreeNode(objectArea, name, true);
	map[name] = newNode;
	if (root == NULL)
	{
		root = newNode;	
	}
	else if (root != NULL && root->isLeaf)   //if we have only one node in tree
	{
		
		AABB combined = root->aabb + objectArea;
		BVHTreeNode* branch = new BVHTreeNode(combined, "branch", false);
		branch->rightChild = root;
		branch->leftChild = newNode;
		root = branch;
		root->leftChild->parent = root;
		root->rightChild->parent = root;
	}
	else
	{
		BVHTreeNode* temp = root;
		while (!temp->isLeaf)           //to find where to add newNode
		{
			int increaseInRightTreeSize = AABB::unionArea(newNode->aabb,
				temp->rightChild->aabb) - temp->rightChild->aabb.getArea();
			int increaseInLeftTreeSize = AABB::unionArea(newNode->aabb,
				temp->leftChild->aabb) - temp->leftChild->aabb.getArea();
			if (increaseInRightTreeSize < increaseInLeftTreeSize)
			{
				temp = temp->rightChild;
			}
			else
			{
				temp = temp->leftChild;
			}
		}
		AABB combined = temp->aabb + objectArea;
		BVHTreeNode* branch = new BVHTreeNode(combined, "branch", false);
		branch->rightChild = temp;
		branch->leftChild = newNode;
		if (temp->parent->rightChild == temp)        //following if else statements is for to determine the sibling of branch
		{
			temp->parent->rightChild = branch;
		}
		else
		{
			temp->parent->leftChild = branch;
		}
		branch->parent = temp->parent;
		branch->leftChild->parent = branch;
		branch->rightChild->parent = branch;

		BVHTreeNode* sibling;
		while (branch->parent != NULL)   //update the AABB of hte parent nodes
		{
			if (branch->parent->rightChild != branch)        //following if else statements is for to determine the sibling of branch
			{
				sibling = branch->parent->rightChild;
			}
			else
			{
				sibling = branch->parent->leftChild;
			}
			branch->parent->aabb = branch->aabb + sibling->aabb;
			branch = branch->parent;
		}
	}	
}
void BVHTree::removeBVHMember(std::string name)
{
	BVHTreeNode* temp = map[name];
	BVHTreeNode* sibling;
	map.erase(name);
	if (temp->parent != NULL) {                //added after grading
		if (temp->parent->rightChild != temp)        //following if else statements is for to determine the sibling of branch
		{
			sibling = temp->parent->rightChild;
		}
		else
		{
			sibling = temp->parent->leftChild;
		}
		if (sibling->parent->parent == NULL)
		{
			root = sibling;

		}
		else  //remove branch and leaf node and adjust the three accordingly
		{
			if (temp->parent->parent->leftChild == temp->parent)
			{
				temp->parent->parent->leftChild = sibling;
				sibling->parent = temp->parent->parent;
			}
			else
			{
				temp->parent->parent->rightChild = sibling;
				sibling->parent = temp->parent->parent;
			}

		}

		delete temp->parent;
		temp->parent = NULL;
		delete temp;
		temp = NULL;
		root->parent = NULL;
	}
	else { root = NULL; }           //added after grading
	
}

void BVHTree::moveBVHMember(std::string name, AABB newLocation)
{
	BVHTreeNode* temp = map[name];

	if (temp->parent != NULL && temp->parent->aabb.contains(newLocation)) //changed after grading temp->parent != NULL was added
	{
		temp->aabb = newLocation;
	}
	else
	{
		removeBVHMember(name);
		addBVHMember(newLocation, name);
	}
}
std::vector<std::string> BVHTree::getCollidingObjects(AABB object)
{
	vector<string> list;
	BVHTreeNode* temp = root;
	createList(temp, object, list);
	return list;
}
void BVHTree::printNode(std::ostream &out, BVHTreeNode *node, int level) {
	if (root == nullptr) return;
	for (int i = 0; i < level; i++) {
		out << "  ";
	}
	if (!node->isLeaf) {
		out << "+ branch || ";
		node->aabb.printAABB(out);
		out << std::endl;
		printNode(out, node->rightChild, level + 1);
		printNode(out, node->leftChild, level + 1);
	}
	else {
		out << "- ";
		if (node->parent) {
			if (node->parent->rightChild == node)
				out << "R ";
			else
				out << "L ";
		}
		out << "- leaf: " << node->name << " || ";
		node->aabb.printAABB(out);
		out << std::endl;
	}
}
void  BVHTree::createList(BVHTreeNode* node, AABB object, vector<string> & list)
{
	if (node == NULL)
		return;

	
	if (node->aabb.collide(object))
	{
		createList(node->leftChild, object, list);
		createList(node->rightChild, object, list);
	}

	if (node->isLeaf && node->aabb.collide(object))
	{
		list.push_back(node->name);
	}
}
void BVHTree::deleteTree(BVHTreeNode* node)
{
	if (node == NULL) return;

	/* first delete both subtrees */
	deleteTree(node->leftChild);
	deleteTree(node->rightChild);

	/* then delete the node */
	delete node;
}
std::ostream &operator<<(std::ostream &out, BVHTree &tree) {
	tree.printNode(out, tree.root, 0);
	return out;
}