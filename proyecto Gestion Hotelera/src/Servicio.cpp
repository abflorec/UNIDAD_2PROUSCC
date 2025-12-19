#include "Servicio.h"
#include <iostream>
#include <iomanip>

Servicio::Servicio(int id, TipoServicio tipo, std::string nombre, 
                   std::string descripcion, double precio)
    : idServicio(id), tipo(tipo), nombre(nombre), 
      descripcion(descripcion), precio(precio), disponible(true) {}

int Servicio::getIdServicio() const { return idServicio; }
TipoServicio Servicio::getTipo() const { return tipo; }
std::string Servicio::getNombre() const { return nombre; }
std::string Servicio::getDescripcion() const { return descripcion; }
double Servicio::getPrecio() const { return precio; }
bool Servicio::getDisponible() const { return disponible; }

std::string Servicio::getTipoString() const {
    switch(tipo) {
        case TipoServicio::RESTAURANTE: return "Restaurante";
        case TipoServicio::SPA: return "Spa";
        case TipoServicio::LAVANDERIA: return "Lavandería";
        case TipoServicio::TRANSPORTE: return "Transporte";
        case TipoServicio::GIMNASIO: return "Gimnasio";
        case TipoServicio::PISCINA: return "Piscina";
        case TipoServicio::MINIBAR: return "Minibar";
        case TipoServicio::ROOM_SERVICE: return "Room Service";
        default: return "Desconocido";
    }
}

void Servicio::setPrecio(double nuevoPrecio) { 
    if (nuevoPrecio > 0) precio = nuevoPrecio; 
}

void Servicio::setDisponible(bool disponible) { 
    this->disponible = disponible; 
}

void Servicio::setDescripcion(std::string nuevaDescripcion) { 
    descripcion = nuevaDescripcion; 
}

void Servicio::mostrarInfo() const {
    std::cout << "=== INFORMACION DE SERVICIO ===\n";
    std::cout << "ID: " << idServicio << "\n";
    std::cout << "Nombre: " << nombre << "\n";
    std::cout << "Tipo: " << getTipoString() << "\n";
    std::cout << "Descripcion: " << descripcion << "\n";
    std::cout << "Precio: $" << std::fixed << std::setprecision(2) << precio << "\n";
    std::cout << "Disponible: " << (disponible ? "Si" : "No") << "\n";
}

void Servicio::aplicarDescuento(double porcentaje) {
    if (porcentaje > 0 && porcentaje <= 100) {
        double descuento = precio * (porcentaje / 100);
        precio -= descuento;
    }
}