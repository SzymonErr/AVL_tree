/*
 * tree.cpp
 *
 *  Created on: Apr 4, 2018
 *      Author: szymon
 */

#include <iostream>
#include <cstdlib>
#include "tree.h"
#include "node.h"
using namespace std;

void tree::nodeinfo(node* curr){
	cout << "Key: " << curr->key << endl;
	if (curr->parent != NULL)
	cout << "Parent: " << (curr->parent)->key << endl;
	else cout << "Parent: NULL" << endl;
	if (curr->left != NULL){
		cout << "Left: " << (curr->left)->key << endl;
	} else cout << "Left: NULL" << endl;
	if (curr->right != NULL){
		cout << "Right: " << (curr->right)->key << endl;
	} else cout << "Right: NULL" << endl;
}

void tree::show_depth(){
	cout << "Wysokosc drzewa: " << depth(root) << endl;;
}


void tree::insert(int value){
	node *tmp = new node;
	tmp->key = value;

	if (isempty()) root = tmp;
	else {
		node *current;
		current = root;

		while(current) {		//Poszukiwanie rodzica dla nowego wezla
			tmp->parent = current;
			if (tmp->key < current->key)
				current = current->left;
			else
				current = current->right;
		}
		if (tmp->key < (tmp->parent)->key)		//dodanie liscia do drzewa
			(tmp->parent)->left = tmp;
		else
			(tmp->parent)->right = tmp;
	}
	if (tmp != root) update_bf(tmp);
	return;
}

node* tree::removeAVL(node* curr){
	node *bifor, *tmp, *tmp2, *tmp3;
	bool nest = true;

	if(curr->left != NULL) {
		tmp3 = curr->left;
		while(tmp3->right != NULL){
			tmp3 = tmp3->right;
		}
	}

	if (curr->left == NULL || curr->right == NULL){
		if(curr->left != NULL){
			bifor = curr->left;
			curr->left = NULL;
		}
		else{
			bifor = curr->right;
			curr->right = NULL;
		}
		curr->bf = 0;
		nest = true;
	}
	else {
		bifor = removeAVL(tmp3);
		nest = false;
	}
	if (bifor != NULL){
		bifor->parent = curr->parent;
		bifor->left = curr->left;
		if(bifor->left != NULL) (bifor->left)->parent = bifor;
		bifor->right = curr->right;
		if(bifor->right != NULL) (bifor->right)->parent = bifor;
		bifor->bf = curr->bf;
	}
	if(curr->parent == NULL){
			root = bifor;
		}
	else{
		if((curr->parent)->left == curr) (curr->parent)->left = bifor;
			else (curr->parent)->right = bifor;
	}
	  if(nest)
	  {
	    tmp = bifor;
	    bifor = curr->parent;
	    while(bifor)
	    {
	      if(!bifor->bf)
	      {              // Przypadek nr 1
	        if(bifor->left == tmp)  bifor->bf = -1;
	        else bifor->bf = 1;
	        break;
	      }
	      else
	      {
	        if(((bifor->bf == 1) && (bifor->left == tmp)) || ((bifor->bf == -1) && (bifor->right == tmp)))
	        {           // Przypadek nr 2
	          bifor->bf = 0;
	          tmp = bifor;
	          bifor = bifor->parent;
	        }
	        else
	        {
	          if(bifor->left == tmp)  tmp2 = bifor->right;
	          else tmp2 = bifor->left;
	          if(!tmp2->bf)
	          {         // Przypadek 3A
	            if(bifor->bf == 1) rotate_ll(bifor);
	            else rotate_rr(bifor);
	            break;
	          }
	          else if(bifor->bf == tmp2->bf)
	          {         // Przypadek 3B
	            if(bifor->bf == 1) rotate_ll(bifor);
	            else rotate_rr(bifor);
	            bifor = tmp2;
	            bifor = tmp2->parent;
	          }
	          else
	          {         // Przypadek 3C
	            if(bifor->bf == 1) rotate_lr(bifor);
	            else rotate_rl(bifor);
	            tmp = bifor->parent;
	            bifor = tmp->parent;
	          }
	        }
	      }
	    }
	  }
	  return curr;

}

void tree::remove_key(int value){
	node *current;
		bool findWally = 0;

		//Szukanie wezla z podana wartoscia
		if (root == NULL){
			cout << "Drzewo jest puste" << endl;
			return;
		}
		current = root;
		while(current != NULL){
			if (current->key == value){
				findWally = 1;
				//nodeinfo(current);
				break;
				}
			else {
				parent = current;
				if (value < current->key)
					current = current->left;
				else
					current = current->right;
			}
		}
		if (findWally != 1){
			cout << "Brak podanej wartosci w drzewie" << endl;
			return;
		}
		current = removeAVL(current);
}

void tree::inorder(node *nodus){
	if (nodus != NULL){
		if (nodus->left)
			inorder(nodus->left);
		cout << nodus->key << " ";
		if (nodus->right)
			inorder(nodus->right);
	}
	else return;
}

void tree::look_inorder(){
	inorder(root);
}

void tree::preorder(node *nodus){
	if (nodus != NULL){
		cout << nodus->key << "/" << nodus->bf << " ";
		if (nodus->left)
			preorder(nodus->left);
		if (nodus->right)
			preorder(nodus->right);
	}
	else return;
}

void tree::look_preorder(){
	preorder(root);
}
void tree::postorder(node *nodus){
	if (nodus != NULL){
		if (nodus->left)
			postorder(nodus->left);
		if (nodus->right)
			postorder(nodus->right);
		cout << nodus->key << "/" << nodus->bf << " ";
	}
	else return;
}

void tree::look_postorder(){
	postorder(root);
}


void tree::rotate_ll( node* curr){
	node *tmp, *tmp_parent;

		cout << "LL: " << curr->key << endl;
		tmp = curr->left;
		tmp_parent = curr->parent;
		curr->left = tmp->right;
		if (curr->left != NULL){
			(curr->left)->parent = curr;
		}
		curr->parent = tmp;
		tmp->parent = tmp_parent;
		tmp->right = curr;

		if(tmp->parent != NULL){
			if((tmp->parent)->left == curr) (tmp->parent)->left = tmp;
			else (tmp->parent)->right = tmp;
		} else root = tmp;
		if (tmp->bf == 1){
				curr->bf = 0;
				tmp->bf = 0;
			}
			else {
				curr->bf = 1;
				tmp->bf = -1;
			}
}

void tree::rotate_rr(node *curr){
	node *tmp, *tmp_parent;

	cout << "RR: " << curr->key << endl;
	tmp = curr->right;
	tmp_parent = curr->parent;
	curr->right = tmp->left;
	if (curr->right != NULL){
		(curr->right)->parent = curr;
	}
	curr->parent = tmp;
	tmp->parent = tmp_parent;
	tmp->left = curr;

	if(tmp->parent != NULL){
		if((tmp->parent)->left == curr) (tmp->parent)->left = tmp;
		else (tmp->parent)->right = tmp;
	} else root = tmp;
	if (tmp->bf == -1){
		curr->bf = 0;
		tmp->bf = 0;
	}
	else {
		curr->bf = -1;
		tmp->bf = 1;
	}
	return;
}

void tree::rotate_rl(node *curr){
	node *tmp_r, *tmp_l, *tmp_parent;

	cout << "RL: " << curr->key << endl;
	tmp_r = curr->right;
	tmp_l = tmp_r->left;
	tmp_parent = curr->parent;
	(curr->right)->left = tmp_l->right;
	if((curr->right)->left != NULL) ((curr->right)->left)->parent = curr->right;
	curr->right = tmp_l->left;
	if (curr->right != NULL) (curr->right)->parent = curr;
	tmp_l->left = curr;
	curr->parent = tmp_l;
	tmp_l->right = tmp_r;
	tmp_r->parent = tmp_l;
	tmp_l->parent = tmp_parent;

	if(tmp_l->parent != NULL){
			if((tmp_l->parent)->left == curr) (tmp_l->parent)->left = tmp_l;
			else (tmp_l->parent)->right = tmp_l;
		} else root = tmp_l;
	if (tmp_l->bf == -1) curr->bf = 1;
	else curr->bf = 0;
	if (tmp_l->bf == 1) tmp_r->bf = -1;
	else tmp_r->bf = 0;
	tmp_l->bf = 0;
}

void tree::rotate_lr(node *curr){
	node *tmp_son, *tmp_grandson, *tmp_parent;

	cout << "LR: " << curr->key << endl;
	tmp_son = curr->left;
	tmp_grandson = tmp_son->right;
	tmp_parent = curr->parent;
	tmp_son->right = tmp_grandson->left;
	if (tmp_son->right != NULL) (tmp_son->right)->parent = tmp_son;
	curr->left = tmp_grandson->right;
	if (curr->left != NULL) (curr->left)->parent = curr;
	tmp_grandson->right = curr;
	curr->parent = tmp_grandson;
	tmp_grandson->left = tmp_son;
	tmp_son->parent = tmp_grandson;
	tmp_grandson->parent = tmp_parent;

	if(tmp_grandson->parent != NULL){
			if((tmp_grandson->parent)->left == curr) (tmp_grandson->parent)->left = tmp_grandson;
			else (tmp_grandson->parent)->right = tmp_grandson;
		} else root = tmp_grandson;
	if (tmp_grandson->bf == 1) curr->bf = -1;
	else curr->bf = 0;
	if (tmp_grandson->bf == -1) tmp_son->bf = 1;
	else tmp_son->bf = 0;
	tmp_grandson->bf = 0;
	return;
}

int tree::depth(node *root){
	if (root != NULL){
		int lDepth = depth(root->left);
		int rDepth = depth(root->right);

		if (lDepth > rDepth) return (lDepth+1);
		else return (rDepth+1);
		}
	else
		return 0;
}

int tree::check_bf(node *root){
	int left, right;
	left = depth(root->left);
	right = depth(root->right);
	root->bf = left - right;
	return root->bf;
}

void tree::update_bf(node* son){
	node *parr = son->parent;
	if (parr->bf == 0){
		if(son == parr->left) parr->bf = 1;
		else parr->bf = -1;
		parr = parr->parent;
		son = son->parent;
	}
	else{
		parr->bf = 0;
		return;
	}
	while(parr != NULL){
		if (parr->bf != 0){
			if(parr->bf == -1){
				if(parr->left == son){
					parr->bf = 0;
					return;
				}
				else{
					if(son->bf == 1) rotate_rl(parr);
					else rotate_rr(parr);
				return;
				}
			}
			else{
				if (parr->right == son){
					parr->bf = 0;
					return;
				}
				else{
					if(son->bf == -1) rotate_lr(parr);
					else rotate_ll(parr);
					cout << "test1" << endl;
					return;
				}
			}
		}
		else{
			if(parr->left == son) parr->bf = 1;
			else parr->bf = -1;
			son = parr;
			parr = parr->parent;
		}
	}
}




