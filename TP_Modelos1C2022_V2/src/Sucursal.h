#include <stdio.h>
#include <string>
#include <vector>

class Sucursal{
  public:
	std::string nombre = "";
	double monto = 0;
	long double ubicacionX = 0;
	long double ubicacionY = 0;
	bool sucursalVisitada = false;
	Sucursal();
	Sucursal(std::string nombre, double monto);
	Sucursal& operator=(const Sucursal& sucursal );
	void setUbicacion(long double ubicacionX, long double ubicacionY);
	long double distanciaASucursal(Sucursal* Sucursal);

};
