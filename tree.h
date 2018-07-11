/*
 * tree.h
 *
 *  Created on: Apr 4, 2018
 *      Author: szymon
 */

#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include <cstdlib>
#include "node.h"
using namespace std;

class tree : public node{	//Dziedziczenie wezla
	node* root;
	void inorder(node*);
	void preorder(node*);
	void postorder(node*);

	void rotate_rr(node*);
	void rotate_ll(node*);
	void rotate_rl(node*);
	void rotate_lr(node*);

public:
	tree(){				//Konstruktor klasy
		root = NULL;
	}

	void insert(int);
	void remove(int);
	node* removeAVL(node*);
	void remove_key(int);
	void nodeinfo(node*);
	bool isempty() const {		//Sprawdza, czy drzewo jest puste
		return root == NULL;
	}
	void print_root(){
		cout << "Root: " << root->key << endl;
	}
	void look_inorder();
	void look_preorder();
	void look_postorder();


	int check_bf(node*);
	int depth(node*);
	void show_depth();
	void update_bf(node*);

};



#endif /* TREE_H_ */
