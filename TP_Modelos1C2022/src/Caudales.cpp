#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <list>
#include "Camion.h"

using namespace std;

void dividirLineaEspacios(std::string const &str, const char* delim,
            std::vector<std::string> &out)
{
    char *token = strtok(const_cast<char*>(str.c_str()), delim);
    while (token != nullptr)
    {
        out.push_back(std::string(token));
        token = strtok(nullptr, delim);
    }
}

vector<Sucursal> getSucursales(double dimension){
	vector<Sucursal> sucursales(dimension);
	return sucursales;
}

void leer_archivo(double& capacidad, double& dimension, list<Sucursal>& sucursales){

	vector<Sucursal> sucursalesVector;
	string nombreArchivo = "problema_uno.txt";
	ifstream archivo(nombreArchivo.c_str());
	string linea;
	int numLinea  = 0;
	int sizeLinea = 0;
	int cantCarac = 0;
	double monto = 0;
	const char* space_delimiter = " ";

	while (getline(archivo, linea)) {
		numLinea++;

		sizeLinea = linea.size();

		if ( numLinea == 1 ){
				cantCarac = sizeLinea - 11;
				capacidad = std::stod(linea.substr(11 , cantCarac));
		}

		if ( numLinea == 2 ){
				cantCarac = sizeLinea - 11;
				dimension = std::stod(linea.substr(11 , cantCarac));
				sucursalesVector = getSucursales(dimension);
		}


		//se añanen sucursales con montos
		if ( numLinea == 3 ){
			int posVector = 0;
			while (getline(archivo, linea) && linea != "FIN DEMANDAS") {
				std::vector<std::string> out;
				dividirLineaEspacios(linea, space_delimiter, out);

				string nombre = out[0];
				string montoS = out[1];
				int size = out[1].size();

				monto = std::stod(montoS.substr(0,size));

				sucursalesVector[posVector] = Sucursal(nombre, monto);
				posVector++;

			}
		}

		//se añanen sucursales con ubicaciones
		if (linea == "NODE_COORD_SECTION"){
			int posVector = 0;
			while (getline(archivo, linea) && linea != "EOF") {

				std::vector<std::string> out;
				dividirLineaEspacios(linea, space_delimiter, out);

				string ubicacionXS = out[1];
				string ubicacionYS = out[2];
				int ubicacionXSize = ubicacionXS.size();
				int ubicacionYSize = ubicacionYS.size();

				long double ubicacionX = std::stold(ubicacionXS.substr(0 , ubicacionXSize ));
				long double ubicacionY = std::stold(ubicacionYS.substr(0 , ubicacionYSize ));
				sucursalesVector[posVector].setUbicacion(ubicacionX, ubicacionY);
				posVector++;

			}
		}

	}

	for (unsigned int i = 0; i < sucursalesVector.size() ; i++)
		sucursales.push_back(sucursalesVector[i]);
}

int main() {

	double capacidad;
	double dimension;
	list<Sucursal> sucursalesList;

	leer_archivo(capacidad, dimension, sucursalesList);

	Camion camion(capacidad, sucursalesList);
	camion.recorrer();
	camion.imprimir_circuito();

	return 0;
}
