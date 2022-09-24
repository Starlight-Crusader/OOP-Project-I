#include <iostream>
#include <string>
#include <cstdlib>

#include "classes.h"

using namespace std;

int setup(Tile g[], int d) {
	int a = d-1;

	for(int i = 0; i < d; i++) {
		for(int j = 0; j < d; j++) {
			g[i*d+j].setTrail(-1);
		}
	}

	for(int i = 0; i < d; i++) {
		for(int j = 0; j < d; j++) {
			g[i*d+j].setOccup(false);
		}
	}

	for(int i = 0; i < d; i++) {
		g[4*d+i].setTrail(a);
		a--;
	}

	return 0;
}

int draw(Tile g[], int d) {
	for(int i = 0; i < d; i++) {
		for(int j = 0; j < d; j++) {
			if(g[i*d+j].getTrail()) {
				cout << "\u001b[33m~\u001b[0m";
			} else {
				cout << "\u001b[32m.\u001b[0m";
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
