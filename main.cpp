/*
 * main.cpp
 *
 *  Created on: Apr 4, 2018
 *      Author: szymon
 */

#include <iostream>
#include <cstdlib>
#include "node.h"
#include "tree.h"
using namespace std;

void present(tree &drzewo, int ins, int del){
	int tab[ins];
	int tmp;

	for (int i=0; i<ins; i++){
		tmp = rand() % 100;
		tab[i] = tmp;
		drzewo.insert(tmp);
	}
	cout << endl;
	cout << drzewo.isempty() << endl;
	drzewo.print_root();
	cout << endl;
	drzewo.look_inorder();
	cout << endl;
	drzewo.look_preorder();
	cout << endl;
	drzewo.look_postorder();
	cout << endl;
	drzewo.show_depth();

	for (int j=0; j<del; j++){
		tmp = rand() % ins;
		cout << "Usuwany węzeł: " << tab[tmp] << endl;
		drzewo.remove_key(tab[tmp]);
	}
	cout << endl;
	cout << "Po usunieciu: " << endl;
	cout << drzewo.isempty() << endl;
	drzewo.print_root();
	cout << endl;
	drzewo.look_inorder();
	cout << endl;
	drzewo.look_preorder();
	cout << endl;
	drzewo.look_postorder();
	cout << endl;
	drzewo.show_depth();
}
int main() {
	tree drzewo;
	present(drzewo, 10, 3);
	cout << endl;
	//cout << endl << drzewo.isempty() << endl;
	//drzewo.look_preorder();
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}



