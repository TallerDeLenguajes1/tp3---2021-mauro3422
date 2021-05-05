#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char *TiposProductos[]={"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};

typedef struct {
    int ProductoID;
    int Cantidad;
    char *TipoProducto;
    float PrecioUnitario;

}producto;
typedef struct{
    int ClienteID;
    char *NombreCliente;
    int CantidadProductosAPedir;
    producto *productos;
}cliente;
void cargarCliente(cliente *item, int cant);
float costoTotalProducto(producto *item);
void mostrarCliente(cliente *item,int indice);
int main(void){

    srand(time(NULL));
    int cantCli;
    float sumatoria;

    do
    {
        printf("Ingrese la cantidad de clientes solo hasta 5:");
        scanf("%d",&cantCli);
        fflush(stdin);
        printf("-------------------------------\n");   

    } while ( cantCli>5 || cantCli<0);
    


    cliente *lista=(cliente *)malloc(cantCli*sizeof(cliente));
    cargarCliente(lista,cantCli);

    for (int i = 0; i < cantCli; i++)
    {   
        //reseteo
        sumatoria=0;
        for (int j = 0; j < lista[i].CantidadProductosAPedir; j++)
        {
            sumatoria+=costoTotalProducto((lista+i)->productos+j);
        }
        mostrarCliente(lista,i);
        printf("---Costo total del inventario:%2.f---\n----------------------------\n",sumatoria);
        
    }
    




    
    free(lista->productos->TipoProducto);
    free(lista->productos);
    free(lista->NombreCliente);
    free(lista);
    getchar();
    return 0;
}



void cargarCliente(cliente *item,int cant){
   for (int i = 0; i < cant; i++)
   {
        printf("----------Cliente ID:[%d]----------\n",i+1);
        //Cliente ID
        item[i].ClienteID=i;
        printf("Ingrese el Nombre del cliente:");
        item[i].NombreCliente=(char *)malloc(sizeof(char)*30);
        fflush(stdin);
        gets(item[i].NombreCliente);    
        //Aleatoriamente consigo una cantidad de productos diferentes a pedir 
        item[i].CantidadProductosAPedir=rand()%(5-1+1)+1;
        printf("----Productos Diferentes a ingresar [%d]----\n",item[i].CantidadProductosAPedir);
        //Reservo memoria para el struct producto.
        item[i].productos=(producto *)malloc(sizeof(producto)*item[i].CantidadProductosAPedir);
        //Lo cargo
        for (int j = 0; j < item[i].CantidadProductosAPedir; j++)
        {
            //Determino el id del producto.
            item[i].productos[j].ProductoID=j;
            //Cantidad del producto.
            item[i].productos[j].Cantidad=rand()%(4-1+1)+1;
            //Calculo algun indice para el Arreglo TiposProducto
            int temp=rand()%(4-0+1)+0;
            //Reservo memoria para la cadena asi se pueda guardar.
            item[i].productos[j].TipoProducto=(char *)malloc(sizeof(char)*13);
            //Guardo el nombre del producto.
            strcpy(item[i].productos[j].TipoProducto,TiposProductos[temp]);
            //Consigo un precio aleatorio.
            item[i].productos[j].PrecioUnitario=rand() % ((100-10)+1)+10;
        
    
        }
    }
}
void mostrarCliente(cliente *item,int indice){
    
    printf("Cliente ID [%d]\n",item[indice].ClienteID);
    printf("Nombre:%s\n",item[indice].NombreCliente);
    printf("Cantidad de productos pedidos:%d\n",item[indice].CantidadProductosAPedir);
    for (int i = 0; i < item[indice].CantidadProductosAPedir; i++)
    {
        printf("-------Producto [%d]-------\n",i+1);
        printf("ID:%d\n",item[indice].productos[i].ProductoID);
        printf("Cantidad:%d\n",item[indice].productos[i].Cantidad);
        printf("Tipo de producto:%s\n",item[indice].productos[i].TipoProducto);
        printf("Precio Unitario:%2.f\n",item[indice].productos[i].PrecioUnitario);
    }
    
}

float costoTotalProducto(producto *item){
    return item->PrecioUnitario*item->Cantidad;
}