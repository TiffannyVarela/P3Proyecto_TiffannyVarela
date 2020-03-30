#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

using namespace std;

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

bool limpiar(char*);//
bool listar(char*);//
bool crearCarpeta(char*);//
bool crearArchivo(char*);//
bool escribir(char*);//este escribe en chino una vez de por medio
bool leer(char*);//
bool cambiarColor(char*);//*
bool cambiarUser(char*);//
bool cambiarMaquina(char*);//*
bool salir(char*);//

bool is_dir(string dir)
{
  DIR * directorio;
  if (directorio = opendir(dir.c_str()))
  {
    closedir(directorio);
    return true;             
  }   
  else
  {
   return false;   
  }
}

bool is_file(string file)
{
 FILE * archivo;
 if (archivo = fopen(file.c_str(), "r"))
 {
  fclose(archivo);
  return true;           
 }    
 else
 {
  return false;  
 }
}

int font=2,back=0;
ofstream outfile;

string direccion=fs::current_path().generic_string();

int main(int argc, char const *argv[])
{
	//salir con tecla Esc
	/*
	char c;
	do
	{
		c=getch();
	} while (c!=27);
	 */
	string u="home";
	string m="vm-gauss";
	const char*  user=u.c_str();
	const char* maquina=m.c_str(); 
	const char* direc=direccion.c_str();
	vector <string> listaDir;
	listaDir.push_back(direccion);
	
	char c; 
	initscr();
	char p[128];
	if (has_colors()) start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	attrset(COLOR_PAIR(1));
	while(salir(p))
	{
		keypad(stdscr,TRUE);
		addstr(user);
		addstr("@");
		addstr(maquina);
		addstr(":");
		addstr(direc);
		addstr(":~$ ");
		refresh();
		getstr(p);
		//user = p;
		if (p[0]=='c' && p[1]=='l')
		{
			if (limpiar(p)){}
		}

		if (p[0]=='l' && p[1]=='s')
		{
			if (listar(p)){}
		}
		
		/*if (p[0]=='c' && p[1]=='d')
		{
			string nombre="";
			string lista="";
			string directorios="";
			string nuevo="";
			for (int i = 3; i < sizeof(p); i++)
			{
				nombre+=p[i];
			}
			if (is_dir(nombre)){
				DIR * directorio;
				struct dirent * elemento;
				string elem;
				for (int i = 0; i < listaDir.size(); i++)
				{
					if (i < listaDir.size()-1)
					{
						direccion+="/";
					}
					direccion+=nombre;
				}
				nuevo+="/"+nombre;
				listaDir.push_back(nuevo);
				if (directorio = opendir(direccion.c_str()))
				{ 
					while (elemento = readdir(directorio))
					{
				 		elem = elemento->d_name;
				 		//lista=lista+elem+"\n";
				 		if (is_dir(elem)) directorios=directorios+elem+"\n";
	  					else if (is_file(elem)) lista=lista+elem+"\n";
						
					}            
				}
				addstr(lista.c_str());
			}
  			else addstr("Elemento no existe\n");
				
			refresh();
		}
		

		if (p[0]=='c' && p[1]=='d'&& p[1]=='/')
		{
			string nombre="";
			string lista="";
			string directorios="";
			string nuevo="";
			listaDir.erase(listaDir.begin()+listaDir.size());
			DIR * directorio;
				struct dirent * elemento;
				string elem;
				direccion=direccion+"/"+nombre;
				for (int i = 0; i < listaDir.size(); i++)
				{
					direccion+=listaDir[i];
				}
				if (directorio = opendir(direccion.c_str()))
				{ 
					while (elemento = readdir(directorio))
					{
				 		elem = elemento->d_name;
				 		//lista=lista+elem+"\n";
				 		if (is_dir(elem)) directorios=directorios+elem+"\n";
	  					else if (is_file(elem)) lista=lista+elem+"\n";
						
					}            
				}
				addstr(lista.c_str());
		}*/

		if (p[0]=='d' && p[1]=='e'&&p[2]=='l'&&p[3]==' ')
		{
			fs::path dir = fs::temp_directory_path();
			string nombre="";
			if (is_dir(nombre) || is_file(nombre)){
				for (int i = 4; i < sizeof(p); i++)
				{
					nombre+=p[i];
				}
				fs::remove_all(dir/nombre);
				refresh();
			}
			else{
				addstr("El elemento no existe\n"); 
			}
		}
		
		if (p[0]=='m')
		{
			if (crearCarpeta(p)){
				string newcarpeta="";
				for (int i = 6; i < sizeof(p); i++)
				{
					newcarpeta+=p[i];
				}
				fs::create_directories(newcarpeta);
				refresh();
			}
		}

		if (p[0]=='f')
		{
			if (crearArchivo(p)){
				string newarchivo="";
				for (int i = 5; i < sizeof(p); i++)
				{
					newarchivo+=p[i];
				}
				//outfile.open(ruta + nombreArchivo + ".txt", std::ios::app);
				outfile.open(newarchivo, std::ios::app);
				outfile.close();
				refresh();
			}
		}

		if (p[0]=='w')
		{
			if (escribir(p)){
				string comando="";
				for (int i = 0; i < sizeof(p); i++)
				{
					comando+=p[i];
				}
				string cadena="";
				string nombre="";
				size_t found = comando.find(".txt ");
				for (int i = 6; i < found+4; i++)
				{
					nombre+=p[i];
				}  				
				//error de escritura, escribe a veces en chino
				if (is_file(nombre))
				{
					size_t found2 = comando.find(" ");
					cadena=comando.substr(found+5,found2-1);
					outfile.open(nombre, std::ios::app);
					outfile<<cadena<<" ";
					outfile.close();
				}
				else addstr("Elemento no existe\n");
				refresh();
			}
		}
		
		if (p[0]=='r'&&p[1]=='e'&&p[2]=='a')
		{
			if (leer(p)){
				string comando="";
				for (int i = 5; i < sizeof(p); i++)
				{
					comando+=p[i];
				} 				
				if (is_file(comando))
				{
					ifstream archivo(comando);
					char linea[128];

				    if(archivo.fail()){
					    addstr("Error al abrir el archivo ");
						addstr(comando.c_str());
					}
				    else{
					    while(!archivo.eof())
					    {
					        archivo>>linea;
					        addstr(linea);
					        addstr("\n");
					    }
					    archivo.close();
					}
				}
				else addstr("Elemento no existe\n");
				refresh();
			}
		}

		if (cambiarColor(p)){
			if (sizeof(p)>=15)
			{
				if (p[12]=='r'&&p[13]=='e'&&p[14]=='d')
				{
					font = 2;
					back =1;
					start_color();
					init_pair(2, font, back);
					wbkgd(stdscr,COLOR_PAIR(2));
				}
				else if (p[12]=='b'&&p[13]=='l'&&p[14]=='c'&&p[14]=='k')
				{
					font = 2;
					back =0;
					start_color();
					init_pair(2, font, back);
					wbkgd(stdscr,COLOR_PAIR(2));
				}
				else if (p[12]=='w'&&p[13]=='h'&&p[14]=='i'&&p[14]=='t'&&p[14]=='e')
				{
					font = 2;
					back =7;
					start_color();
					init_pair(2, font, back);
					wbkgd(stdscr,COLOR_PAIR(2));
				}
			}
		}
		if (p[6]=='M'&&p[7]=='a'&&p[8]=='c'&&p[9]=='h'&&p[11]=='i')
		{
			if (cambiarMaquina(p))
			{
				string newmaquina="";
				for (int i = 15; i < sizeof(p); i++)
				{
					newmaquina+=p[i];
				}
				maquina=newmaquina.c_str();
				addstr(maquina);
				refresh();
			}
		}
		if (p[6]=='U')
		{
			if (cambiarUser(p))
			{
				string newUser="";
				for (int i = 11; i < sizeof(p); i++)
				{
					newUser+=p[i];
				}
				user=newUser.c_str();
				addstr(user);
				refresh();
			}
		}
		if (salir(p))
		{
		}
	}
	return 0;
}

bool limpiar(char* x){
	if (sizeof(x)>=5)
	{
		if (x[0]=='c'&&x[1]=='l'&&x[2]=='e'&&x[3]=='a'&&x[4]=='r')
		{
			clear();
			refresh();
		}
	}
}


bool listar(char* x){
	if (sizeof(x)>=2)
	{
		
		string lista="";
		string directorios="";
		if (x[0]=='l'&&x[1]=='s')
		{
			
			DIR * directorio;
			struct dirent * elemento;
			string elem;
			if (directorio = opendir(direccion.c_str()))
			{ 
				while (elemento = readdir(directorio))
				{
			 		elem = elemento->d_name;
			 		//lista=lista+elem+"\n";
			 		if (is_dir(elem)) directorios=directorios+elem+"\n";
  					else if (is_file(elem)) lista=lista+elem+"\n";
					
				}            
			}
			addstr(lista.c_str());
			if (has_colors()) start_color();
			font = 6;
			init_pair(3, 6, back);
			attroff(A_BOLD);
			attrset(COLOR_PAIR(3) | A_BOLD);
			printw(directorios.c_str());
			refresh();

			init_pair(4, 2, back);
			attroff(A_BOLD);
			attrset(COLOR_PAIR(4));
			refresh();
			closedir(directorio);
		}
	}
}


bool crearCarpeta(char* x){
	if (sizeof(x)>=7)
	{
		if (x[0]=='m'&&x[1]=='k'&&x[2]=='d'&&x[3]=='i'&&x[4]=='r'&&x[5]==' ')
		{
			
		}
	}
}


bool crearArchivo(char* x){
	if (sizeof(x)>=6)
	{
		if (x[0]=='f'&&x[1]=='i'&&x[2]=='l'&&x[3]=='e'&&x[4]==' ')
		{
			
		}
	}
}


bool escribir(char* x){
	if (sizeof(x)>=7)
	{
		if (x[0]=='w'&&x[1]=='r'&&x[2]=='i'&&x[3]=='t'&&x[4]=='e'&&x[5]==' ')
		{
			
		}
	}
}


bool leer(char* x){
	if (sizeof(x)>=6)
	{
		if (x[0]=='r'&&x[1]=='e'&&x[2]=='a'&&x[3]=='d'&&x[4]==' ')
		{

		}
	}
}


bool cambiarColor(char* x){
	if (sizeof(x)>=13)
	{
		if (x[0]=='c'&&x[1]=='h'&&x[2]=='a'&&x[3]=='n'&&x[4]=='g'&&x[5]=='e'&&x[6]=='C'&&x[7]=='o'&&x[8]=='l'&&x[9]=='o'&&x[10]=='r'&&x[11]==' ')
		{
			
		}
	}
}


bool cambiarUser(char* x){
	if (sizeof(x)>=12)
	{
		if (x[0]=='c'&&x[1]=='h'&&x[2]=='a'&&x[3]=='n'&&x[4]=='g'&&x[5]=='e'&&x[6]=='U'&&x[7]=='s'&&x[8]=='e'&&x[9]=='r'&&x[10]==' ')
		{
			
		}
	}
}


bool cambiarMaquina(char* x){
	if (sizeof(x)>=16)
	{
		if (x[0]=='c'&&x[1]=='h'&&x[2]=='a'&&x[3]=='n'&&x[4]=='g'&&x[5]=='e'&&x[6]=='M'&&x[7]=='a'&&x[8]=='c'&&x[9]=='h'&&x[11]=='i'&&x[12]=='n'&&x[13]=='3'&&x[14]==' ')
		{
			
		}
	}
}


bool salir(char* x){
	if (sizeof(x)>=4)
	{
		if (x[0]=='e'&&x[1]=='x'&&x[2]=='i'&&x[3]=='t')
		{
			endwin();
		}
	}
}


