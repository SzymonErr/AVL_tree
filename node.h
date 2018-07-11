/*
 * node.h
 *
 *  Created on: Apr 4, 2018
 *      Author: szymon
 */

#ifndef NODE_H_
#define NODE_H_
#include <iostream>
using namespace std;

class node{
public:
	int key, bf;
	node *left, *right, *parent;
	node(){
		key = 0;
		bf = 0;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
};

#endif /* NODE_H_ */
