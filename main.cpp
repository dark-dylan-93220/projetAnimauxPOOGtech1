#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

bool jour = true;

class Joueur {
private:

public:

};

class Animal {
public:
	string nom;
	string espece;
	string regime;
	bool enVie;
	bool aFaim;

	Animal(string nom, string espece, string regime, bool enVie, bool aFaim) : nom(n), espece(e), regime(r), enVie(ev), aFaim(af) {}

	virtual void mourir() = 0;
 };

class Loup : public Animal{
public:
	Loup() : Animal("Roger", "Loup", "carivore", true, false, false) {};

	void attaquer(Animal& cible) override {
		//fonction d'attaque
	}
	void mourir() override {
		//fonction de mort
	}
};

class environement {
private:
	std::vector<Animal*> nourritures;
};



int main() {
	pass
}

