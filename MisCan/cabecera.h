#ifndef CABECERA_H_INCLUDED
#define CABECERA_H_INCLUDED
#include <iostream>

//GABRIEL VIVAS
using namespace std;
class Estado
{
public:
    int E[3];//M/C/B

    Estado()//Constructor inicializo valores en 3 Generamos ESTADO INCIAIL
    {
        E[0]=3;//M
        E[1]=3;//C
        E[2]=1;//B
    };

    bool testObj()  //Funcion test objetivo
    {
        bool flag=1;
        for(int i=0; i<3; i++)
        {
            if (E[i]!=0)
                flag=0;
        }
        return flag;
    };

    bool checkLose()
    {
        bool flag = 0;
        //Restricciones M>C en ambas orillas
        if((E[0]>0 && E[0]<E[1] )|| (3-E[0]>0 && 3-E[0]<3-E[1]))
            flag=1;
        return flag;
    };

    //Dado que al aplicar los posibles cambios de estado se puede dar
    //estados inválidos por ejemplo [4,2,1], ES necesario validar los cambios a realizar
    bool validarEstado()
    {
        bool flag =0;
        if(E[0]<0 || E[0]>3|| E[1]<0 || E[1]>3 )
            flag=1;
        return flag;
    };

    void print()
    {
        cout<<E[0]<<" "<<E[1]<<" "<<E[2]<<" "<<endl;
    };

    void changeEstado(int opcion)
    {

        int signo = (E[2]==1) ? -1 : 1;
        switch(opcion)
        {
        case 0: //1C
            E[1]+=1*signo;
            break;
        case 1: //2C
            E[1]+=2*signo;
            break;
        case 2: //1M
            E[0]+=1*signo;
            break;
        case 3:  //2M
            E[0]+=2*signo;
            break;
        case 4: //1M 1C
            E[1]+=1*signo;
            E[0]+=1*signo;
            break;
        }

        if(validarEstado()||checkLose())
            for(int i=0; i<3; i++)
                E[i]=-1;

        //Mover bote
        E[2]= (E[2]==0) ? 1 : 0;
    };
};

class Nodo
{
public:
    Estado estado;
    Nodo *P;
    Nodo *H[5];
    int N;  //Nivel de profundidad del nodo
    int C;  //Costo acumulado de pasos desde el estado inicial
    bool flag;

    //constructor
    Nodo()
    {
        P=NULL;
        flag=0;
        for (int i =0; i<5; i++)
            H[i]= NULL;
        N=0;
        C=0;
    };

};


class Visitados
{
public:
    int nV;
    int *V = new int[3];

    Visitados()
    {
        nV= 0;
        for(int i=0; i<3; i++)
            V[i]=-2;
    };

    void print()
    {
        for(int i=0; i<(nV-1)*3; i++)
        {
            cout<<V[i]<<"  " ;
            if((i+1)%3==0)
                cout<<""<<endl;
        }
    };

    void nuevoElemento(int est[])
    {
        int elementos = nV*3;
        int *aux= new int[elementos];
        if(V[0]==-2)
        {
            for(int j=0; j<3; j++)
                V[j]= est[j];
        }
        else
        {
            for(int i=0; i<elementos-3; i++)
                aux[i]= V[i];

            aux[elementos-3]= est[0];
            aux[elementos-2]= est[1];
            aux[elementos-1]= est[2];

            delete[] V;
            V=aux;
            aux=NULL;
        }
        nV++;
    };


    bool existeEstado(int est[])
    {
        bool flag =0;
        for(int i=0; i<(nV-1)*3; i= i+3)
        {
            //cout<<"ESTO ES i "<<i<<endl;
            if(V[i]==est[0] && V[i+1]==est[1] && V[i+2]==est[2])
                flag=1;
        }
        return flag;
    };


};

class Frontera
{
public:
    Nodo **f; //Arreglo de punteros a nodos
    int nEf;  //nUMERO ELEMENTOS EN FRONTERA

    Frontera()
    {
        f= NULL;
        nEf=0;
    };

    //Destructor Frontera
    ~Frontera()
    {
        for(int i=0; i<nEf; i++)
            f[i]=NULL;
        delete[]f;
        f=NULL;
        nEf=0;

    };

    void ordenarFrontera()
    {
        //Implementar un algoritmo de ordenamiento

    };


    //Copio la frontera actual a un aux, anado Nodo n a aux
    // y Aux es eel nuevo F
    void nuevoElemento(Nodo *n)
    {
        Nodo **aux;
        aux = new Nodo*[nEf+1];
        for(int i=0; i<nEf; i++)
        {
            aux[i]=f[i];
            f[i]=NULL;
        }
        aux[nEf]=n;
        if(nEf>0)
            delete[] f;
        f=NULL;
        f=aux;
        nEf++;

    };

    void print()
    {
        cout<< "Esto es mi Solucion "<<endl;
        for(int i=nEf-1; i>-1; i--)
            f[i]->estado.print();
    };
};

class Arbol
{
public:
    Frontera fr;
    Nodo *na; //Nodo actual
    Visitados visit; //Estados visitados
    void crearArbol()
    {
        Nodo n; //Nodo raiz
        na= &n;
        visit.nV=1;
        crearHijos(na);

    };

    void crearHijos(Nodo *na)
    {
        cout<<"================"<< endl;
        cout<<"Nivel actual:"<< na->N << endl;
        if(na->estado.testObj())
        {
            na->estado.print();
            cout<<"Es objetivo"<< endl;
            return;
        }

        cout<<"Estado Actual:";
        na->estado.print();
        visit.nuevoElemento(na->estado.E);
        //cout<<"\\\\\\\\\\\\\\\\\\"<< endl;
        //visit.print();
        //cout<<"\\\\\\\\\\\\\\\\\\"<< endl;
        for (int i =0; i<5; i++)
        {
            na->H[i]= new Nodo;
            na->H[i]-> P=na;
            na->H[i]->estado = na->estado;
            na->H[i]->N= na->N+1;
            na->H[i] ->estado.changeEstado(i);
            //na->H[i] ->estado.print();
            //cout<<visit.existeEstado(na->estado.E)<<endl;
            if(na->H[i]->estado.E[0]==-1||(visit.existeEstado(na->H[i]->estado.E)))
            {
                na->H[i] = NULL;
                continue;
            }
            else
            {
                na->H[i]-> estado.print();
                //na = na->H[i];
                crearHijos(na->H[i]);
            }
            //Verifico final
            if(na->H[i]->estado.testObj())
            {
                na = na->H[i];
                while( na->P!=NULL)
                {
                    fr.nuevoElemento(na);
                    na=na->P;
                }
                cout<<"Es objetivo"<< endl;
                fr.nuevoElemento(na);
                fr.print();
                //return;
                exit(0);
            }
        }
        /*
        for (int i =0; i<5; i++)
        {
            if(na->H[i]==NULL)
                continue;
            na = na->H[i];
            crearHijos(na);
        }*/
    };
};
#endif // CABECERA_H_INCLUDED
