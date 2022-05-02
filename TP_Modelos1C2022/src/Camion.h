#include <list>
#include "Sucursal.h"
#include <vector>

using namespace std;

//monto minimo en el camion
#define MONTO_MIN  0

class Camion{
public:
	list<Sucursal> circuitoFinal;
	list<Sucursal> sucursales;
	double monto = 0;
	double capacidad = 0;
	Camion();
	Camion(double capacidad, list<Sucursal> sucursales);
	virtual ~Camion();
	void sumarMonto(double montoS);
	void recorrer();
	void imprimir_circuito();
	void recorrer_recursivo(Sucursal sucursal, list<Sucursal> sucursalesSinVisitar);
	bool destinoPosible(Sucursal sucursal);
	list<Sucursal> destinosPosibles(Sucursal sucursal, list<Sucursal> sucursales);
	void obtener_configuraciones(vector<vector<Sucursal>>& configuraciones, vector<Sucursal> sucursales);
	void imprimir_lista(list<Sucursal> sucursales);
	Sucursal obtenerSucursalMasProxima(Sucursal sucursal, list<Sucursal> sucursales);
};

