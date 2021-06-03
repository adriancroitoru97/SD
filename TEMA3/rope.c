/* Copyright 2021 Adrian Croitoru & Tudor Selea */

#include "./rope.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

#define EMPTY ""

const char *strdup(const char *s);

/* Se initializeaza un nod */
RopeNode* makeRopeNode(const char* str) {
    RopeNode *node = malloc(sizeof(*node));
    DIE(!node, "malloc failed");

    node->left = node->right = NULL;
    node->str = str;
    node->weight = strlen(node->str);

    return node;
}

/* Se initializeaza Rope Tree-ul */
RopeTree* makeRopeTree(RopeNode* root) {
    RopeTree *tree = malloc(sizeof(*tree));
    DIE(!tree, "malloc failed");

    tree->root = root;

    return tree;
}

void printRopeNode(RopeNode* rn) {
    if (!rn)
        return;

    if (!(rn->left) && !(rn->right)) {
        printf("%s", rn->str);
        return;
    }

    printRopeNode(rn->left);
    printRopeNode(rn->right);
}

void printRopeTree(RopeTree* rt) {
    if (rt && rt->root) {
        printRopeNode(rt->root);
        printf("%s", "\n");
    }
}

void debugRopeNode(RopeNode* rn, int indent) {
    if (!rn)
        return;

    for (int i = 0; i < indent; ++i)
        printf("%s", " ");

    if (!strcmp(rn->str, EMPTY))
        printf("# %d\n", rn->weight);
    else
        printf("%s %d\n", rn->str, rn->weight);

    debugRopeNode(rn->left, indent+2);
    debugRopeNode(rn->right, indent+2);
}

int getTotalWeight(RopeNode* rt) {
    if (!rt)
        return 0;

    return rt->weight + getTotalWeight(rt->right);
}

/* Se concateneaza cei doi arbori dati ca parametru */
RopeTree* concat(RopeTree* rt1, RopeTree* rt2) {
	const char *empty = strdup(EMPTY);
    RopeNode *new_root = makeRopeNode(empty);

    new_root->left = rt1->root;
    new_root->right = rt2->root;
    new_root->weight = getTotalWeight(new_root->left);

    RopeTree *new_tree = makeRopeTree(new_root);
    return new_tree;
}

/* Se afla caracterul de la pozitia idx din Rope Tree */
char indexRope(RopeTree* rt, int idx) {
	if (idx > 0)
		indexRope(rt, -idx);
	else if (idx < 0)
		idx = -idx;

    RopeNode *root = rt->root;
    int idx_cpy = idx;

    /* Se parcurge rope-ul si se modifica idx_cpy astfel incat,
       in final, contorul va fi egal cu pozitia caracterului
       din string-ul aflat pe frunza corespunzatoare */
	while(1) {
		if (root->left)
			root->weight = getTotalWeight(root->left);
		else if (strlen(root->str) > 0)
			root->weight = strlen(root->str);


    	if (root->weight <= idx_cpy && root->right) {
    		idx_cpy = idx_cpy - root->weight;
    		root = root->right;
    		continue;
    	}

    	if (root->left) {
    		root = root->left;
    		continue;
    	}

    	return root->str[idx_cpy];
    }
}

/* Se cauta stringul din intervalul [start,end) */
char* search(RopeTree* rt, int start, int end) {
	char *searched = (char*)malloc(sizeof(char) * (end - start + 1));

	/* Se obtine fiecare caracter al stringului cautat 
	   folosind functia indexRope */
	for (int i = start; i < end; i++) {
		searched[i - start] = indexRope(rt, i);
	}

	searched[end - start] = '\0';

	return searched;
}

/* Se face o copie a Rope Tree-ului */
RopeNode *tree_copy(RopeNode *node) {
	if (!node)
		return NULL;

	RopeNode *new_tree = makeRopeNode(strdup(node->str));
	new_tree->left = tree_copy(node->left);
	new_tree->right = tree_copy(node->right);
	new_tree->weight = node->weight;

	return new_tree;
}

void split_recursive(RopeNode *node, int idx, RopeNode **parent) {
	RopeTree *temp, *temp2, *aux;
	if (node && node->weight >= idx) {
		split_recursive(node->left, idx, parent);

		/* construirea tree-ului din dreapta, care este balansat
		   automat de functia concat */
		if (!(*parent)) {
			*parent = node->right;
		} else {
			temp = makeRopeTree(node->right);
			aux = makeRopeTree(*parent);
			temp2 = concat(aux, temp);
			*parent = temp2->root;

			free(temp);
			free(aux);
			free(temp2);
		}

		/* taierea efectiva a unei legaturi */
		node->right = NULL;
		/* rebalansarea tree-ului din stanga dupa taierea legaturilor */
		node->weight = getTotalWeight(node);
	} else if (node && node->weight < idx) {
		split_recursive(node->right, idx - node->weight, parent);
	}
}

/* Functie de spargere a Rope Tree-ului initial in doua Rope Tree-uri */
SplitPair split(RopeTree* rt, int idx) {
	SplitPair pair;

	/* Daca indexul este 0, sirul de caractere ramane intact */
	if (idx == 0) {
		const char *empty = strdup(EMPTY);
		pair.left = makeRopeNode(empty);
		pair.right = rt->root;

		return pair;
	}

	/* Analog cu cazul de mai sus */
	if (idx >= getTotalWeight(rt->root)) {
		const char *empty = strdup(EMPTY);
		pair.left = rt->root;
		pair.right = makeRopeNode(empty);

		return pair;
	}

	/* spargerea nodurilor - in momentul in care splitul intersecteaza
	   string-ul dintr-o frunza */
	int idx_cpy = idx;
	RopeNode *root = tree_copy(rt->root);
	RopeNode *root_cpy = root;

	/* algoritm similar cu cel de la indexRope pentru a se gasi
	   adresa nodului ce urmeaza a fi "split-uit" */
	while(1) {
    	if (root->weight <= idx_cpy && root->right) {
    		idx_cpy = idx_cpy - root->weight;
    		root = root->right;
    		continue;
    	}

    	if (root->left) {
    		root = root->left;
    		continue;
    	}

    	break;
    }

    /* "split-uirea" nodului gasit in 2 noi frunze ce se vor 
       linka nodului vechi, pentru ca split-ul efectiv sa nu mai 
       intersecteze string-ul din frunza initiala */
	if (idx_cpy != 0) {
    	RopeTree *modified = makeRopeTree(root);

    	char *first_string = search(modified, 0, idx_cpy);
    	char *second_string = search(modified, idx_cpy, root->weight);

    	RopeNode *first = makeRopeNode(first_string);
    	RopeNode *second = makeRopeNode(second_string);

    	free(modified);

    	root->left = first;
    	root->right = second;
    	free((void*)root->str);
    	root->str = strdup(EMPTY);
    	root->weight = strlen(first->str);
	}

	/* functia efectiva de split, cazul general */
	RopeNode *parent = NULL;
	split_recursive(root_cpy, idx, &parent);

	pair.left = root_cpy;
	pair.right = parent;

	return pair;
}

/* Se insereaza stringul str pe pozitia idx in Rope Tree */
RopeTree* insert(RopeTree* rt, int idx, const char* str) {
	RopeTree *new, *s2, *s1, *s3, *s12;
	/* Nodul care contine stringul ce trebuie inserat in Rope Tree */
	RopeNode *node = makeRopeNode(str);

	/* Se sparge Rope Tree-ul initial in 2 Rope Tree-uri mai mici */
	SplitPair the_split = split(rt, idx);
	s1 = makeRopeTree(the_split.left);
	s2 = makeRopeTree(node);

	/* Se concateneaza prima parte a Rope Tree-ului initial
	   cu nodul in care se afla stringul str */
	s12 = concat(s1, s2);

	/* Se concateneaza Rope Tree-ul obtinut mai sus cu a doua
	   parte a Rope Tree-ului initial */
	s3 = makeRopeTree(the_split.right);
	new = concat(s12, s3);

	free(s1);
	free(s2);
	free(s3);
	free(s12);

	return new;
}

/* Se elimina sirul de lungime len incepand cu indexul start din tree */
RopeTree* delete(RopeTree* rt, int start, int len) {
	RopeTree *new, *temp;
	RopeTree *temp1, *temp2;

	/* Se sparge Rope Tree-ul initial in punctul "start" */
	SplitPair first_split = split(rt, start);
	temp = makeRopeTree(first_split.right);

	/* Se sparge a doua parte a Rope Tree-ului in punctul "start + len" */
	SplitPair second_split = split(temp, len);

	/* Se concateneaza prima parte a Rope Tree-ului initial cu
	   a doua parte a Rope Tree-ului obtinut mai sus */
	temp1 = makeRopeTree(first_split.left);
	temp2 = makeRopeTree(second_split.right);
	new = concat(temp1, temp2);

	free(temp);
	free(temp1);
	free(temp2);

	return new;
}
