/**
 * SD, 2021
 * 
 * Lab #9, BST & Heap
 * 
 * Task #1 - Binary Search Tree implementation
 */

#include "bst.h"
#include "utils.h"

/**
 * Helper function to create a node
 * @data: the data to be added in the node
 * @data_size: data's size
 */
static bst_node_t *__bst_node_create(void *data, size_t data_size)
{
    bst_node_t *bst_node;  

    bst_node = malloc(sizeof(*bst_node));

    DIE(bst_node == NULL, "bst_node malloc");

    bst_node->left = bst_node->right = NULL;

    bst_node->data = malloc(data_size);
    DIE(bst_node->data == NULL, "bst_node->data malloc");
    memcpy(bst_node->data, data, data_size);

    return bst_node;
}

bst_tree_t *bst_tree_create(size_t data_size,
                            int (*cmp_f)(const void *, const void *))
{
    bst_tree_t *bst_tree;

    bst_tree = malloc(sizeof(*bst_tree));
    DIE(bst_tree == NULL, "bst_tree malloc");

    bst_tree->root  = NULL;
    bst_tree->data_size = data_size;
    bst_tree->cmp   = cmp_f;

    return bst_tree;
}

void bst_tree_insert(bst_tree_t *bst_tree, void *data)
{
    int rc;
    bst_node_t *root    = bst_tree->root;
    bst_node_t *parent  = NULL;
    bst_node_t *node    = __bst_node_create(data, bst_tree->data_size);

    if(!root) {
        bst_tree->root = node;
    } else {
        while(1) {
            rc = bst_tree->cmp(node->data, root->data);
            if(rc < 0) {
                parent = root;
                root = root->left;
                if(!root) {
                    parent->left = node;
                    break;
                }
            } else if(rc > 0) {
                parent = root;
                root = root->right;
                if(!root) {
                    parent->right = node;
                    break;
                }
            }
        }
    }
}

/**
 * Helper function to remove an element from a BST
 * @bst_node: the binary search subtree's root where to remove the element from
 * @data: the data that is contained by the node which has to be removed
 * @data_size: data size
 * @cmp: function used to compare the data contained by two nodes
 */
static bst_node_t *__bst_tree_remove(bst_node_t *bst_node,
                                    void *data, size_t data_size,
                                    int (*cmp)(const void *, const void *))
{
    int rc;
    bst_node_t *tmp;

    if (!bst_node)
        return NULL;

    rc = cmp(data, bst_node->data);

    if (rc < 0) {
        bst_node->left = __bst_tree_remove(bst_node->left, data, data_size, cmp);
    } else if (rc > 0) {
        bst_node->right = __bst_tree_remove(bst_node->right, data, data_size, cmp);
    } else {
        if(!bst_node->left && !bst_node->right) {
            free(bst_node->data);
            free(bst_node);
            return NULL;
        } else {
            if(!bst_node->left || !bst_node->right) {
                if(!bst_node->left)
                    tmp = bst_node->right;
                else
                    tmp = bst_node->left;

                free(bst_node->data);
                free(bst_node);

                return tmp;
            } else {
                tmp = bst_node->right;
                while(1) {
                    if (!tmp)
                        break;
                    tmp = tmp->left;
                }

                memcpy(bst_node->data, tmp->data, data_size);
                bst_node->right = __bst_tree_remove(bst_node->right, tmp->data, data_size, cmp);
            }
        }
    }

    return bst_node;
}

void bst_tree_remove(bst_tree_t *bst_tree, void *data)
{
    bst_tree->root = __bst_tree_remove(bst_tree->root, data,
                                       bst_tree->data_size, bst_tree->cmp);
}

/**
 * Free the left and the right subtree of a node, its data and itself
 * @b_node: the node which has to free its children and itself
 * @free_data: function used to free the data contained by a node
 */
static void __bst_tree_free(bst_node_t *bst_node, void (*free_data)(void *))
{
    if (!bst_node)
        return;

    __bst_tree_free(bst_node->left, free_data);
    __bst_tree_free(bst_node->right, free_data);
    free(bst_node->data);
    free(bst_node);
    bst_node = NULL;
}

void bst_tree_free(bst_tree_t *bst_tree, void (*free_data)(void *))
{
    __bst_tree_free(bst_tree->root, free_data);
    free(bst_tree);
}

static void
__bst_tree_print_inorder(bst_node_t* bst_node, void (*print_data)(void*))
{
	if (!bst_node)
		return;
        
    __bst_tree_print_inorder(bst_node->left, print_data);
    print_data(bst_node->data);
    __bst_tree_print_inorder(bst_node->right, print_data);
}

void
bst_tree_print_inorder(bst_tree_t* bst_tree, void (*print_data)(void*))
{
	__bst_tree_print_inorder(bst_tree->root, print_data);
}
