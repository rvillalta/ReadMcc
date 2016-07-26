

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
void get_values(string &, double *);
void ver_matriz(double *, int );
void explora(string &);
int main()
{
	ifstream pa;
	int i = 0;
	string line, temp;
	string::size_type len;
	double *val, *val2, datos[3], matriz[300][3];
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
				get_values(line, val);
				for (int j=0; j<3; j++) matriz[i][j] = datos[j]; 
				i++;
			}
		}
	}
	ver_matriz(val2, i);
	return 1;
}


void get_values(string &str, double *ptr)
{
	size_t found;
	str = str.substr(3, str.length());
	found = str.find("	");
	*ptr = stod(str.substr(0, found));
	ptr++;
	str = str.substr(found +2, str.length());
	found = str.find("	");
	*ptr = stod(str.substr(0, found));
	ptr++;
	*ptr = stod(str.substr(found+2, str.length()));
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

void explora(string &filename)
{
	ifstream pa;
	pa.open(filename);
	if (!pa.is_open()) coutt << "No se pudo abrir " << filename << endl;
	else {
		while (!pa.eof(){

		}
	}
}
