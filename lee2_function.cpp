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
void lee_archivo(string, double * , int *, int *, string *);
void escribe_archivo(string, double *, int *, int *);
int main()
{
	double *dat, data[80000];
	string filename, prueba[3], *ptr_str;
	int *fils, *sel, control[100],  filas[100], i, j, ndatos, ntot,  k = 0, s = 1, tt, select[4];
	sel = select;
	dat = data;
	fils = filas;
	ptr_str = prueba;
	filename = "Open_PDD_sorted.ASC";
	//filename = "X06 OPEN 2X2 CR PinPoint.CD2";
	lee_archivo(filename, dat, fils, sel, ptr_str);
	
	for (i=0; i<3; i++) cout << prueba[i] << endl;
	
	dat = data;
	escribe_archivo("salida.txt", dat, fils, sel);
	ndatos = filas[0];
	control[0] = 0;
	ntot = 0;
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
	 ifstream gr;
	 int s = 1, i, k, j, d, nset, col, fil, depth, cont, nfil_max = 0, select[4], ntot, control[300];
	 double data[1000][4][100];
	 bool check;
	 string line;
	 size_t found;
	 pa.open(filename);
	 
	 control[0] = 0;
	 cont = 0;
	 depth = 0;
	 nset = *nfils;
	 cout << "nset " << nset << endl;
	 int filas[nset];
	 nfils++;
	 cout << " NFILAS " << endl;
	 //for (i = 0; i < nset +	 1; i++){filas[i] = *nfils; cout << i << "  " << filas[i] << endl; nfils++; }
	 for (i = 0; i < nset ; i++){filas[i] = *nfils; cout << i << "  " << filas[i] << endl; nfils++; }
	
	 for (i = 0; i < 4; i++){select[i] = *sel; sel++;}
	 
	 for (i = 0; i < nset; i++){ntot = ntot + filas[i];}

	 for (i = 0; i < nset  ; i++) if (nfil_max < filas[i]) nfil_max = filas[i];
	 //for (i = 1; i < nset + 1 ; i++) if (nfil_max < filas[i]) nfil_max = filas[i];
	 //if (nset < 2) nfil_max = 1;
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
	// "******************** FIN CREACION DE LA MATRIZ DATA[][][] *************************" << endl;
	//cout << "select = [";
	//for (i =0; i < nset, i++) cout << selct
	//cout << "]" << endl;
	cout << endl;
	for (fil=780; fil < 791; fil++){
		for(col=0; col < 4; col++){
			cout << "data[" << fil << "][" << col << "] =" << data[fil][col][0] << " ";
		}
		cout << endl;
	}
	pa << "#";
	for (i = 0; i < 2 * nset; i++) pa << "	" << setw(2) << i + 1 <<" 	" ;
	pa << endl;
	for (i =0; i < nfil_max; i++){
		//cout << "TT " << data[i][j][d] << endl;
		for (d = 0; d < nset; d++){
			for (j = 0; j < 4; j++){
				if (select[j]){
					//if (i > filas[d]) pa << "	" << " " ;
					if (i > filas[d]-1) {
						pa << "-----" << "	" ;
					}
					//else pa << showpos << setprecision(1) << fixed << data[i][j][d] << "	";
					else pa << setfill(' ') << setw(5) << setprecision(1) << fixed << data[i][j][d] << "	";
				}
				 
			 }
		}
		pa << endl;
	}
	pa.close();	
	/*
	pb.open("graph.gp");
	gr.open("molde_gnuplot.gp");
	if (!gr.is_open() | !pb.is_open()){
		cout << " NO SE PUDO ABRIR ALGUN ARCHIVO PARA CREAR EL COMANDO PARA GNUPLOT" << endl;
	}
	else{
		while (!pb.eof()){
			getline(gr, line);
			pb << line << endl;
			found = line.find("GNUTERM");
			if (found != string::npos){
				
			}
		}
	}
	pb.close();
	gr.close();
	*/
}

void lee_archivo(string filename, double *datos , int *nfils, int *ptr_sel, string *pal)
{
/*
	FILENAME  nombre del archivo del cual se extraera la data
	*DATOS    puntero a dobles donde se almacenaran los datos leidos
		  en el siguiente orden X Y Z data
	*NFILS    puntero a enteros donde se almacenara el numero de filas de
		  cada uno de los set de datos del archivo, el primer elemento
		  (nfils[0]) almacenara eñ numero de sets diferentes de datos*/

	*pal = "A";
	pal++;
		*pal = "Como";
	pal++;
		*pal = "Tego Hambre";
	
	ifstream pa;
	string line, t, t1, t2;
	int i, cont, j, k, opt[3][4];
	double values[4];
	size_t found;
	bool bandera = false, check = true, pass = true;
	string word, param[13][2], temp[13];
	// Definicion de la matriz opt para seleccionar los datos a visualizar
	for (i = 0; i < 3; i++){
		for (j = 0; j < 4; j++){
			if (j < 3) opt[i][j] = 0;
			else opt[i][j] = 1;
		}
	}
	for (i = 0; i < 3; i++) opt[i][i] = 1;
	param[0][0] = "%DATE";
	param[0][1] = "FECHA DE LA MEDICION 			";
	param[1][0] = "%VERSION";
	param[1][1] = "VERSION DEL ARCHIVO W2CAD 		";
	param[2][0] = "%DETY";
	param[2][1] = "TIPO DE DETECTOR 			";
	param[3][0] = "%BMTY";
	param[3][1] = "TIPO DE HAZ 				";
	param[4][0] = "%TYPE";
	param[4][1] = "TIPO DE MEDIDA 				";
	param[5][0] = "%WDGL";
	param[5][1] = "NOMBRE DE LA CUÑA 			";
	param[6][0] = "%WDGD";
	param[6][1] = "DIRECCION DE LA CUÑA 		";
	param[7][0] = "%AXIS";
	param[7][1] = "MEDIDA EN EL EJE 			";
	param[8][0] = "%PNTS";
	param[8][1] = "NUMERO DE PUNTOS 			";
	param[9][0] = "%STEP";
	param[9][1] = "SEPARACION ENTRE PUNTOS [mm/10]		";
	param[10][0] = "%SSD";
	param[10][1] = "DISTANCIA FUENTE SUPERFICIE [mm]	";
	param[11][0] = "%FLSZ";
	param[11][1] = "TAMAÑO DE CAMPO [mm] 			";
	param[12][0] = "%DPTH";
	param[12][1] = "PROFUNDIDAD DE LA MEDIDA [mm]		";
	
	
	pa.open(filename);
		if(!pa.is_open()){
		cout << "NO SE PUDO ABRIR EL ARCHIVO " << filename << endl;
	}
	else{
		cout << "ARCHIVO " << filename <<" ABIERTO EXITOSAMENTE" << endl;
		getline(pa, line);
		found = line.find(" ");
		cout << endl;
		cout << "	Hay un total de " << stoi(line.substr(found + 1, line.length())) << " Set de datos" << endl;
		while (!pa.eof()){
			getline(pa, line);
			// Detecta el fin de una curva
			found = line.find("$ENOM");
			if (found != string::npos){
				 cout << endl;
				 word = word + temp[3];
				 word = word + "_";
				 word = word + temp[4];
				 word = word + "_";
				 word = word + temp[11];
				 //word = word + "_";
			 }
			found = line.find("%");
			if (found != string::npos){
				for (i = 0; i < 13; i++){
					found = line.find(param[i][0]);
					if (found != string::npos){
						found = line.find(" ");
						cout << param[i][1] << line.substr(found + 1, line.length()) << endl; //$ENOM
						temp[i] = line.substr(found + 1, line.length());
					}
				}
			}
			
		}
	}
	pa.close();
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
			//Selecciona el vector sel de acuerdo al tipo de curva
			found = line.find("%AXIS");
			if (found != string::npos && check){
					check = false;
					found = line.find(" "); // busca espacio
					//cout << "encontre " << line.substr(found+1,1) << "	" << line.compare(found+1,1,"X") << endl;
					if (line.compare(found+1,1,"X") == 0){
						for (i = 0; i < 4; i++ ) {
							*ptr_sel = opt[0][i];
							ptr_sel++;
						}
					}
					else if(line.compare(found+1,1,"Y") == 0){
						for (i = 0; i < 4; i++ ) {
							*ptr_sel = opt[1][i];
							ptr_sel++;
						}
					}
					else if(line.compare(found+1,1,"Z") == 0){
						for (i = 0; i < 4; i++ ) {
							*ptr_sel = opt[2][i];
							ptr_sel++;
						}
					}
			}
			if(t1 == "<" & t1 != t2){
				if(bandera) {
					*nfils = i;
					nfils++;
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

