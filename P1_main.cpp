// PROYECTO AHORCADO ADRIANA VEGA 11351101
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
using std::getline;

void leerArchivo(char**);
void imprimirArreglo(char**,int);
void iniciarGuess(char*, int);
void imprimirJuego(int, int, int, char*);
bool ganar(char*);
int numeroLetras(char**, int);
int compararLetra(char, char*, char*);
int compararPalabra(char*, char*, char*&);

int main(int argc, char* argv[]){
	//creacion arreglo palabras
	const int numpalabras = 30; // numero de palabras en el arreglo
	char** palabras = new char*[numpalabras];
	for (int i = 0; i < numpalabras; ++i){
		palabras[i] = new char[10];
	}
	leerArchivo(palabras);
	//imprimirArreglo(palabras,numpalabras);
	//JUEGO
	srand(time(0));
	int opcion=0;
	cout << "\nBIENVENIDO A AHORCADO\n1- Partida Facil (4-5 letras)\n2- Partida Media (6-7 letras)\n3- Partida Dificil (8-9 letras)\n4-Salir\nIndique lo que desea hacer: ";
	cin >> opcion;
	while(opcion < 4 && opcion > 0){
		int errores=0, aciertos=0;
		int posicion = ((opcion-1)*numpalabras/3)+rand()%(numpalabras/3); // dependiendo del nivel de dificultad, se escojera la palabra correcta
		int letras = numeroLetras(palabras,posicion);
		char* respuesta = new char[letras];
		char* guess = new char[letras];
		respuesta = palabras[posicion]; 
		//cout << respuesta << endl;
		iniciarGuess(guess,letras);
		do{
			imprimirJuego(aciertos,errores,letras,guess);
			cout << "\n1- una letra\n2- la palabra\nCual desea adivinar? ";
			cin >> opcion;
			switch(opcion){
				case 1:{ //adivinar por letra
					char letra;
					cout << "Ingrese la letra: ";
					cin >> letra;
					if(compararLetra(letra,respuesta,guess) == 0)
						aciertos++;
					else
						errores++;
					break;
				}
				case 2:	{
					char* palabra = new char[letras];
					cout << "Ingrese la palabra: ";
					cin >> palabra;
					if(compararPalabra(palabra,respuesta,guess) == 0)
						aciertos++;
					else
						errores++;
					break;}
			}
			//errores++;
		}while(errores < 6 && !ganar(guess));
		if(ganar(guess)){
			imprimirJuego(aciertos,errores,letras,guess);
			cout << "\tGANO!!" << endl;
		}else{
			imprimirJuego(aciertos,errores,letras,guess);
			cout << "\tPERDIO!! La palabra era \"" << respuesta << "\"" << endl;
		}
		cout << "\nBIENVENIDO A AHORCADO\n1- Partida Facil\n2- Partida Media\n3- Partida Dificil\n4-Salir\nIndique lo que desea hacer: ";
		cin >> opcion;
	}
	cout << "ADIOS!!\n" << endl;
	return 0;
} // fin main

int compararLetra(char letra, char* respuesta, char* guess){
	int posicion=0, encontradas=0;
	while(respuesta[posicion] != '\0'){
		if(respuesta[posicion]==letra){
			guess[posicion] = letra;
			encontradas++;
		}
		posicion++;
	}
	if(encontradas == 0)
		return 1;
	else
		return 0;
}

int compararPalabra(char* palabra, char* respuesta, char*& guess){
	int posicion=0, encontradas=0;
	while(respuesta[posicion] != '\0'){
		if(respuesta[posicion]==palabra[posicion]){
			encontradas++;
		}
		posicion++;
	}
	if(encontradas != posicion)
		return 1;
	else{
		posicion = 0;
		while(respuesta[posicion] != '\0'){
			guess[posicion] = respuesta[posicion];
			posicion++;
		}
		return 0;
	}
}

void leerArchivo(char** palabras){
	int i =0;
	char* palabra = new char[10];
	ifstream documento;
	documento.open("P1_palabras.txt");
	while(!documento.eof()){
		documento.getline(palabra,10);
		if(palabra[0] != '-'){
			palabras[i] = palabra;
			i++;
		}
		palabra = new char[10];
	}
	documento.close();
}

void iniciarGuess(char* guess, int letras){
	for (int i = 0; i < letras; ++i){
		guess[i] = '_';
	}
}

void imprimirArreglo(char** palabras, int num){
	cout << "{ ";
	for (int i = 0; i < num; ++i)
		cout << palabras[i] << " ";
	cout << "}" << endl;
}

void imprimirJuego(int aciertos, int errores, int letras, char* guess){
	cout << "\n\t _____" << endl;
	if(ganar(guess)){
		cout << "\t|     |\n\t|         ___\n\t|        {^v^}\n\t|         \\|/\n\t|          |\n\t|         / \\" << endl;
	} else{
		switch(errores){
			case 0:
				cout << "\t|     |\n\t|\n\t|\n\t|\n\t|\n\t|" << endl;
				break;
			case 1:
				cout << "\t|    _|_\n\t|   {^.^}\n\t|\n\t|\n\t|\n\t|" << endl;
				break;
			case 2:
				cout << "\t|    _|_\n\t|   {^_^}\n\t|     |\n\t|     |\n\t|\n\t|" << endl;
				break;
			case 3:
				cout << "\t|    _|_\n\t|   {^_^}\n\t|    /|\n\t|     |\n\t|\n\t|" << endl;
				break;
			case 4:
				cout << "\t|    _|_\n\t|   {>.<}\n\t|    /|\\\n\t|     |\n\t|\n\t|" << endl;
				break;
			case 5:
				cout << "\t|    _|_\n\t|   {>_<}\n\t|    /|\\\n\t|     |\n\t|    /\n\t|" << endl;
				break;
			case 6:
				cout << "\t|    _|_\n\t|   {X_X}\n\t|    /|\\\n\t|     |\n\t|    / \\\n\t|" << endl;	
				break;	
		}
	}
	cout << "\n\taciertos = " << aciertos << "\terrores = " << errores << "\n\t[ ";
	for (int i = 0; i < letras; ++i)
		cout << guess[i] << " ";
	cout << "]\n" << endl;		
}

int numeroLetras(char** lista, int posicion){
	int num_letras=1;
	while(lista[posicion][num_letras] != '\0')
		num_letras++;
	return num_letras;
}

bool ganar(char* guess){
	int i=0;
	bool gano = true;
	while(guess[i] != '\0'){
		if(guess[i] == '_')
			gano = false;
		i++;
	}
	return gano;
}