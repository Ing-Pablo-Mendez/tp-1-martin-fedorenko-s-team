#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define filename1 "Conductores.bin"
#define filename2 "Procesados.bin"

using namespace std;

struct conductor
{
    char conductorID[6];
    int fechavencimiento;
    bool activo = true;
    int totalinfracciones=0;
    int totalmonto=0;
    char email[6];
};

struct infraccion
{
    char infraccionID[6];
    char fechahora[13];
    int monto;
    char conductorID[6];
    char provincia[6];
};

struct listaconductores
{
    char conductores[6];
};

void creardatosdepruebaconductores()
{
    FILE *f1;
    conductor c[6];

    strcpy(c[0].conductorID, "00001");
    c[0].fechavencimiento = 20201101;
    c[0].activo = true;
    c[0].totalinfracciones = 0;
    c[0].totalmonto = 0;
    strcpy(c[0].email, "a.com");

    strcpy(c[1].conductorID, "00002");
    c[1].fechavencimiento = 20201103;
    c[1].activo = true;
    c[1].totalinfracciones = 0;
    c[1].totalmonto = 0;
    strcpy(c[1].email, "b.com");

    strcpy(c[2].conductorID, "00003");
    c[2].fechavencimiento = 20201105;
    c[2].activo = true;
    c[2].totalinfracciones = 0;
    c[2].totalmonto = 0;
    strcpy(c[2].email, "c.com");

    strcpy(c[3].conductorID, "00004");
    c[3].fechavencimiento = 20201101;
    c[3].activo = true;
    c[3].totalinfracciones = 0;
    c[3].totalmonto = 0;
    strcpy(c[3].email, "d.com");

    strcpy(c[4].conductorID, "00055");
    c[4].fechavencimiento = 20201101;
    c[4].activo = true;
    c[4].totalinfracciones = 0;
    c[4].totalmonto = 0;
    strcpy(c[4].email, "e.com");

    if (f1=fopen(filename1,"wb"))
    {
        fwrite(c, sizeof(conductor),5,f1);
        fclose(f1);
    }
    return;
}

bool guardarconductor()
{
    FILE *f1;
    conductor c;
    if (f1=fopen(filename1,"ab"))
    {
        cout << "\nIngrese ID del conductor (5 caracteres):" << endl;
        cin >>  c.conductorID;
        cout << "Ingrese fecha de vencimiento del registro (AAAAMMDD):" << endl;
        cin >> c.fechavencimiento;
        cout << "Ingrese eMail (5 caracteres):" << endl;
        cin >> c.email;
        fwrite(&c, sizeof(conductor),1,f1);
        fclose(f1);
        return true;
    }
    return false;
}

int mostrarconductores()
{
    FILE *f1;
    conductor c;
    if (f1=fopen(filename1,"rb"))
    {
        fread(&c,sizeof(conductor),1,f1);
        cout << "\n";
        while(!feof(f1))
        {
            cout << "ID del conductor: " << c.conductorID << endl;
            cout << "Fecha de vencimiento del registro (AAAAMMDD): " << c.fechavencimiento << endl;
            cout << "Total de infracciones previas: " << c.totalinfracciones << endl;
            cout << "eMail: " << c.email << endl;
            cout << "Estado del conductor: " << c.activo << endl << endl;
            fread(&c,sizeof(conductor),1,f1);
        }
        fclose(f1);
        return 1;
    }
    return 0;
}

int buscarconductor()
{
    FILE *f1;
    conductor c;
    char buscado[6], opc;
    int encontrado = 0;

    cout << "\nInserte ID o eMail del conductor que desea encontrar:" << endl;

    cin >> buscado;

    if(f1=fopen(filename1,"rb+"))
    {
        while(!encontrado && fread(&c,sizeof(conductor),1,f1))
        {
            if ((strcmp(c.conductorID, buscado)==0) || (strcmp(c.email, buscado)==0))
            {
                cout << "\n¿Que desea hacer?" << endl;
                cout << "A - Mostrar datos del conductor " << c.conductorID << endl;
                cout << "B - Desactivar al conductor " << c.conductorID << endl;
                cout << "C - Mostrar infracciones y monto en total del conductor " << c.conductorID << endl;
                cout << "Presione ESC para salir..." << endl;
                do
                {
                    opc = getch();
                }while ( opc != 'a' && opc != 'A' && opc != 'b'&& opc != 'B'  && opc != 'c' && opc != 'C' && opc != 27 );

                switch (opc)
                {
                    case 'a':
                    case 'A':
                        encontrado = 1;
                        cout << "\nID del conductor: " << c.conductorID << endl;
                        cout << "Fecha de vencimiento del registro (AAAAMMDD): " << c.fechavencimiento << endl;
                        cout << "Infracciones totales: " << c.totalinfracciones << endl;
                        cout << "eMail: " << c.email << endl;
                        cout << "Estado del conductor: " << c.activo << endl << endl;
                    break;
                    case 'b':
                    case 'B':
                        encontrado = 1;
                        c.activo = false;
                        fseek(f1,(-1)*sizeof(conductor), SEEK_CUR);
                        fwrite(&c, sizeof(conductor),1,f1);
                        cout << "\nEl conductor fue desactivado" << endl << endl;
                    break;
                    case 'c':
                    case 'C':
                        encontrado = 1;
                        cout << "\nEl conductor " << c.conductorID << " posee un monto total de " << c.totalmonto << "$ debido a " << c.totalinfracciones << " infracciones." << endl << endl;
                    break;
                }
            }
        }
        if(!encontrado)
        {
            cout << "\nEl conductor que usted busca no existe..." << endl << endl;
        }
        fclose(f1);
        return 1;
    }
    return 0;
}

int listarporprovincia()
{
    FILE *f2;
    infraccion inf;
    char provincia[6];
    listaconductores lista[100];
    int i, j=0, encontrado;

    cout << "\Inserte el codigo de la provincia que desea evaluar:" << endl;

    cin >> provincia;

    if(f2=fopen(filename2,"rb"))
    {
        while(fread(&inf,sizeof(infraccion),1,f2))
        {
            encontrado = 0;
            i=0;
            if (strcmp(inf.provincia, provincia)==0)
            {
                do
                {
                    if (strcmp(inf.conductorID, lista[i].conductores)==0)
                    {
                        encontrado = 1;
                    }
                    if (!encontrado)
                    {
                        strcpy(lista[j].conductores, inf.conductorID);
                        j++;
                    }
                    i++;
                }
                while(strcmp(inf.conductorID, lista[i].conductores)==0);
            }
        }
        if(!j)
        {
            cout << "\nNingun conductor registrado cometio infracciones en esta provincia" << endl << endl;
        }
        else
        {
            cout << "\Los conductores que cometieron infracciones en la provincia son: " << endl;
            for(i=0; i<j; i++)
            {
                cout << lista[i].conductores << endl;
            }
            cout << "\n";
        }
        fclose(f2);
        return 1;
    }
    return 0;
}

void procesarlote()
{
    FILE *f1;
    FILE *f2;
    infraccion inf[100];
    conductor c;
    char opc;
    int i, encontrado;

    do
    {
        encontrado = 0;
        cout << "\nIngrese ID de la infraccion (5 caracteres):" << endl;
        cin >>  inf[i].infraccionID;
        cout << "Ingrese fecha y hora de la infraccion (AAAAMMDDHHMM):" << endl;
        cin >> inf[i].fechahora;
        cout << "Ingrese el monto de la infraccion:" << endl;
        cin >> inf[i].monto;
        cout << "Ingrese ID del conductor (5 caracteres):" << endl;
        cin >>  inf[i].conductorID;
        cout << "Ingrese provincia (5 caracteres):" << endl;
        cin >> inf[i].provincia;

        if(f1=fopen(filename1,"rb+"))
        {
            while(!encontrado && fread(&c,sizeof(conductor),1,f1))
            {
                if (strcmp(c.conductorID,inf[i].conductorID)==0)
                {
                    cout << "Datos actualizados" << endl;
                    encontrado=1;
                    c.totalinfracciones++;
                    c.totalmonto=c.totalmonto+inf[i].monto;
                    fseek(f1,(-1)*sizeof(conductor), SEEK_CUR);
                    fwrite(&c, sizeof(conductor),1,f1);
                }
            }
            if(!encontrado)
            {
                cout << "El conductor que usted ingreso no existe, registrelo por favor..." << endl;
                guardarconductor();
                cout << "Reingrese los datos de la infraccion por favor..." << endl;
                continue;
            }
        fclose(f1);
        }
        else
        {
            cout << "No existe el archivo 'Conductores.bin'" << endl;
        }

        if(f2=fopen(filename2, "ab"))
        {
            fwrite(inf, sizeof(infraccion),1,f2);
            fclose(f2);
        }
        else
        {
            cout << "No se pudo crear archivo Infracciones.bin" << endl;
        }

        cout << "Presiones cualquier tecla si desea continuar, ESC si desea salir.\n" << endl;
        opc=getch();
        if(opc==27)
            break;
        else
            continue;
    }
    while(opc!=27);
}

void finalizarjornada(int fechaactual)
{
    FILE *faux;
    FILE *f1;
    conductor c;
    faux = fopen("auxiliar.bin","wb");
        if (f1=fopen(filename1,"rb+"))
        {
            while(fread(&c,sizeof(conductor),1,f1))
            {
                if (c.activo && (fechaactual<c.fechavencimiento))
                {
                    fwrite(&c, sizeof(conductor),1,faux);
                }
            }
            fclose(f1);
        }
        fclose(faux);
        if (!remove(filename1))
        {
            if(!rename("auxiliar.bin",filename1))
                cout << "Archivo procesado correctamente" << endl;
            else
                cout << "No se pudo procesar el archivo" << endl;
        }
        else
            cout << "No fue posible eliminar el archivo anterior" << endl;
}

char menu()
{
    char opc;
    cout << "Seleccione una opcion:" << endl;
    cout << "A - Crear datos de prueba" << endl;
    cout << "B - Guardar un registro de conductor"<< endl;
    cout << "C - Mostrar todos los registros de conductores"<< endl;
    cout << "D - Buscar un registro de conductor (desactivar o mostrar datos)"<< endl;
    cout << "E - Listar conductores que cometieron infracciones en determinada provincia"<< endl;
    cout << "F - Procesar lote de infracciones" << endl;
    cout << "ESC - Salir/Finalizar jornada" << endl;
    do
        opc = getch();
    while (opc != 'a' && opc != 'A' && opc != 'b'&& opc != 'B'  && opc != 'c' && opc != 'C' && opc != 'd' && opc != 'D' && opc != 'e' && opc != 'E' && opc != 'f' && opc != 'F' && opc != 27);
    switch (opc)
    {
        case 'a':
        case 'A':
            creardatosdepruebaconductores();
                cout << "\nSe crearon los datos de prueba" << endl <<endl;
        break;
        case 'b':
        case 'B':
            if (guardarconductor())
                cout << "El registro se ha guardado." << endl <<endl;
            else
                cout << "Error al intentar guardar el archivo." << endl;
        break;
        case 'c':
        case 'C':
            if(!mostrarconductores())
                cout << "Error al intentar abrir el archivo." << endl;
        break;
        case 'd':
        case 'D':
            if (!buscarconductor())
                cout << "Error al intentar abrir el archivo." << endl;
        break;
        case 'e':
        case 'E':
            if (!listarporprovincia())
                cout << "Error al intentar abrir el archivo." << endl;
        break;
        case 'f':
        case 'F':
            procesarlote();
        break;
    }
    return opc;
}

int main()
{
    char out;
    int fecha;

    cout << "Por favor introduzca la fecha del dia de hoy (AAAAMMDD):" << endl;
    cin >> fecha;
    fflush(stdin);

    do
        out = menu();
    while (out != 27);

    finalizarjornada(fecha);

    return 0;
}
