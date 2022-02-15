#include "cabecera.h"

using namespace std;

int main()
{
    /*
    GABRIEL VIVAS

    Implementación de la solución de Misioneros y Caníbales
    Realizamos un árbol con los movimientos posibles:
    1. 1C-> A o B
    2. 2C-> A o B
    3. 1M-> A o B
    4. 2M-> A o B
    5. 1M & 1C-> A o B
    La  solución se realiza mediante búsqueda por profundidad
    */
    Arbol arbol;
    arbol.crearArbol();
    return 0;
}
