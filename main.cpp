#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

#include "entities.h"

using namespace std;

class Game {
	public:
		int dim = 9;

		Tile field[9*9];
		Enemy enemies[100]; int numOfEnemies;
		Tower towers[9*9]; int numOfTowers;
		Support supports[9*9]; int numOfSupports;

		void setup() {
			numOfEnemies = 0;
			numOfTowers = 0;
			numOfSupports = 0;

			int n = dim;

			for(int i = 0; i < dim; i++) {
				for(int j = 0; j < dim; j++) {
					field[i*dim+j].setTrailN(-1);
					field[i*dim+j].setOccup(false);
				}
			}

			for(int i = 0; i < dim; i++) {
		                field[4*dim+i].setTrailN(n--);
        		}
		}

		void draw() {
			for(int i = 0; i < dim; i++) {
				for(int j = 0; j < dim; j++) {
					if(field[i*dim+j].getTrailN() > -1) {
		                                cout << "\u001b[33m~\u001b[0m";
                		        } else if(!field[i*dim+j].getOccup()){
                               			cout << "\u001b[32m.\u001b[0m";
                        		} else {
						cout << '+';
					}
				}

				cout << '\n';
			}
		}
};

class Stats {
	private:
		int numOfTowers;
		int money;
		int round;
		int phase;
		bool abort;
		int hp;

	public:
		void setup() {
			numOfTowers = 0;
			money = 10;
			round = 1;
			phase = 0;
			abort = false;
			hp = 50;
		}

		void printFinalStats() {
			cout << '\n';
                        cout << "-------------------------------------\n";
                        cout << "             Final stats:\n";
                        cout << " * Rounds survived: " << round-1 << ",\n";
                        cout << " * Towers placed: " << numOfTowers << ",\n";
                        cout << " * HP left: " << hp << ",\n";
                        cout << " * Money left: " << money << '\n';
                        cout << "-------------------------------------\n";
                        cout << '\n';
		}

		void printPhase() {
			if(!phase) {
				cout << "\n=========== PLANNIG PHASE ===========";
			} else {
				cout << "\n============ ACTION PHASE ===========";
			}
		}

		void printStats() {
			cout << '\n';
                        cout << "-------------------------------------\n";
                        cout << "               Stats:                \n";
                        cout << " * HP: " << hp << ",\n";
                        cout << " * Money: " << money << '\n';
                        cout << "-------------------------------------\n";
                        cout << '\n';
		}

		void setNum(int newVal) {
			numOfTowers = newVal;
		}

		int getNum() {
			return numOfTowers;
		}

		void setMoney(int newVal) {
			money = newVal;
		}

		int getMoney() {
			return money;
		}

		void setRound(int newVal) {
			round = newVal;
		}

		int getRound() {
			return round;
		}

		void setPhase(int newVal) {
			phase = newVal;
		}

		int getPhase() {
			return phase;
		}

		void setAbort(bool newVal) {
			abort = newVal;
		}

		bool getAbort() {
			return abort;
		}

		void setHp(int newVal) {
			hp = newVal;
		}

		int getHp() {
			return hp;
		}
};

class Console {
	public:
		void printOptionsMain() {
			cout << '\n';
			cout << "-------------------------------------\n";
			cout << "          Select an action:\n";
			cout << " 1. Place a new tower,\n";
			cout << " 2. Place a new support,\n";
			cout << " 3. Sell a support,\n";
			cout << " 4. Start the next round,\n";
			cout << " 5. Finish the game\n";
			cout << "-------------------------------------\n";
			cout << '\n';
		}

		void printOptionsTower() {
			cout << '\n';
			cout << "-------------------------------------\n";
			cout << " Input coord-s of a new tower in the\n";
			cout << " form: 'x y' OR enter '0 0' in order\n";
			cout << " to abort this operation ...\n";
			cout << "-------------------------------------\n";
			cout << '\n';
			cout << "INPUT: ";
		}

		void printOptionsSupport() {
                        cout << '\n';
                        cout << "-------------------------------------\n";
                        cout << " Input coord-s of a new supp. in the\n";
                        cout << " form: 'x y' OR enter '0 0' in order\n";
                        cout << " to abort this operation ...\n";
                        cout << "-------------------------------------\n";
                        cout << '\n';
                        cout << "INPUT: ";
                }

		void printOptionsSell() {
                        cout << '\n';
                        cout << "-------------------------------------\n";
                        cout << " Input coord-s of an obj. to sell in\n";
                        cout << " the form: 'x y' OR enter '0 0' in\n";
                        cout << " order to abort this operation ...\n";
                        cout << "-------------------------------------\n";
                        cout << '\n';
                        cout << "INPUT: ";
                }

		void clrscr() {
			system("clear");
		}
};

class PriceList {
	private:
		int tower;
		int support;

	public:
		void setup() {
			tower = 10;
			support = 20;
		}

		int getPriceTower() {
			return tower;
		}

		int getPriceSupport() {
			return support;
		}
};

int main() {
	unsigned int second = 1000000;

	Console c; c.clrscr();
	PriceList p; p.setup();
	Stats s; s.setup();
	Game session; session.setup();

	char option;
	int x, y;

	while(!s.getAbort()) {
		if(!s.getPhase()) {
			c.clrscr();
			s.printPhase();
			s.printStats();
			session.draw();
			c.printOptionsMain();

			scanf("%c", &option);

			switch(option) {
				case '1':
					c.printOptionsTower();
					scanf("%i %i", &x, &y);

					if(x == 0 && y == 0) {
						break;
					} else {
						if(session.field[(y-1)*session.dim+(x-1)].getTrailN() > -1 || session.field[(y-1)*session.dim+(x-1)].getOccup() == true) {
							cout << "ERROR: This tile in not free!\n";
							usleep(2*second);
							break;
						}

						s.setMoney(s.getMoney() - 5);
						s.setNum(s.getNum() + 1);

						session.towers[session.numOfTowers].setCoords(x-1, y-1);
						session.towers[session.numOfTowers].setDmg(1.0f);
						session.numOfTowers++;

						session.field[(y-1)*session.dim+(x-1)].setOccup(true);

						break;
					}

				case '2':
					c.printOptionsSupport();
					scanf("%i %i", &x, &y);

					if(x == 0 && y == 0) {
						break;
					} else {
						// Functionality for creating a new support

						break;
					}

				case '3':
					c.printOptionsSell();
					scanf("%i %i", &x, &y);

                                        if(x == 0 && y == 0) {
                                                break;
                                        } else {
                                                // Functionality for selling a support

						break;
                                        }

				case '4':
					s.setPhase(1);
					break;

				case '5':
					c.clrscr();
					s.printFinalStats();
					return 0;
			}
		} else {
			// Simulation of the round
		}
	}
};
