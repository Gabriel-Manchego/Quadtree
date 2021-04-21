#include <iostream>
using namespace std;

class Punto{
public:
	int x, y;
	Punto(){
		x = 0;
		y = 0;
	}
	Punto(int X, int Y){
		x = X;
		y = Y;
	}
};

class Nodo{
public:
	Punto pos;
	string color;
	Nodo(){
		color = "gris";
	}
	Nodo(Punto POS, string COL){
		pos = POS;
		color = COL;
	}
			
};

class QuadTree{
	QuadTree *ai;
	QuadTree *ad;
	QuadTree *bi;
	QuadTree *bd;
	Punto LimAI;
	Punto LimBD;
	Nodo *n;
public:
	int absoluto(int);
	void insertar(Nodo*);
	QuadTree(){
		ai = nullptr;
		ad = nullptr;
		bi = nullptr;
		bd = nullptr;
		LimAI = Punto(0,0);
		LimBD = Punto(0,0);
		n = nullptr;
	}
	QuadTree(Punto AI, Punto BD){
		ai = nullptr;
		ad = nullptr;
		bi = nullptr;
		bd = nullptr;
		LimAI = AI;
		LimBD = BD;
		n = nullptr;
	}
};
int QuadTree::absoluto(int num){
	if(num < 0){
		return (num * -1);
	}
	return num;
}
void QuadTree::insertar(Nodo *nodo){
	if (nodo == nullptr){
		return;
	}
	if (absoluto(LimAI.x - LimBD.x) <= 1 && absoluto(LimAI.y - LimBD.y) <= 1){
		if (n == nullptr){
			n = nodo;
		}
		return;
	}
	if ((LimAI.x + LimBD.x) / 2 >= nodo->pos.x){
		if ((LimAI.y + LimBD.y) / 2 >= nodo->pos.y){
			if (ai == nullptr){
				ai = new QuadTree(Punto(LimAI.x, LimAI.y), Punto((LimAI.x + LimBD.x) / 2,(LimAI.y + LimBD.y) / 2));
			}
			ai -> insertar(nodo);
		}
		else{
			if (bi == nullptr){
				bi = new QuadTree(Punto(LimAI.x, (LimAI.y + LimBD.y) / 2), Punto((LimAI.x + LimBD.x) / 2, LimBD.y));
			}
			bi -> insertar(nodo);
		}
	}
	else{
		if ((LimAI.y + LimBD.y) / 2 >= nodo->pos.y){
			if (ad == nullptr){
				ad = new QuadTree(Punto((LimAI.x + LimBD.x) / 2, LimAI.y), Punto(LimBD.x, (LimAI.y + LimBD.y) / 2));
			}
			ad -> insertar(nodo);
		}
		else{
			if (bd == nullptr){
				bd = new QuadTree(Punto((LimAI.x + LimBD.x) / 2, (LimAI.y + LimBD.y) / 2), Punto(LimBD.x, LimBD.y));
			}
			bd -> insertar(nodo);
		}
	}
}

int main()
{
	QuadTree Limites(Punto(0,0), Punto(100,100));
	Nodo pixel(Punto(25,50),"amarillo");
	Limites.insertar(&pixel);
	return 0;
}

