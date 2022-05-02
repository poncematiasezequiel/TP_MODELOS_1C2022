#include "Camion.h"
#include <iostream>

using namespace std;

Camion::Camion() {
	this->monto = 0;
}

Camion::Camion(double capacidad, list<Sucursal> sucursales){
	this->capacidad = capacidad;
	this->sucursales = sucursales;
}
void Camion::imprimir_circuito(){

	list<Sucursal>::iterator it;

	for (it = this->circuitoFinal.begin() ; it != this->circuitoFinal.end() ; ++it){
		Sucursal sucursal = it.operator *();
		if ( sucursal.nombre != "Central")
			cout << sucursal.nombre << " ";
	}

}

Camion::~Camion() {
}

void Camion::sumarMonto(double montoS){
	this->monto = this->monto + montoS;
}

bool Camion::destinoPosible(Sucursal sucursal){
	int montoActualizado = this->monto + sucursal.monto;
	return ( montoActualizado >= MONTO_MIN && montoActualizado <= this->capacidad);
}

void Camion::imprimir_lista(list<Sucursal> sucursales){
	list<Sucursal>::iterator it;

	for (it = sucursales.begin() ; it != sucursales.end() ; ++it){
		Sucursal sucursal = it.operator *();
		cout << "Nombre Sucursal: "      << sucursal.nombre << endl;
	}
}

//dada una sucursal se retorna todos los destinos validos segun su estado actual
list<Sucursal> Camion::destinosPosibles(Sucursal sucursal, list<Sucursal> sucursales){

	list<Sucursal> destinos;

	list<Sucursal>::iterator it;

	for (it = sucursales.begin() ; it != sucursales.end() ; ++it){
		Sucursal sucursalIt = it.operator *();
		if (sucursal.nombre != sucursalIt.nombre){
			if (destinoPosible(sucursalIt))
				destinos.push_back(sucursalIt);
			}
	}

	return destinos;
}

//dada una sucursal y destinos posibles se retorna la sucursal de destino mas proxima
Sucursal Camion::obtenerSucursalMasProxima(Sucursal sucursal, list<Sucursal> sucursales){

	Sucursal sucursalMasProxima;
	list<Sucursal>::iterator it;
	long double distanciaMinimia = 10000000;

	for (it = sucursales.begin() ; it != sucursales.end() ; ++it){
		Sucursal sucursalIt = it.operator *();
		long double distancia = sucursal.distanciaASucursal(sucursalIt);

		if (distancia <= distanciaMinimia){
			distanciaMinimia = distancia;
			sucursalMasProxima = sucursalIt;
		}
	}

	return sucursalMasProxima;
}

void Camion::recorrer_recursivo(Sucursal sucursal, list<Sucursal> sucursalesSinVisitar){

	//se guarda sucursal actual
	this->circuitoFinal.push_back(sucursal);

	if (sucursalesSinVisitar.empty()){
		return;
	}

	list<Sucursal>::iterator it;

	Sucursal sucursalSig = this->obtenerSucursalMasProxima(sucursal,sucursalesSinVisitar);

	//se tiene en cuenta saldo del siguiente
	this->sumarMonto(sucursalSig.monto);

	//se buscan los destinos posibles para la siguiente sucursal
	list<Sucursal> destinos = destinosPosibles(sucursalSig, this->sucursales);

	list<Sucursal>::iterator it_Destinos;
	list<Sucursal>::iterator it_SucursalesRecorridas;

	list<Sucursal> destinosFiltrados;
	//de los destinos que se evaluan son aquellos que no se hayan visitado antes --> filtro los visitados
	for (it_Destinos = destinos.begin() ; it_Destinos != destinos.end() ; ++it_Destinos){
		Sucursal sucursalDestino = it_Destinos.operator *();
		bool existe = false;

		for (it_SucursalesRecorridas = this->circuitoFinal.begin() ; it_SucursalesRecorridas != this->circuitoFinal.end() ; ++it_SucursalesRecorridas){
			Sucursal sucursalRecorrida = it_SucursalesRecorridas.operator *();

			if (sucursalDestino.nombre == sucursalRecorrida.nombre)
				existe = true;
		}

		if (!existe)
			destinosFiltrados.push_back(sucursalDestino);
	}

	this->recorrer_recursivo(sucursalSig , destinosFiltrados);
}

void Camion::recorrer(){

	list<Sucursal> circuito;
	list<Sucursal> configuracion;

	Sucursal central = Sucursal ("Central" , 0);

	list<Sucursal> destinos = destinosPosibles(central, this->sucursales);

	this->recorrer_recursivo(central , destinos);

}
