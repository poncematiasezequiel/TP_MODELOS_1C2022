#include <stdio.h>
#include <string>

class Sucursal{
  public:
	std::string nombre = "";
	double monto = 0;
	long double ubicacionX = 0;
	long double ubicacionY = 0;
	Sucursal();
	Sucursal(std::string nombre, double monto);
	void setUbicacion(long double ubicacionX, long double ubicacionY);
	long double distanciaASucursal(Sucursal Sucursal);

};
