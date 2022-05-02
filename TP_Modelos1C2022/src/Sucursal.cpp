#include <cmath>
#include "Sucursal.h"

Sucursal::Sucursal(){
}

Sucursal::Sucursal(std::string nombre, double monto){
	this->nombre = nombre;
	this->monto = monto;
}

void Sucursal::setUbicacion(long double ubicacionX, long double ubicacionY){
	this->ubicacionX = ubicacionX;
	this->ubicacionY = ubicacionY;
}

long double Sucursal::distanciaASucursal(Sucursal Sucursal){

	long double XI_XJ = this->ubicacionX - Sucursal.ubicacionX;
	long double YI_YJ = this->ubicacionY - Sucursal.ubicacionY;

	long double XI_XJ_2 = XI_XJ * XI_XJ;
	long double YI_YJ_2 = YI_YJ * YI_YJ;

	return sqrt(XI_XJ_2 + YI_YJ_2);
}
