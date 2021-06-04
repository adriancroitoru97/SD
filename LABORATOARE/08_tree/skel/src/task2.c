/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Task #2 - <resume_or_paste_the_task_here>
 */

#include "binary_tree.h"

void print_data(void *data)
{
    printf("%d ", *(int *) data);
}

int max(int a, int b) {
	if (a > b)
		return a;

	return b;
}

int height(struct b_node_t* node)
{
    if (!node)
        return 0;

    return 1 + max(height(node->left), height(node->right));
}

int isBalanced(struct b_node_t* root)
{
	if (!root)
        return 1;

    int left_h = height(root->left);
    int right_h = height(root->right);
 
    if (abs(left_h - right_h) <= 1 && isBalanced(root->left) && isBalanced(root->right))
        return 1;
 
    return 0;
}

int main(void)
{
	int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    b_tree_t *tree = b_tree_create(sizeof(int));
    for (int i = 0; i < 10; i++) {
    	b_tree_insert(tree, &v[i]);
    }

    b_tree_print_preorder(tree, print_data);

    if (isBalanced(tree->root))
        printf("Tree is balanced\n");
    else
        printf("Tree is not balanced\n");


    b_tree_free(tree, free);
    exit(EXIT_FAILURE);
}
