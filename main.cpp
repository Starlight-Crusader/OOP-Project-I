#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

#include "entities.h"

using namespace std;

class Game {
	private:
		int dim;
		Tile field[9*9];
                Enemy enemies[100]; int numOfEnemies;
                Tower towers[9*9]; int numOfTowers;
                Support supports[9*9]; int numOfSupports;

	public:
		int getDim() {
			return dim;
		}

		int getNumOfE() {
			return numOfEnemies;
		}

		int getNumOfT() {
			return numOfTowers;
		}

		int getNumOfS() {
			return numOfSupports;
		}

		bool checkTile(int j, int i) {
			if(field[i*dim+j].getTrailN() > -1 || field[i*dim+j].getOccup() == true) {
                        	return true;
                        } else {
				return false;
			}
		}

		void buildAStruct(int j, int i, int t) {
			if(t == 0) {
				towers[numOfTowers].setCoords(j, i);
                                towers[numOfTowers].setDmg(1.0f);
                                numOfTowers++;

                                field[i*dim+j].setOccup(true);
			} else if(t == 1) {
				supports[numOfSupports].setCoords(j, i);
                                supports[numOfSupports].setBoost(1.0f);
                                numOfSupports++;

                                field[i*dim+j].setOccup(true);
			}
		}

		int sellAStructure(int j, int i) {
			for(int a = 0; a < numOfTowers; a++) {
				if(towers[a].getX()-1 == j && towers[a].getY()-1 == i) {
					for(int b = a; b < numOfTowers; b++) {
						towers[b].setCoords(towers[b+1].getX()-1, towers[b+1].getY()-1);
						towers[b].setDmg(towers[b+1].getDmg());
					}

					field[i*dim+j].setOccup(false);
					numOfTowers--;
					return 0;
				}
			}

			for(int a = 0; a < numOfSupports; a++) {
                                if(supports[a].getX()-1 == j && supports[a].getY()-1 == i) {
                                        for(int b = a; b < numOfSupports; b++) {
                                                supports[b].setCoords(supports[b+1].getX()-1, supports[b+1].getY()-1);
                                                supports[b].setBoost(supports[b+1].getBoost());
                                        }

					field[i*dim+j].setOccup(false);
                                        numOfSupports--;
                                        return 1;
                                }
                        }

			return -1;
		}

		/* void printE() {
			for(int i = 0; i < numOfEnemies; i++) {
				cout << "x = " << enemies[i].getX() << '\n';
				cout << "y = " << enemies[i].getX() << '\n';
				cout << "s = " << enemies[i].getStep() << '\n';
			}
		} */

		void setup() {
			dim = 9;
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
		                field[4*dim+i].setTrailN(n);
				n--;
        		}
		}

		void draw() {
			bool br = false;

			for(int i = 0; i < dim; i++) {
				for(int i = 0; i < 14; i++) {
					cout << ' ';
				}

				for(int j = 0; j < dim; j++) {
					if(field[i*dim+j].getTrailN() > -1) {
						br = false;

						for(int k = 0; k < numOfEnemies; k++) {
							if(enemies[k].getX()-1 == j && enemies[k].getY()-1 == i) {
								cout << "\u001b[31m0\u001b[0m";
								br = true;
								break;
							}
						}

						if(!br) {
							cout << "\u001b[33m~\u001b[0m";
						} else {
							continue;
						}
                		        } else if(!field[i*dim+j].getOccup()){
                               			cout << "\u001b[32m.\u001b[0m";
                        		} else {
						for(int a = 0; a < numOfTowers; a++) {
							if(towers[a].getX()-1 == j && towers[a].getY()-1 == i) {
								cout << "\u001b[34m*\u001b[0m";
							}
						}

						for(int a = 0; a < numOfSupports; a++) {
                                                        if(supports[a].getX()-1 == j && supports[a].getY()-1 == i) {
                                                                cout << "\u001b[31m+\u001b[0m";
                                                        }
                                                }
					}
				}

				cout << '\n';
			}
		}

		void addEnemies(int n) {
			numOfEnemies = n;

			for(int i = 0; i < n; i++) {
				enemies[i].setHp(2.0f);
				enemies[i].setStep(i + 11);
				enemies[i].setCoords(999, 999);
			}
		}

		void moveEnemies() {
			for(int i = 0; i < numOfEnemies; i++) {
				enemies[i].setStep(enemies[i].getStep()-1);
			}
		}

		void rewriteCoords() {
			int br = 0;

			for(int i = 0; i < numOfEnemies; i++) {
				br = 0;

				for(int j = 0; j < dim; j++) {
					for(int k = 0; k < dim; k++) {
						if(field[j*dim+k].getTrailN() == enemies[i].getStep()) {
							enemies[i].setCoords(k, j);
							br = 1; break;
						}

						if(br) { break; }
					}
				}

				if(!br) {
					enemies[i].setCoords(999, 999);
				}
			}
		}

		int shootTargets() {
			int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
			int kills = 0;
			bool shot = false;

			for(int i = 0; i < numOfTowers; i++) {
				shot = false;

				for(int j = 7; j >= 0; j--) {
					for(int k = 0; k < numOfEnemies; k++) {
						if(towers[i].getX()+directions[j][1] == enemies[k].getX() && towers[i].getY()+directions[j][0] == enemies[k].getY()) {
							enemies[k].setHp(enemies[k].getHp()-towers[i].getDmg()); shot = true;

							if(enemies[k].getHp() <= 0) {
								for(int a = k; a < numOfTowers; a++) {
                                                			enemies[a].setCoords(enemies[a+1].getX()-1, enemies[a+1].getY()-1);
                                                			enemies[a].setHp(enemies[a+1].getHp());
                                        			}

								numOfEnemies--;
								kills++;
							}
						}

						if(shot) { break; }
					}

					if(shot) { break; }
				}
			}

			return kills;
		}

		int checkFinish() {
			int damage = 0;

			for(int i = 0; i < numOfEnemies; i++) {
				if(enemies[i].getStep() < 1) {
					damage += 2;

					for(int a = i; a < numOfTowers; a++) {
                                        	enemies[a].setCoords(enemies[a+1].getX()-1, enemies[a+1].getY()-1);
                                               	enemies[a].setHp(enemies[a+1].getHp());
                                        }

                                       	numOfEnemies--;
				}
			}

			return damage;
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
		int kills;

	public:
		void setKills(int newVal) {
			kills = newVal;
		}

		int getKills() {
			return kills;
		}

		void setup() {
			numOfTowers = 0;
			money = 20;
			round = 0;
			phase = 0;
			abort = false;
			hp = 50;
			kills = 0;
		}

		bool checkMoney(int val) {
			if(money >= val) {
				return true;
			} else {
				return false;
			}
		}

		void printFinalStats() {
			cout << '\n';
                        cout << "-------------------------------------\n";
                        cout << "             Final stats:\n";
                        cout << " * Rounds survived: " << round-1 << ",\n";
                        cout << " * Towers placed: " << numOfTowers << ",\n";
                        cout << " * HP left: " << hp << ",\n";
                        cout << " * Enemies killed: " << kills << '\n';
                        cout << "-------------------------------------\n";
                        cout << '\n';
		}

		void printPhase() {
			if(!phase) {
				cout << "\n=========== PLANNIG PHASE ===========\n";
			} else {
				cout << "\n============ ACTION PHASE ===========\n";
				cout << '\n';
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
			cout << " 1. Place a new tower (10),\n";
			cout << " 2. Place a new support (20),\n";
			cout << " 3. Sell a structure (! 50% back !),\n";
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
	int v = 0;

	Console c; c.clrscr();
	PriceList p; p.setup();
	Stats s; s.setup();
	Game session; session.setup();

	char option; int result;
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
					if(!s.checkMoney(p.getPriceTower())) {
						cout << "You do not have enough money!\n";
						usleep(2*second);
						break;
					}

					c.printOptionsTower();
					scanf("%i %i", &x, &y);

					if(x == 0 && y == 0) {
						break;
					} else {
						if(session.checkTile(x-1, y-1)) {
							cout << "ERROR: This tile in not free!\n";
							usleep(2*second);
							break;
						} else {
							s.setMoney(s.getMoney() - 10);
	                                                s.setNum(s.getNum() + 1);

							session.buildAStruct(x-1, y-1, 0);
						}

						break;
					}

				case '2':
					if(!s.checkMoney(p.getPriceSupport())) {
        	                                cout << "You do not have enough money!\n";
                                                usleep(2*second);
                                                break;
                                        }

					c.printOptionsSupport();
					scanf("%i %i", &x, &y);

					if(x == 0 && y == 0) {
						break;
					} else {
						if(session.checkTile(x-1, y-1)) {
                                                        cout << "ERROR: This tile in not free!\n";
                                                        usleep(2*second);
                                                        break;
                                                } else {
                                                        s.setMoney(s.getMoney() - 20);
                                                        s.setNum(s.getNum() + 1);

                                                        session.buildAStruct(x-1, y-1, 1);
                                                }

						break;
					}

				case '3':
					c.printOptionsSell();
					scanf("%i %i", &x, &y);

                                        if(x == 0 && y == 0) {
                                                break;
                                        } else {
						result = session.sellAStructure(x-1, y-1);
                                                if(result > -1) {
							if(result == 0) {
								s.setMoney(s.getMoney() + p.getPriceTower() / 2);
							} else {
								s.setMoney(s.getMoney() + p.getPriceSupport() / 2);
							}

							cout << "Success!\n";
							usleep(2*second);
						} else {
							cout << "Unable to find a structure with these coord-s!\n";
							usleep(2*second);
						}

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
			s.setRound(s.getRound() + 1); v = 0;

			session.addEnemies(2 + s.getRound() / 2);

			while(session.getNumOfE()) {
				session.moveEnemies(); session.rewriteCoords();

				v = session.checkFinish();
				s.setHp(s.getHp() - v);

				if(s.getHp() <= 0) {
					c.clrscr();
                                        s.printFinalStats();
                                        return 0;
				}

				c.clrscr(); s.printPhase(); session.draw(); usleep(0.1*second);

				v = session.shootTargets();
				s.setMoney(s.getMoney() + v);
				s.setKills(s.getKills() + v);

				c.clrscr(); s.printPhase(); session.draw(); usleep(0.1*second);
			}

			s.setPhase(0);
		}
	}
};
