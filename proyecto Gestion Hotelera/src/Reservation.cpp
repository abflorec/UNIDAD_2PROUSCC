#include "Reservation.h"
#include <iostream>
#include <iomanip>

int Reservation::contadorReservas = 1000;

Reservation::Reservation(Cliente* cliente, Room* habitacion, 
                         std::string fechaCheckIn, std::string fechaCheckOut,
                         int numPersonas, std::string observaciones)
    : idReserva(++contadorReservas), cliente(cliente), habitacion(habitacion),
      fechaCheckIn(fechaCheckIn), fechaCheckOut(fechaCheckOut),
      numNoches(5), // Simplificado: asumimos 5 noches
      numPersonas(numPersonas), checkInRealizado(false),
      checkOutRealizado(false), observaciones(observaciones) {
    
    habitacion->setEstado(EstadoHabitacion::RESERVADA);
}

int Reservation::getIdReserva() const { return idReserva; }
Cliente* Reservation::getCliente() const { return cliente; }
Room* Reservation::getHabitacion() const { return habitacion; }
std::string Reservation::getFechaCheckIn() const { return fechaCheckIn; }
std::string Reservation::getFechaCheckOut() const { return fechaCheckOut; }
int Reservation::getNumNoches() const { return numNoches; }
int Reservation::getNumPersonas() const { return numPersonas; }
bool Reservation::getCheckInRealizado() const { return checkInRealizado; }
bool Reservation::getCheckOutRealizado() const { return checkOutRealizado; }
std::string Reservation::getObservaciones() const { return observaciones; }

double Reservation::getCostoTotal() const {
    double costoTotal = habitacion->calcularCosto(numNoches);
    
    // Sumar costo de servicios
    for (const auto& servicio : serviciosConsumidos) {
        costoTotal += servicio.getPrecio();
    }
    
    return costoTotal;
}

void Reservation::setObservaciones(std::string nuevasObservaciones) {
    observaciones = nuevasObservaciones;
}

void Reservation::agregarServicio(Servicio servicio) {
    serviciosConsumidos.push_back(servicio);
    std::cout << "Servicio agreado: " << servicio.getNombre() << " ($" << servicio.getPrecio() << ")\n";
}

std::vector<Servicio> Reservation::getServiciosConsumidos() const {
    return serviciosConsumidos;
}

void Reservation::realizarCheckIn() {
    if (!checkInRealizado) {
        checkInRealizado = true;
        habitacion->setEstado(EstadoHabitacion::OCUPADA);
        std::cout << "Check-in realizado para la reserva #" << idReserva << "\n";
    }
}

void Reservation::realizarCheckOut() {
    if (checkInRealizado && !checkOutRealizado) {
        checkOutRealizado = true;
        habitacion->setEstado(EstadoHabitacion::DISPONIBLE);
        std::cout << "Check-out realizado para la reserva #" << idReserva << "\n";
    }
}

bool Reservation::estaActiva() const {
    return checkInRealizado && !checkOutRealizado;
}

void Reservation::mostrarInfo() const {
    std::cout << "=== INFORMACION DE RESERVA ===\n";
    std::cout << "ID Reserva: #" << idReserva << "\n";
    std::cout << "Cliente: " << cliente->getNombreCompleto() << "\n";
    std::cout << "Habitacion: " << habitacion->getNumero() << "\n";
    std::cout << "Check-in: " << fechaCheckIn << "\n";
    std::cout << "Check-out: " << fechaCheckOut << "\n";
    std::cout << "Noches: " << numNoches << "\n";
    std::cout << "Personas: " << numPersonas << "\n";
    
    if (!serviciosConsumidos.empty()) {
        std::cout << "Servicios adicionales:\n";
        for (const auto& s : serviciosConsumidos) {
            std::cout << "  - " << s.getNombre() << " ($" << std::fixed << std::setprecision(2) << s.getPrecio() << ")\n";
        }
    }

    std::cout << "Costo total: $" << std::fixed << std::setprecision(2) << getCostoTotal() << "\n";
    std::cout << "Estado: ";
    if (!checkInRealizado) {
        std::cout << "Pendiente de check-in";
    } else if (!checkOutRealizado) {
        std::cout << "Activa (ocupada)";
    } else {
        std::cout << "Completada";
    }
    std::cout << "\n";
    if (!observaciones.empty()) {
        std::cout << "Observaciones: " << observaciones << "\n";
    }
}

void Reservation::modificarFechas(std::string nuevaCheckIn, std::string nuevaCheckOut) {
    fechaCheckIn = nuevaCheckIn;
    fechaCheckOut = nuevaCheckOut;
}