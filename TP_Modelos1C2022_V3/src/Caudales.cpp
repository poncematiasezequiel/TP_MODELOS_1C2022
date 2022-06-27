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

void leer_archivo(double& capacidad, double& dimension, vector<Sucursal>& sucursales){

	vector<Sucursal> sucursalesVector;
	string nombreArchivo = "problema_tres.txt";
	ifstream archivo(nombreArchivo.c_str());
	string linea;
	int numLinea  = 0;
	int sizeLinea = 0;
	int cantCarac = 0;
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

		//se agregan sucursales con ubicaciones
		if (linea == "NODE_COORD_SECTION"){
			int posVector = 0;
			while (getline(archivo, linea) && linea != "EOF") {

				std::vector<std::string> out;
				dividirLineaEspacios(linea, space_delimiter, out);

				string nombre = out[0];
				string ubicacionXS = out[1];
				string ubicacionYS = out[2];
				int ubicacionXSize = ubicacionXS.size();
				int ubicacionYSize = ubicacionYS.size();

				int monto = 0;
				long double ubicacionX = std::stold(ubicacionXS.substr(0 , ubicacionXSize ));
				long double ubicacionY = std::stold(ubicacionYS.substr(0 , ubicacionYSize ));
				sucursalesVector[posVector] = Sucursal(nombre, monto);
				sucursalesVector[posVector].setUbicacion(ubicacionX, ubicacionY);
				posVector++;

			}
		}

	}

	sucursales = sucursalesVector;
}

int main() {

	double capacidad;
	double dimension;
	vector<Sucursal> sucursales;

	leer_archivo(capacidad, dimension, sucursales);

	Camion camion(capacidad, dimension, sucursales);
	camion.recorrer();
	camion.imprimir_circuito();

	return 0;
}
