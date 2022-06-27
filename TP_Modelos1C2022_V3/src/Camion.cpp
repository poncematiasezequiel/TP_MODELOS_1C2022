#include "Camion.h"
#include <iostream>

using namespace std;


Camion::Camion() {
	this->monto = 0;
}

Camion::Camion(double capacidad, double dimension, vector<Sucursal> sucursales){
	this->capacidad = capacidad;
	this->sucursales = sucursales;
	this->dimension = dimension;
}

void Camion::imprimir_circuito(){

	string nombreArchivo = "solucion_tres.txt";
	ofstream archivo;

	archivo.open( nombreArchivo.c_str(), fstream::app);

	vector<Sucursal>::iterator it;

	for (it = this->circuitoFinal.begin() ; it != this->circuitoFinal.end() ; ++it){
		Sucursal sucursal = it.operator *();
		if ( sucursal.nombre != "Central")
			archivo << sucursal.nombre << " " ;
	}

	archivo.close();
}

Camion::~Camion() {
}

void Camion::sumarMonto(double montoS){
	this->monto = this->monto + montoS;
}

bool Camion::destinoPosible(Sucursal* sucursal){
	int montoActualizado = this->monto + sucursal->monto;
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
list<Sucursal>* Camion::destinosPosibles(){
	list<Sucursal>* destinos = new list<Sucursal>();

	vector<Sucursal>::iterator it;

	for (it =  this->sucursales.begin() ; it !=  this->sucursales.end() ; ++it){
		Sucursal sucursalIt = it.operator *();
		if (sucursalIt.sucursalVisitada == false){
				destinos->push_back(sucursalIt);
		}
	}

	return destinos;
}

//dada una sucursal y destinos posibles se retorna la sucursal de destino mas proxima
Sucursal Camion::obtenerSucursalMasProxima(Sucursal* sucursal, list<Sucursal>* sucursales){

	Sucursal sucursalMasProxima;
	list<Sucursal>::iterator it;
	long double distanciaMinimia = 10000000;

	for (it = sucursales->begin() ; it != sucursales->end() ; ++it){
		Sucursal sucursalIt = it.operator *();
		long double distancia = sucursal->distanciaASucursal(&sucursalIt);

		if (distancia <= distanciaMinimia){
			distanciaMinimia = distancia;
			sucursalMasProxima = sucursalIt;
		}
	}

	return sucursalMasProxima;
}

void Camion::recorrer(){

	list<Sucursal>* destinos;

	int montoCentral = 0;

	Sucursal central = Sucursal ("Central" , montoCentral);


	//todos los destinos que puedo ir desde central
	destinos = destinosPosibles();

	//entre todos los destinos posibles, busco cual está mas proxima
	Sucursal sucursalSig = this->obtenerSucursalMasProxima(&central,destinos);
	delete destinos;

	do {
		//se guarda sucursal mas proxima al circuito
		this->circuitoFinal.push_back(sucursalSig);

		//marco la sucursal como visitada para que no se la vuelva a evaluar
		int i = stoi(sucursalSig.nombre) - 1;
		this->sucursales[i].sucursalVisitada = true;

		destinos = destinosPosibles();

		Sucursal sucursalProxima = this->obtenerSucursalMasProxima(&sucursalSig,destinos);
		delete destinos;

		sucursalSig = sucursalProxima;

	} while (this->circuitoFinal.size() < this->dimension);

}


list<Sucursal> Camion::filtrarDestinos(list<Sucursal> destinos){

	list<Sucursal> destinosFiltrados;
	list<Sucursal>::iterator it_Destinos;
	vector<Sucursal>::iterator it_SucursalesRecorridas;

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

	return destinosFiltrados;
}
