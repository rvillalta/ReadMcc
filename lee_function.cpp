/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@												 												 @
@		PROGRAMA QUE LEE LOS ARCHIVOS W2CAD CON LOS QUE SE ALIMENTA EL ECLIPSE           		 @
@				Raul Villalta Julio 2016					 									 @
@												 												 @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

// COMPILAR USANDO LA OPCION: 	-STD=C++11

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;
void lee_archivo(string, double * , int *);
void escribe_archivo(string, double *, int *, int *);
int main()
{
	double *dat, data[80000];
	string filename;
	int *fils, *sel, control[100],  filas[100], i, j, ndatos, ntot,  k = 0, s = 1, tt, select[4] = {1, 0, 0, 1};
	sel = select;
	dat = data;
	fils = filas;
	filename = "/home/raul/Documentos/Commissioning/Eclipse Beam Data/X06_MLC/0600DPR.asc";
	lee_archivo(filename, dat, fils);
	//lee_archivo("X06 OPEN 2X2 CR PinPoint.CD2", dat, fils);
	//cout << "Entre el nombre del archivo de salida  " ;
	//getline(cin, filename);
	dat = data;

	escribe_archivo("salida.txt", dat, fils, sel);
	ndatos = filas[0];
	control[0] = 0;
	ntot = 0;
	/*			VER SALIDA DE DOATOS LEIDA
	 *
	 * 


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
			//cin >> tt;
		}
		
	}*/

	return 0;
}
void escribe_archivo(string filename, double *datos, int *nfils, int *sel)
{
	/* Este programa escribe los datos leidos por la funcion
	 * lee_archivo() y los ecribe de manera selectiva en columnas ordenadas 
	 * de manera que puedan ser utilizadas por el programa GNUPLOT
	 
	 FILENAME nombre del archivo donde sera escrita la data.
	 *DATOS puntero al vector double donde esta lamacenados los datos
			leidos por lee_archivo()
	 *NFILS puntero al vector int donde esta guardada la informacion
	 		sobre el numero de filas de cada uno de los set de datos del
	        archivo, el primer elemento (nfils[0]) almacenara eñ numero 
	        de sets diferentes de datos
	 */
	 
	 ofstream pa, pb;
	 int s = 1, i, k, j, d, nset, col, fil, depth, cont, nfil_max = 0, select[4], ntot, control[300];
	 double data[300][4][100];
	 bool check;
	 pa.open(filename);
	 pb.open("data.txt");
	 control[0] = 0;
	 cont = 0;
	 depth = 0;
	 nset = *nfils;
	 cout << "nset " << nset << endl;
	 int filas[nset];
	 nfils++;
	 for (i = 0; i < nset +	 1; i++){filas[i] = *nfils; cout << i << "  " << filas[i] << endl; nfils++; }
	
	 for (i = 0; i < 4; i++){select[i] = *sel;sel++;}
	 
	 for (i = 0; i < nset; i++){ntot = ntot + filas[i];}

	 for (i = 1; i < nset + 1 ; i++) if (nfil_max < filas[i]) nfil_max = filas[i];
	cout << "max_nfils " << nfil_max;
	// "******************** CREACION DE LA MATRIZ DATA[][][] *************************" << endl;
	cont = -1;
	for (k = 0; k < nset; k++){
		cont++;
		for (i = 0; i < filas[cont]; i++){
			for (j = 0; j < 4; j++){
				data[i][j][k] = *datos;
				datos++;
			}
		}
	}
	i = 2;
	cout << "	my data   " << data[0][i][0] << endl;
	cout << "	my data   " << data[0][i][1] << endl;
	cout << "	my data   " << data[0][i][2] << endl;
	cout << "	my data   " << data[0][i][3] << endl;
	// "******************** FIN CREACION DE LA MATRIZ DATA[][][] *************************" << endl;
	for (fil=0; fil < 10; fil++){
		for(col=0; col < 4; col++){
			cout << data[fil][col][3] << " ";
		}
		cout << endl;
	}
	cout << "*********************************************************** " << endl;
	for (i =0; i < nfil_max; i++){
		for (d = 0; d < nset; d++){
			for (j = 0; j < 4; j++){
				if (select[j]){
					if (i > filas[d]) pa << "	" << " " ;
					else pa << showpos << setprecision(1) << fixed << data[i][j][d] << "	";
				}
				 
			 }
		}
		pa << endl;
	}
	pa.close();
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
					//cout << "#####################################################" << endl;
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

