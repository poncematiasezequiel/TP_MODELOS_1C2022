#include <cmath>
#include "Sucursal.h"

Sucursal& Sucursal::operator=(const Sucursal& sucursal){
     if(this != &sucursal) {
         this->nombre = sucursal.nombre;
         this->monto = sucursal.monto;
         this->sucursalVisitada = sucursal.sucursalVisitada;
         this->ubicacionX = sucursal.ubicacionX;
         this->ubicacionY = sucursal.ubicacionY;
     }
     return *this;
 }

Sucursal::Sucursal(){
	this->nombre = "";
	this->monto = 0;
	this->sucursalVisitada = false;
	this->ubicacionX = 0;
	this->ubicacionY = 0;
}

Sucursal::Sucursal(std::string nombre, double monto){
	this->nombre = nombre;
	this->monto = monto;
	this->sucursalVisitada = false;
	this->ubicacionX = 0;
	this->ubicacionY = 0;
}

void Sucursal::setUbicacion(long double ubicacionX, long double ubicacionY){
	this->ubicacionX = ubicacionX;
	this->ubicacionY = ubicacionY;
}

long double Sucursal::distanciaASucursal(Sucursal* sucursal){

	long double XI_XJ = this->ubicacionX - sucursal->ubicacionX;
	long double YI_YJ = this->ubicacionY - sucursal->ubicacionY;

	long double XI_XJ_2 = XI_XJ * XI_XJ;
	long double YI_YJ_2 = YI_YJ * YI_YJ;

	return sqrt(XI_XJ_2 + YI_YJ_2);
}
