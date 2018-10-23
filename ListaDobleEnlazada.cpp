#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <iterator>

using namespace std;

/********************NODO*************************/
struct Nodo{

       string nombre;
       int matricula;
       struct Nodo *siguiente;
       struct Nodo *anterior;
};

typedef struct Nodo *Tlista; //ALIAS

/********************INSERTAR*************************/

void Insertar(Tlista &inicio,Tlista &fin){
    
    Tlista nuevo;
    //IMPORTANDO ARCHIVO
    ifstream myfile("alumnos.txt");
    string data;
    
    while(!myfile.eof())
	{
		//EXTRAER INFORMACIÓN LINEA POR LINEA
    	getline(myfile,data);
		   
		nuevo=new(struct Nodo);	
		//CONVERTIR STRING A INT	
		nuevo->matricula=atoi(data.c_str());
		//OBTENER STRING	
		nuevo->nombre=data;
		//ENLAZAR NODOS	
		if(inicio==NULL)
		{
          inicio=nuevo;
          inicio->siguiente=NULL;
          inicio->anterior=NULL;
          fin=inicio;
        }
	    else
	    {
          fin->siguiente=nuevo;
          nuevo->siguiente=NULL;
          nuevo->anterior=fin;
          fin=nuevo;
        }   	
	}

}

/********************DESPLEGAR LISTA*************************/

void MostrarLista(Tlista &inicio,Tlista &fin,int op1)
{
    Tlista aux;
    if(op1==1)
    {

       //CICLO PARA DESPLEGAR LISTA
       aux = inicio;
         while(aux != NULL)
         {
          cout <<"\n "<< aux->matricula <<" "<< aux->nombre << endl;
          aux = aux->siguiente;
         }
          
          cout<<endl;
          cout<<"Al reves"<<endl;
     
          aux = fin;
     
         while(aux !=NULL)
         {
          cout <<"\n "<< aux->matricula <<" "<< aux->nombre << endl;
          aux= aux->anterior;
         }
    }
    
    //MOSTRAR ELEMENTOS ORDENADOS POR SELECCIÓN
    if(op1==2)
    {
      ofstream generar("OrdenadosSeleccion.txt");
      aux = inicio;
      
      while(aux != NULL)
      {
         generar <<"\n "<< aux->matricula <<" "<< aux->nombre << endl;
          aux = aux->siguiente;
      }	
    }

   //MOSTRAR ELEMENTOS ORDENADOS POR QUICKSORT
    if(op1==3)
    {    
      ofstream generar("OrdenadosQuickSort.txt");
      aux = inicio;
      
     while(aux != NULL)
     {
         generar <<"\n "<< aux->matricula <<" "<< aux->nombre << endl;
          aux = aux->siguiente;
     }	 
    }

}

/********************ORDENAMIENTO POR SELECCIÓN*************************/

void OrdenarSeleccion(Tlista &inicio){
	
	Tlista aux2=inicio,aux3=NULL,aux4=inicio;
    string nom,nom1;
    int min,aux,a,au;
	
	cout<<"Orden por Seleccion"<<endl;
	
    while(aux2!=NULL)
	{
	    aux4=aux2->siguiente;
	    min=aux2->matricula; //MINIMO
	    
	     while(aux4!=NULL)
		 {
		 		
	     	if( aux4->matricula<min)
			 {
	     		min=aux4->matricula;
	     		nom=aux4->nombre;
	     		aux3=aux4; //ALMACENAMIENTO EN EL AUX3
	     		a=1; //INDICADOR
			 }
		 
		      aux4=aux4->siguiente;
		 
		    if(aux4==NULL&&a==1)
		   {
		   	//SWAP
			au=aux2->matricula;
			nom1=aux2->nombre;
			
			aux3->matricula=au;
			aux3->nombre=nom1;
			
		    aux2->matricula=min;
		    aux2->nombre=nom;
		   }
	   }
	   aux2=aux2->siguiente;
	   a=0;
	} 	
}

/********************ORDENAMIENTO POR QUICKSORT************************/

//INTERCAMBIO DE NODOS
void swap ( Tlista &a, Tlista &b )
{  Tlista t; t = a;  a = b;  b = t;   }

//PARTICIONES
Tlista partition(Tlista &l, Tlista &h)
{
	Tlista i,j;
	
    int x  = h->matricula;
 
      i = l->anterior; 
 

    for (j = l; j != NULL; j = j->siguiente)
    {
        if (j->matricula < x)
        {
            (i == NULL)? i = l : i = i->siguiente;
 
            swap(i, j);
        }
    }
    i = (i == NULL)? l : i->siguiente; 
    
    swap(i, h);
    
    return i;
}

//RECURSIVIDAD
void quickSort(Tlista &l,Tlista &h)
{
   if (h != NULL && l != h && l != h->siguiente)
    {
        Tlista p = partition(l, h);
        quickSort(l, p->anterior);
        quickSort(p->siguiente, h);
        
    }
}

//MÉTODO PRINCIPAL QUICKSORT
void Quicksort(Tlista &inicio)
{
	
    Tlista aux = inicio;
    //ENCONTRANDO EL ÚLTIMO NODO
     while(aux != NULL)
     {
          aux = aux->siguiente;
     }
    quickSort(inicio, aux);
    
}
		
/********************MENÚ*************************/

void GenerarMenu()
{
    cout<<"\n\t\tLista Doblemente Enlazada\n\n";
    cout<<" 1. Insertar             "<<endl;
    cout<<" 2. Mostrar             "<<endl;
    cout<<" 3. Ordenar por Seleccion             "<<endl;
    cout<<" 4. Ordenar por Quicksort            "<<endl;
    cout<<" 5. SALIR                "<<endl;
}

/********************MAIN*************************/

main(){

    Tlista inicio = NULL;
    Tlista fin;
    int op,op1;
    string nom,cadena;
    int mat,matp;

    system("color 0a"); 
    

    do{
        GenerarMenu();
        cout<<" >Opcion: ";
        cin>> op;
        switch(op){
            //INSERTAR AL INICIO
            case 1:
                 Insertar(inicio,fin);
                 cout<<"\n Datos ingresados"<<endl;
            break;
           //MOSTRAR
            case 2:
            	if(inicio!=NULL)
				{
					MostrarLista(inicio,fin,1);
				}
				else
				{
				 cout<<"\n No hay datos ingresados"<<endl;	
				}
            break;
            //ORDENAR SELECCION
            case 3:
            	if(inicio!=NULL)
            	{
            	  OrdenarSeleccion(inicio);
            	  MostrarLista(inicio,fin,2);
            	  cout<<"\n Archivo generado"<<endl;
				}
				else
				{
				 cout<<"\n No hay datos ingresados"<<endl;		
				}
            	
            break;
            case 4:
            //ORDENAR QUICKSORT
            if(inicio!=NULL)
            {
              Quicksort(inicio);
              MostrarLista(inicio,fin,3);
			  cout<<"\n Archivo generado"<<endl;	
			}
			else
			{
			 cout<<"\n No hay datos ingresados"<<endl;	
			}
                
            	break;
            default:
                cout<<"\n Opcion incorrecta"<<endl;
            }

       cout<<endl<<endl;
       getch();
       system("cls");
       
    }while(op!=5);

   system("pause");
   return 0;
}
