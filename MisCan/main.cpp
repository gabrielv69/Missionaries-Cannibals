#include "cabecera.h"

using namespace std;

int main()
{
    /*
    GABRIEL VIVAS

    Implementaci�n de la soluci�n de Misioneros y Can�bales
    Realizamos un �rbol con los movimientos posibles:
    1. 1C-> A o B
    2. 2C-> A o B
    3. 1M-> A o B
    4. 2M-> A o B
    5. 1M & 1C-> A o B
    La  soluci�n se realiza mediante b�squeda por profundidad
    */
    Arbol arbol;
    arbol.crearArbol();
    return 0;
}
