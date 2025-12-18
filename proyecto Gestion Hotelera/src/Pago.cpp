#include "Pago.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

int Pago::contadorPagos = 2000;

Pago::Pago(Reservation* reserva, double monto, MetodoPago metodo, 
           std::string numeroTransaccion)
    : idPago(++contadorPagos), reserva(reserva), monto(monto), 
      metodo(metodo), estado(EstadoPago::PENDIENTE) {
    
    // Generar fecha actual simple
    fechaPago = "15/06/2024 14:30";
    
    // Generar número de transacción si no se proporciona
    if (numeroTransaccion.empty()) {
        srand(time(0));
        int randomNum = 100000 + rand() % 900000;
        this->numeroTransaccion = "TXN" + std::to_string(randomNum);
    } else {
        this->numeroTransaccion = numeroTransaccion;
    }
}

int Pago::getIdPago() const { return idPago; }
Reservation* Pago::getReserva() const { return reserva; }
double Pago::getMonto() const { return monto; }
MetodoPago Pago::getMetodo() const { return metodo; }
EstadoPago Pago::getEstado() const { return estado; }
std::string Pago::getFechaPago() const { return fechaPago; }
std::string Pago::getNumeroTransaccion() const { return numeroTransaccion; }

std::string Pago::getMetodoString() const {
    switch(metodo) {
        case MetodoPago::EFECTIVO: return "Efectivo";
        case MetodoPago::TARJETA_CREDITO: return "Tarjeta de Credito";
        case MetodoPago::TARJETA_DEBITO: return "Tarjeta de Debito";
        case MetodoPago::TRANSFERENCIA: return "Transferencia";
        case MetodoPago::PAYPAL: return "PayPal";
        default: return "Desconocido";
    }
}

std::string Pago::getEstadoString() const {
    switch(estado) {
        case EstadoPago::PENDIENTE: return "Pendiente";
        case EstadoPago::COMPLETADO: return "Completado";
        case EstadoPago::RECHAZADO: return "Rechazado";
        case EstadoPago::REEMBOLSADO: return "Reembolsado";
        default: return "Desconocido";
    }
}

void Pago::procesarPago() {
    if (estado == EstadoPago::PENDIENTE) {
        estado = EstadoPago::COMPLETADO;
    }
}

void Pago::rechazarPago() {
    if (estado == EstadoPago::PENDIENTE) {
        estado = EstadoPago::RECHAZADO;
    }
}

void Pago::reembolsarPago() {
    if (estado == EstadoPago::COMPLETADO) {
        estado = EstadoPago::REEMBOLSADO;
    }
}

bool Pago::estaCompletado() const {
    return estado == EstadoPago::COMPLETADO;
}

void Pago::mostrarInfo() const {
    std::cout << "=== INFORMACION DE PAGO ===\n";
    std::cout << "ID Pago: #" << idPago << "\n";
    std::cout << "Reserva: #" << reserva->getIdReserva() << "\n";
    std::cout << "Monto: $" << std::fixed << std::setprecision(2) << monto << "\n";
    std::cout << "Metodo: " << getMetodoString() << "\n";
    std::cout << "Estado: " << getEstadoString() << "\n";
    std::cout << "Fecha: " << fechaPago << "\n";
    std::cout << "Transaccion: " << numeroTransaccion << "\n";
}