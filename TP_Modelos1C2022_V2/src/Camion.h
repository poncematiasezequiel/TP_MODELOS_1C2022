#include <list>
#include "Sucursal.h"
#include <vector>
#include <fstream>

using namespace std;

//monto minimo en el camion
#define MONTO_MIN  0

class Camion{
public:
	vector<Sucursal> circuitoFinal;
	vector<Sucursal> sucursales;
	double monto = 0;
	double capacidad = 0;
	double dimension = 0;
	Camion();
	Camion(double capacidad, double dimension, vector<Sucursal> sucursales);
	virtual ~Camion();
	void sumarMonto(double montoS);
	void recorrer();
	void imprimir_circuito();
	void recorrer_recursivo(Sucursal sucursal, list<Sucursal>* sucursalesSinVisitar);
	bool destinoPosible(Sucursal* sucursal);
	list<Sucursal>* destinosPosibles();
	list<Sucursal> filtrarDestinos(list<Sucursal> sucursales);
	void imprimir_lista(list<Sucursal> sucursales);
	Sucursal obtenerSucursalMasProxima(Sucursal* sucursal, list<Sucursal>* sucursales);
};
