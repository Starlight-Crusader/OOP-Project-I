#include <iostream>
#include <string>

class Trail {
	private:
		int trailN;

	public:
		void setTrailN(int val) {
                        trailN = val;
                }

                int getTrailN() {
                        return trailN;
                }
};

class Tile: public Trail {
	private:
		bool occupied;

	public:
		void setOccup(bool newVal) {
			occupied = newVal;
		}

		bool getOccup() {
			return occupied;
		}
};

class Entity {
	private:
		int x; int y;

	public:
		void setCoords(int newX, int newY) {
			x = newX; y = newY;
		}

		int getX() {
			return x+1;
		}

		int getY() {
			return y+1;
		}
};

class Tower: public Entity {
	private:
		float dmg;

	public:
		void setDmg(float newVal) {
			dmg = newVal;
		}

		float getDmg() {
			return dmg;
		}
};

class Enemy: public Entity {
	private:
		float hp;
		int step;

	public:
		void setHp(float newVal) {
			hp = newVal;
		}

		float getHp() {
			return hp;
		}

		void setStep(int val) {
			step = val;
		}

		int getStep() {
			return step;
		}
};

class Support: public Entity {
	private:
		float boost;

	public:
		void setBoost(float val) {
			boost = val;
		}

		float getBoost() {
			return boost;
		}
};
