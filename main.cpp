#include <iostream>
#include <string>
#include <cstdlib>

#include "entities.h"

using namespace std;

class Game {
	public:
		int dim = 9;
		Tile field[9*9];

		void setup() {
			int n = dim;

			for(int i = 0; i < dim; i++) {
				for(int j = 0; j < dim; j++) {
					field[i*dim+j].setTrailN(-1);
					field[i*dim+j].setOccup(true);
				}
			}

			for(int i = 0; i < dim; i++) {
		                field[4*dim+i].setTrailN(n--);
        		}
		}

		void draw() {
			for(int i = 0; i < dim; i++) {
				for(int j = 0; j < dim; j++) {
					if(field[i*dim+j].getTrail() > -1) {
		                                cout << "\u001b[33m~\u001b[0m";
                		        } else {
                               			cout << "\u001b[32m.\u001b[0m";
                        		}
				}

				cout << '\n';
			}
		}
};

int main() {
	Game session; session.setup(); session.draw();

	return 0;
};
