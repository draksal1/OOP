#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "btree.h"

typedef struct BTreeNode
{
	BTreeItem item;
	struct BTreeNode* right;
	struct BTreeNode* left;
	struct BTreeNode* parent;
}
BTreeNode;

typedef struct BTree
{
	BTreeNode* root;
	size_t keySize;
	size_t valSize;
	int(*compare)(const void*, const void*);
	size_t size;
}
BTree;

size_t find_right(BTree* btree);
size_t find_left(BTree* btree);
void kill_node(BTreeNode* node, void(*destroy)(void*));
static const BTreeNode* keyfind_node(const BTreeNode* node, const BTree* tree, const void* key);
static BTreeNode* node_create(const BTree* btree, const void* key);
void btree_clear_recursive(BTreeNode* node, void(*destroy)(void*));
static BTreeNode* tree_insert_recursive(BTree* btree, BTreeNode* node, const void* key, bool* createFlag, BTreeNode* parrent, int wchild);

static void btree_remove_recursive(BTree* btree, const void* key, void(*destroy)(void*));
//static bool is_left_or_right(BTreeNode* child, BTreeNode* par);

static void delete_root(BTreeNode* node, void(*destroy)(void*), BTree* mainTree);
static BTreeNode* delete_node(BTree* tree, BTreeNode* node, void(*destroy)(void*));

void* btree_create(size_t keySize, size_t valueSize, int(*compare)(const void*, const void*))
{
	if (keySize == 0 || valueSize == 0 || compare == NULL) {
		return NULL;
	}
		BTree* tree = (BTree*)malloc(sizeof(BTree));
		if (!tree) {
			return NULL;
		}
		tree->compare = compare;
		tree->keySize = keySize;
		tree->valSize = valueSize;
		tree->root = NULL;
		tree->size = 0;
	return tree;
}

static BTreeNode* node_create(const BTree* btree, const void* key)
{
	void* result;
		BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
		if (!node) {
			return NULL;
		}
		node->item.value = (void*)malloc(btree->valSize);

		node->item.key = (void*)malloc(btree->keySize);
		if (node->item.key && node->item.value)
		{
			memcpy((void*)node->item.key, key, btree->keySize);

			node->left = NULL;
			node->right = NULL;
			result = node;
			return result;
		}
		free(node->item.value);
		free((void*)node->item.key);
		free(node);
		return NULL;
}

void btree_clear_recursive(BTreeNode* node, void(*destroy)(void*))
{
	if (!node) {
		return;
	}
		btree_clear_recursive(node->left, destroy);
		btree_clear_recursive(node->right, destroy);
		kill_node(node, destroy);
}
void kill_node(BTreeNode* node, void(*destroy)(void*)) {
	if (destroy != NULL) {
		destroy(&node->item);
	}
	free(node->item.value);
	free((void*)node->item.key);
	free(node);
}
void btree_clear(void* btree, void(*destroy)(void*))
{	
	BTree* tree = (BTree*)btree;
	btree_clear_recursive(tree->root, destroy);
	tree->size = 0;
	tree->root = NULL;

}


void* btree_init(
	void* btree,
	size_t keySize,
	size_t valueSize,
	int(*compare)(const void*, const void*),
	void(*destroy)(void*))
{
	if (btree == NULL || keySize == 0 || valueSize == 0 || compare == NULL) {
		return NULL;
	}
	btree_clear(btree, destroy);
	BTree* tree = (BTree*)btree;
	tree->keySize = keySize;
	tree->valSize = valueSize;
	tree->compare = compare;
	return tree;
}

void btree_destroy(void* btree, void(*destroy)(void*))
{
	if (btree != NULL) {
		BTree* tree = (BTree*)btree;
		btree_clear(btree, destroy);
		free(tree);
	}
}

size_t btree_count(const void* btree)
{
	size_t result = INVALID;
	const BTree* tree = (BTree*)btree;
	if (btree != NULL) {
		result = tree->size;
	}
	return result;
}


const BTreeNode* keyfind_node(const BTreeNode* node,const BTree* tree, const void* key)
{
	if (!node)
	{
		return NULL;
	}
	int cmp = tree->compare((void*)node->item.key, key);
	if (cmp < 0) {
		return keyfind_node((void*)node->right,tree, key);
	}
	else if (cmp > 0) {
		return keyfind_node((void*)node->left, tree, key);
	}
	return node;
}

void* btree_item(const void* btree, const void* key)
{
	BTree* tree = (BTree*)btree;
	if (btree != NULL && key != NULL) {
		if (tree->root == NULL) {
			return NULL;
		}
		else {
			const BTreeNode* node = keyfind_node(tree->root, tree, key);
			if (!node) {
				return NULL;
			}
			return node->item.value;
		}
	}
	return NULL;
}
static BTreeNode* tree_insert_recursive(BTree* btree, BTreeNode* node, const void* key, bool* createFlag, BTreeNode* parrent, int wchild)
{	
	if (!node)
	{
		node = node_create(btree, key);
		*createFlag = true;
		btree->size = btree->size + 1;
		if (wchild) {
			parrent->right = node;
		}
		else {
			parrent->left = node;
		}
		node->parent = parrent;
		return node->item.value;
	}
	int cmp = btree->compare(node->item.key, key);
	if (cmp < 0)
	{
		return tree_insert_recursive(btree, node->right, key, createFlag, node, 1);
	}
	else if (cmp> 0)
	{
		return tree_insert_recursive(btree, node->left, key, createFlag, node, 0);
	}
	*createFlag = false;
	return node->item.value;
}

void* btree_insert(void* btree, const void* key, bool* createFlag)
{
	BTree* tree = (BTree*)btree;
	if (tree != NULL && key != NULL && createFlag != NULL) {
		*createFlag = false;
			if (!tree->root) {
				*createFlag = true;
				tree->root = node_create(btree, key);
				if (tree->root) {
					tree->size = 1;
					tree->root->parent = NULL;
					return tree->root->item.value;
				}
			}
		return tree_insert_recursive(btree, tree->root, key, createFlag, NULL, 1);
	}
	return NULL;
}


void btree_remove(void* btree, const void* key, void(*destroy)(void*))
{
	BTree* tree = (BTree*)btree;
	if (!tree || !key) {
		return;
	}
	const BTreeNode* node = keyfind_node(tree->root, btree, key);
	if (!node) {
		return;
	}
	btree_erase(tree, (size_t)node, destroy);
}


static BTreeNode* delete_node(BTree* tree, BTreeNode* node_to_delete, void(*destroy)(void*))

{
	BTreeNode* node = NULL;
	if (node_to_delete->left == node_to_delete->right) {
		node = NULL;
	}
	else if (node_to_delete->left == NULL) {
		node = node_to_delete->right;
	}
	else if (node_to_delete->right == NULL) {
		node = node_to_delete->left;
	}

	else {
		node = node_to_delete->right;
		BTreeNode* node2 = node_to_delete->right;
		while (node2->left)  node2 = node2->left;
		node2->left = node_to_delete->left;
		node_to_delete->left->parent = node2;
	}
	if (node != NULL)
		node->parent = node_to_delete->parent;
	kill_node(node_to_delete, destroy);
	tree->size=tree->size-1;
	return node;

}

static void delete_root(BTreeNode* node, void(*destroy)(void*), BTree* mainTree)
{
	if (node->left == NULL && node->right == NULL) {
		kill_node(node, destroy);
		mainTree->root = NULL;
	}
	else if ((node->left != NULL && node->right == NULL) || (node->left == NULL && node->right != NULL)) {
		BTreeNode* tmp;
		if (node->left != NULL) {
			tmp = node->left;
		}
		else {
			tmp = node->right;
		}
		kill_node(node, destroy);
		mainTree->root = tmp;
		tmp->parent = NULL;
	}
	else if (node->left != NULL && node->right != NULL) {
		if (node->right->left == NULL) {
			BTreeNode* tmpRight = node->right;
			BTreeNode* tmpLeft = node->left;
			kill_node(node, destroy);
			mainTree->root = tmpRight;
			tmpRight->parent = NULL;
			mainTree->root->left = tmpLeft;
		}
		else {
			BTreeNode* farLeft;
			for (farLeft = node->right->left; farLeft->left != NULL; farLeft = farLeft->left);
			BTreeNode* tmpRightN = node->right;
			BTreeNode* tmpLeftN = node->left;
			BTreeNode* tmpRightFL = farLeft->right;
			BTreeNode* tmpParentFL = farLeft->parent;
			kill_node(node, destroy);
			farLeft->parent = NULL;
			farLeft->left = tmpLeftN;
			if (tmpLeftN != NULL) {
				tmpLeftN->parent = farLeft;
			}
			farLeft->right = tmpRightN;
			if (tmpRightN != NULL) {
				tmpRightN->parent = farLeft;
			}
			mainTree->root = farLeft;
			tmpParentFL->left = tmpRightFL;
			if (tmpRightFL != NULL) {
				tmpRightFL->parent = tmpParentFL;
			}
		}
	}
}


//0 - left, 1 - right
//static bool is_left_or_right(BTreeNode* child, BTreeNode* par)
//{
//	if (par->left == child) {
//		return false;
//	}
//	else {
//		return true;
//	}
//}

size_t btree_first(const void* btree)
{
	if (btree == NULL) {
		return btree_stop(btree);
	}
	BTree* tree = (BTree*)btree;
	return find_left(tree);
}
size_t find_left (BTree* btree) {
	const BTreeNode* tmp = btree->root;
	if (tmp != NULL) {
		while (tmp->left != NULL) {
			tmp = tmp->left;
		}
		return (size_t)tmp;
	}
	return btree_stop(btree);
}

size_t btree_last(const void* btree)
{
	BTree* tree = (BTree*)btree;
	if (btree == NULL) {
		return btree_stop(tree);
	}
	return find_right(tree);
}

size_t find_right(BTree* btree) {
	BTreeNode* tmp = btree->root;
	if (tmp) {
		while (tmp->right) {
			tmp = tmp->right;
		}
		return (size_t)tmp;
	}
	return btree_stop(btree);
}

size_t btree_stop(const void* btree)
{
	(void)btree;
	return (size_t)NULL;
}

void* btree_current(const void* btree, size_t item_id)
{
	if (btree != NULL && item_id != btree_stop(btree)) {
		BTreeNode* node = (BTreeNode*)item_id;
		return &node->item;
	}
	return NULL;
}

void btree_erase(void* btree, size_t item_id, void(*destroy)(void*))

{

	if (btree == NULL || item_id == btree_stop(btree))
		return;
	BTree* tree = (BTree*)btree;
	BTreeNode* node = (BTreeNode*)item_id;
	BTreeNode* parent = node->parent;
	if (parent == NULL)
		tree->root = delete_node(tree, node, destroy);
	else if (node->parent->left == node)
		parent->left = delete_node(tree, node, destroy);
	else
		parent->right = delete_node(tree, node, destroy);
}

size_t btree_next(const void* btree, size_t item_id)
{
	if (btree == NULL || item_id == btree_stop(btree)) {
		return btree_stop(btree);
	}
	const BTree* tree = (BTree*)btree;
	BTreeNode* node = (BTreeNode*)item_id;
	if (item_id != btree_last(btree)) {
		if (node->right != NULL) {
			BTreeNode* tmp = node->right;
			while (tmp->left) {
				tmp = tmp->left;
			}
			return (size_t)tmp;
		}
		else {
			BTreeNode* tmp = node;
			while (tmp->parent) {
				if (tmp->parent->left == tmp) {
					return (size_t)tmp->parent;
				}
				tmp = tmp->parent;
			}
			return btree_stop(btree);
		}
	
	}
	return btree_stop(btree);
}

size_t btree_prev(const void* btree, size_t item_id)
{
	if (btree == NULL || item_id == btree_stop(btree)) {
		return btree_stop(btree);
	}
	const BTree* tree = (BTree*)btree;
	BTreeNode* node = (BTreeNode*)item_id;
	if (item_id == btree_first(btree)) {
		return btree_stop(btree);
	}
	else if (node->left != NULL) {
		BTreeNode* tmp = node->left;
		while (tmp->right) {
			tmp = tmp->right;
		}
		return (size_t)tmp;
	}
	else {
		BTreeNode* tmp = node;
		while (tmp->parent) {
			if (tmp->parent->right == tmp) {
				return (size_t)tmp->parent;
			}
			tmp = tmp->parent;
		}
		return btree_stop(btree);
	}
	return btree_stop(btree);
}