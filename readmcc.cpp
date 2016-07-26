#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
   string line, temp;
   int len=30, dim=3, i=1, fin =100, cont = 0;
   char file[10]="test.mcc";
   size_t found;
   ifstream pa(file);
   ofstream pb("salida.txt");
   if(!pa & !pb){
      cout << "No se pudo abrir " << file << endl;
   }
   else {
   	while(!pa.eof())
	{
		getline(pa, line);
		found = line.find("BEGIN_DATA");
		if(found != string::npos){
			cout << "Lo encontre en la linea " << i << endl;
			getline(pa, line);
			while(found != string::npos)
			{
				found = line.find("	");
				if (found != string::npos){
					line  = line.replace(found, 1, "");
					pb << line << endl;
					cont ++;
					cout << "f " << found << " tab ";
					cout  << cont << " line " << line << endl;
				}
			}
			cout << "Encontre " << cont << " tabs" << endl;
		}
		i++;
	}
   }
   pa.close();
   pb.close();
   return 0;
}
