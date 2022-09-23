#include <iostream>
#include <string>
#include "classes.h"

using namespace std;

int setup(Tile g[], int d) {
	for(int i = 0; i < d; i++) {
		for(int j = 0; j < d; j++) {
			g[i*d+j].setTrail(false);
		}
	}

	for(int i = 0; i < d; i++) {
		g[4*d+i].setTrail(true);
	}

	return 0;
}

int draw(Tile g[], int d) {
	for(int i = 0; i < d; i++) {
		for(int j = 0; j < d; j++) {
			if(g[i*d+j].getTrail()) {
				cout << '~';
			} else {
				cout << '.';
			}
		}

		cout << '\n';
	}

	return 0;
}

int main() {
	int dim = 9;
	Tile game[dim*dim];

	setup(game, dim); draw(game, dim);

	return 0;
}
