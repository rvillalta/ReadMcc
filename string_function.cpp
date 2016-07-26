#include <iostream>
#include <string>
#include <fstream>
using namespace std;
void get_values(string &, double *, bool);
void ver_matriz(double *, int );
void explora(string , string *, int *, int *);
int main()
{
	ifstream pa;
	int i = 0, nscans, num_lin_scans[10];
	int *int_nscans, *int_num_lin_scans;
	string line, temp, parameters[10], *str_ptr;;
	string::size_type len;
	double *val, *val2, datos[3], matriz[300][3];
	str_ptr = parameters;
	int_nscans = &nscans;
	int_num_lin_scans = &num_lin_scans[0];
	pa.open("prueba.txt");
	val=datos;
	val2 = &matriz[0][0];
	if(!pa.is_open())
	{
		cout << "NO SE PUDO ABRIR" << endl;
	}
	else
	{
		while(!pa.eof())
		{
			getline(pa,line);
			if (line.length() != 0)
			{			
				explora("ElectronPdd.mcc", str_ptr, int_nscans, int_num_lin_scans);
				get_values(line, val, true);
				for (int j=0; j<3; j++) matriz[i][j] = datos[j]; 
				i++;
			}
		}
	}
	ver_matriz(val2, i);
	return 1;
}


void get_values(string &str, double *ptr, bool opt)
{
	size_t found;
	str = str.substr(3, str.length());
	found = str.find("	");
	*ptr = stod(str.substr(0, found));
	ptr++;
	str = str.substr(found +2, str.length());
	found = str.find("	");
	*ptr = stod(str.substr(0, found));
	if (opt){
		ptr++;
		*ptr = stod(str.substr(found+2, str.length()));
	}
}


void ver_matriz(double *ptr, int nfil)
{
	cout << "##################################################" << endl;
	cout << endl;
	for (int i = 0; i < nfil; i++){
		cout << "| ";
		for (int j = 0; j < 3; j++){
			cout << *ptr << " | ";
			ptr++;
		}
		cout << endl;
	}
	cout << "##################################################" << endl;
}

void explora(string filename, string *parametros, int *num_scans, int *num_line_scans)
{
	string line, temp;
	string::size_type len;
	int cont=1, i;
	size_t found;
	*num_scans = 0;
	ifstream pa;
	pa.open(filename);
	if (!pa.is_open()) cout << "No se pudo abrir " << filename << endl;
	else {
		while (!pa.eof()){
			getline(pa, line);
			cout << cont << "	" << line << endl;
			found = line.find("FILE_CREATION_DATE");
			if (found != string::npos){
				found = line.find("=");
				*parametros = line.substr(found +1, line.length());
				cout << "ptr " << *parametros << endl;
				parametros++;	
				cout << "Lo encontre en la " << cont << endl;
			}
			cin >> i;

			cout << "linea " << cont <<"	fecha " << found << endl;
			found = line.find("BEGIN_SCAN");
			if (found != string::npos){
				*num_scans = *num_scans + 1;
			}

			found = line.find("LINAC");
			if (found != string::npos){
				found = line.find("=");
				*parametros = line.substr(found +1, line.length());
				parametros++;	
			}

			found = line.find("MODALITY");
			if (found != string::npos){
				found = line.find("=");
				*parametros = line.substr(found +1, line.length());
				parametros++;	
			}

			found = line.find("ENERGY");
			if (found != string::npos){
				found = line.find("=");
				*parametros = line.substr(found +1, line.length());
				parametros++;	
			}

			found = line.find("SSD");
			if (found != string::npos){
				found = line.find("=");
				*parametros = line.substr(found +1, line.length());
				parametros++;	
			}

			found = line.find("FIELD_INPLANE");
			if (found != string::npos){
				found = line.find("=");
				*parametros = line.substr(found +1, line.length());
				parametros++;	
			}

			found = line.find("FIELD_CROSSPLANE");
			if (found != string::npos){
				found = line.find("=");
				*parametros = line.substr(found +1, line.length());
				parametros++;	
			}

			found = line.find("SCAN_CURVE_TYPE");
			if (found != string::npos){
				found = line.find("=");
				*parametros = line.substr(found +1, line.length());
				parametros++;	
			}

			found = line.find("");
			if (found != string::npos){
				found = line.find("=");
				*parametros = line.substr(found +1, line.length());
				parametros++;	
			} 



			cont++;
		}
	}
	pa.close();
}
