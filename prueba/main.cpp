#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

using namespace std;

// variables globales
const int MAX_PRODUCTOS = 100;

int ids[MAX_PRODUCTOS];
string productos[MAX_PRODUCTOS];
int cantidades[MAX_PRODUCTOS];
double precios[MAX_PRODUCTOS];
int totalProductos = 0;
int siguienteID = 1;

// prototipo de funciones y procedimientos
void ingresarProducto();
void venderProducto();
void consultarStock();
void mostrarInventario();
void mostrarMenu();
void gestionarInventario();
void gotoxy(int x, int y);
void setColor(int color);
void dibujarCuadro(int x1, int y1, int x2, int y2);

// procedimientos

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void dibujarCuadro(int x1, int y1, int x2, int y2) {
    for (int i = x1; i <= x2; i++) {
        gotoxy(i, y1);
        cout << "\xC4"; // -
        gotoxy(i, y2);
        cout << "\xC4"; // -
    }

    for (int i = y1; i <= y2; i++) {
        gotoxy(x1, i);
        cout << "\xB3"; // ¦
        gotoxy(x2, i);
        cout << "\xB3"; // ¦
    }

    gotoxy(x1, y1);
    cout << "\xDA"; // +
    gotoxy(x1, y2);
    cout << "\xC0"; // +
    gotoxy(x2, y1);
    cout << "\xBF"; // +
    gotoxy(x2, y2);
    cout << "\xD9"; // +
}

void ingresarProducto() {
    if (totalProductos < MAX_PRODUCTOS) {
        system("CLS");
        setColor(14); // Color amarillo
        dibujarCuadro(20, 5, 60, 13);
        gotoxy(22, 6);
        cout << "Ingrese nombre del producto: ";
        gotoxy(22, 7);
        cin >> productos[totalProductos];
        gotoxy(22, 8);
        cout << "Ingresar cantidad del producto: ";
        gotoxy(22, 9);
        cin >> cantidades[totalProductos];
        gotoxy(22, 10);
        cout << "Ingresar precio del producto: ";
        gotoxy(22, 11);
        cin >> precios[totalProductos];
        ids[totalProductos] = siguienteID++;
        totalProductos++;
        gotoxy(22, 12);
        setColor(10); // Color verde
        cout << "Producto ingresado con exito!";
        _getch();
    } else {
        system("CLS");
        setColor(12); // Color rojo
        dibujarCuadro(20, 5, 60, 7);
        gotoxy(22, 6);
        cout << "Inventario lleno. No se puede ingresar más productos.";
        _getch();
    }
}

void venderProducto() {
    system("CLS");
    int id;
    int cantidad;
    setColor(14); // Color amarillo
    dibujarCuadro(20, 5, 60, 11);
    gotoxy(22, 6);
    cout << "Ingresar ID del producto a vender: ";
    gotoxy(22, 7);
    cin >> id;
    gotoxy(22, 8);
    cout << "Ingresar cantidad a vender: ";
    gotoxy(22, 9);
    cin >> cantidad;

    for (int i = 0; i < totalProductos; i++) {
        if (ids[i] == id) {
            if (cantidades[i] >= cantidad) {
                cantidades[i] -= cantidad;
                gotoxy(22, 10);
                setColor(10); // Color verde
                cout << "Venta realizada.";
            } else {
                gotoxy(22, 10);
                setColor(12); // Color rojo
                cout << "Cantidad insuficiente en el inventario.";
            }
            _getch();
            return;
        }
    }
    gotoxy(22, 10);
    setColor(12); // Color rojo
    cout << "Producto no encontrado.";
    _getch();
}

void consultarStock() {
    system("CLS");
    int id;
    setColor(14); // Color amarillo
    dibujarCuadro(20, 5, 60, 9);
    gotoxy(22, 6);
    cout << "Ingresar ID del producto a consultar: ";
    gotoxy(22, 7);
    cin >> id;

    for (int i = 0; i < totalProductos; i++) {
        if (ids[i] == id) {
            gotoxy(22, 8);
            setColor(10); // Color verde
            cout << "Stock de " << productos[i] << ": " << cantidades[i];
            _getch();
            return;
        }
    }
    gotoxy(22, 8);
    setColor(12); // Color rojo
    cout << "Producto no encontrado.";
    _getch();
}

void mostrarInventario() {
    system("CLS");
    setColor(14); // Color amarillo
    dibujarCuadro(10, 2, 70, 4 + totalProductos);
    gotoxy(12, 3);
    cout << "Inventario actual:";
    for (int i = 0; i < totalProductos; i++) {
        gotoxy(12, 4 + i);
        cout << "ID: " << ids[i]
             << ", Producto: " << productos[i]
             << ", Cantidad: " << cantidades[i]
             << ", Precio: $" << precios[i];
    }
    _getch();
}

void mostrarMenu() {
    system("CLS");
    setColor(11); // Color azul claro
    dibujarCuadro(20, 5, 60, 13);
    gotoxy(22, 6);
    cout << "Gestion de Inventario";
    gotoxy(22, 7);
    cout << "1. Ingresar Producto";
    gotoxy(22, 8);
    cout << "2. Vender Producto";
    gotoxy(22, 9);
    cout << "3. Consultar Stock";
    gotoxy(22, 10);
    cout << "4. Mostrar Inventario";
    gotoxy(22, 11);
    cout << "5. Salir";
    gotoxy(22, 12);
    cout << "Seleccionar opcion: ";
}

void gestionarInventario() {
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                ingresarProducto();
                break;
            case 2:
                venderProducto();
                break;
            case 3:
                consultarStock();
                break;
            case 4:
                mostrarInventario();
                break;
            case 5:
                cout << "Saliendo...\n";
                break;
            default:
                setColor(12); // Color rojo
                gotoxy(22, 14);
                cout << "Opcion no valida. Intente otra opcion.";
        }

    } while (opcion != 5);
}

int main(int argc, char** argv) {
    system("CLS");
    gestionarInventario();
    return 0;
}

