#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;
    struct node* left;
    struct node* right;
} node;

typedef struct tree {
    node* root;
} tree;

node* create_node(int value) {
    node* n = malloc(sizeof(node));
    if (!n) {
        fprintf(stderr, "failed to allocate memory for node\n");
        return NULL;
    }

    n->value = value;
    n->left = NULL;
    n->right = NULL;

    return n;
}

void free_node(node* n) {
    if (!n) return;

    free_node(n->left);
    free_node(n->right);

    free(n);
}

void destroy_tree(tree* t) {
    if (!t) return;

    free_node(t->root);
    t->root = NULL;
}

// check the nodes value
bool check_node(node* n, int value) {
    if (n->value == value) return true;

    return check_node(n->left, value) || check_node(n->right, value);
}

// this function will find the first occurance of <value>
bool search_tree(tree* t, int value) {
    if (!t) return false;

    return check_node(t->root, value);
}

int main() {
    tree bs = {0};
    bs.root = create_node(10);
    bs.root->left = create_node(20);
    bs.root->left->left = create_node(30);
    bs.root->right = create_node(40);

    printf("deepest node value: %d\n", bs.root->left->left->value);

    printf("searching tree for 30...\n");
    bool result = search_tree(&bs, 30);
    printf("search result: %s\n", result ? "true" : "false");

    destroy_tree(&bs);

    return 0;
}
