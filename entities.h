#include <iostream>
#include <string>

class Tile {
	private:
		int trailN;
		bool occupied;

	public:
		void setTrailN(int val) {
			trailN = val;
		}

		int getTrailN() {
			return trailN;
		}

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

	public:
		void setHp(float newVal) {
			hp = newVal;
		}

		float getHp() {
			return hp;
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
