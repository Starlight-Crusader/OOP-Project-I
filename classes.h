#include <iostream>
#include <string>
#include <time.h> 

class Tile {
	private:
		bool trail;

		int numOfEntities;
		int entities[];

	public:
		void setTrail(bool newVal) {
			trail = newVal;
		}

		bool getTrail() {
			return trail;
		}

		void setNum(int newVal) {
			numOfEntities = newVal;
		}

		int getNum() {
			return numOfEntities;
		}

		void addEntity(int newId) {
			entities[numOfEntities] = newId;
			numOfEntities++;
		}

		void getEntities(int *a) {
			for(int i = 0; i < numOfEntities; i++) {
				*(a+i) = entities[i];
			}
		}
};

class Entity {
	private:
		int id;

	public:
		void setId(int newVal) {
			id = newVal;
		}

		int getId() {
			return id;
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

		int getHp() {
			return hp;
		}
};
