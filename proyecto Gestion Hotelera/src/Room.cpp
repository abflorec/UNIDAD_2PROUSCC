#include "Room.h"
#include <iostream>
#include <iomanip>

Room::Room(int numero, TipoHabitacion tipo, double precioNoche, 
           int capacidad, bool tieneVista, std::string caracteristicas)
    : numero(numero), tipo(tipo), estado(EstadoHabitacion::DISPONIBLE),
      precioNoche(precioNoche), capacidad(capacidad), 
      tieneVista(tieneVista), caracteristicas(caracteristicas) {}

int Room::getNumero() const { return numero; }
TipoHabitacion Room::getTipo() const { return tipo; }
EstadoHabitacion Room::getEstado() const { return estado; }
double Room::getPrecioNoche() const { return precioNoche; }
int Room::getCapacidad() const { return capacidad; }
bool Room::getTieneVista() const { return tieneVista; }
std::string Room::getCaracteristicas() const { return caracteristicas; }

std::string Room::getTipoString() const {
    switch(tipo) {
        case TipoHabitacion::INDIVIDUAL: return "Individual";
        case TipoHabitacion::DOBLE: return "Doble";
        case TipoHabitacion::SUITE: return "Suite";
        case TipoHabitacion::PRESIDENCIAL: return "Presidencial";
        default: return "Desconocido";
    }
}

std::string Room::getEstadoString() const {
    switch(estado) {
        case EstadoHabitacion::DISPONIBLE: return "Disponible";
        case EstadoHabitacion::OCUPADA: return "Ocupada";
        case EstadoHabitacion::MANTENIMIENTO: return "Mantenimiento";
        case EstadoHabitacion::RESERVADA: return "Reservada";
        default: return "Desconocido";
    }
}

void Room::setEstado(EstadoHabitacion nuevoEstado) { estado = nuevoEstado; }
void Room::setPrecioNoche(double nuevoPrecio) { if (nuevoPrecio > 0) precioNoche = nuevoPrecio; }
void Room::setCaracteristicas(std::string nuevasCaracteristicas) { caracteristicas = nuevasCaracteristicas; }

bool Room::estaDisponible() const {
    return estado == EstadoHabitacion::DISPONIBLE;
}

void Room::mostrarInfo() const {
    std::cout << "=== INFORMACION DE HABITACION ===\n";
    std::cout << "Numero: " << numero << "\n";
    std::cout << "Tipo: " << getTipoString() << "\n";
    std::cout << "Estado: " << getEstadoString() << "\n";
    std::cout << "Precio por noche: $" << std::fixed << std::setprecision(2) << precioNoche << "\n";
    std::cout << "Capacidad: " << capacidad << " personas\n";
    std::cout << "Vista: " << (tieneVista ? "Si" : "No") << "\n";
    std::cout << "Caracteristicas: " << caracteristicas << "\n";
}

double Room::calcularCosto(int numNoches) const {
    return precioNoche * numNoches;
}