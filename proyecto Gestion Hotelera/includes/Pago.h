#ifndef PAGO_H
#define PAGO_H

#include "Reservation.h"
#include <string>
#include<vector>

enum class MetodoPago {
    EFECTIVO,
    TARJETA_CREDITO,
    TARJETA_DEBITO,
    TRANSFERENCIA,
    PAYPAL
};

enum class EstadoPago {
    PENDIENTE,
    COMPLETADO,
    RECHAZADO,
    REEMBOLSADO
};

class Pago {
private:
    int idPago;
    Reservation* reserva;
    double monto;
    MetodoPago metodo;
    EstadoPago estado;
    std::string fechaPago;  // Formato: "15/06/2024 14:30"
    std::string numeroTransaccion;
    static int contadorPagos;
    
public:
    Pago(Reservation* reserva, double monto, MetodoPago metodo, 
         std::string numeroTransaccion = "");
    
    // Getters
    int getIdPago() const;
    Reservation* getReserva() const;
    double getMonto() const;
    MetodoPago getMetodo() const;
    std::string getMetodoString() const;
    EstadoPago getEstado() const;
    std::string getEstadoString() const;
    std::string getFechaPago() const;
    std::string getNumeroTransaccion() const;
    
    // Metodos
    void procesarPago();
    void rechazarPago();
    void reembolsarPago();
    bool estaCompletado() const;
    void mostrarInfo() const;
};

#endif