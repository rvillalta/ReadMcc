/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@												 @
@		PROGRAMA QUE LEE LOS ARCHIVOS W2CAD CON LOS QUE SE ALIMENTA EL ECLIPSE           @
@				Raul Villalta Julio 2016					 @
@												 @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

// COMPILAR USANDO LA OPCION: 	-STD=C++11

#include <string>
#include <fstream>
#include <iostream>
using namespace std;
void lee_archivo(string, double * , int *);
int main()
{
	double *dat, data[80000];
	int *fils, control[100],  filas[100], i, j, ndatos, ntot,  k = 0, s = 1, tt;
	dat = data;
	fils = filas;
	lee_archivo("X06 OPEN 2X2 CR PinPoint.CD2", dat, fils);
	ndatos = filas[0];
	control[0] = 0;
	ntot = 0;
	for (i = 1; i < ndatos + 1; i++){
		ntot = ntot + filas[i];
		cout << "filas[" << i << "]=" << filas[i] << endl;
		control[i] = 4 * filas[i]+ control[i - 1];
		cout << "control[" << i << "]=" << control[i] << endl;
	}

	cout << "######################## RESULTADOS #############################" << endl;
	cout << "ntot " << ntot << endl;
	for (i = 0; i < 295; i++){
		cout << i + 1 << "	";
		for (j=0; j<4; j++){
			//cout <<"	" << j << "	" << data[k] << "	";
			cout << data[k] << "	";
			k++;
		}
		cout << endl;
		if (k == control[s]){
			cout << endl;
			cout << endl;
			cout << "-------------------------------------------------------------------------" << endl;
			s++;
			cin >> tt;
		}
	}
	return 0;
}

void lee_archivo(string filename, double *datos , int *nfils)
{
/*
	FILENAME  nombre del archivo del cual se extraera la data
	*DATOS    puntero a dobles donde se almacenaran los datos leidos
		  en el siguiente orden X Y Z data
	*NFILS    puntero a enteros donde se almacenara el numero de filas de
		  cada uno de los set de datos del archivo, el primer elemento
		  (nfils[0]) almacenara eñ numero de sets diferentes de datos*/


	ifstream pa;
	string line, t, t1, t2;
	int i, cont, j, k;
	double values[4];
	size_t found;
	bool bandera = false;
	pa.open(filename);
	if(!pa.is_open()){
		cout << "NO SE PUDO ABRIR EL ARCHIVO " << filename << endl;
	}
	else{
		cont=0;
		t2 = "ASDF";
		k=0;
		nfils++;
		while(!pa.eof()){
			getline(pa, line);
			t1 = line.substr(0, 1);
			if(t1 == "<" & t1 != t2){
				if(bandera) {
					*nfils = i;
					nfils++;
					cout << "#####################################################" << endl;
				}
				i = 0;
				cont++;
				bandera = true;
			}
			if(t1 == "<"){
				found = line.find(" ");
				values[0] = stod(line.substr(1, found));
				t = line.substr(found + 1, line.length() - 1);
				found = t.find(" ");
				values[1] = stod(t.substr(0, found));
				t = t.substr(found +1, t.length());
				found = t.find(" ");
				values[2] = stod(t.substr(0, found));
				values[3]  = stod(t.substr(found +1, t.length()));
				for (j=0; j<4; j++){
					*datos = values[j];
					datos++;
				}
				//for (int s=0; s<4; s++)	cout << values[s] <<"	";
				//cout << endl;
				i++;
			}
			t2 = line.substr(0, 1);
		}
		*nfils = i;
		nfils = nfils - cont;
		*nfils = cont;
	}
	/*
	cout << "######################################################################################" << endl;
	cout << endl;
	cout << endl;
	for (i=0; i<10; i++){
		cout << *nfils << "	";
		nfils++;
	}
	cout << endl;
	*/
}

