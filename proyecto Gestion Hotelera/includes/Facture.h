#ifndef FACTURE_H
#define FACTURE_H

#include "Reservation.h"
#include "Pago.h"
#include <vector>
#include <string>

class Facture {
private:
    int idFactura;
    Reservation* reserva;
    std::vector<Pago*> pagos;
    std::string fechaEmision;  // Formato: "15/06/2024"
    double subtotal;
    double impuestos;
    double total;
    bool pagada;
    static int contadorFacturas;
    
public:
    Facture(Reservation* reserva);
    
    // Getters
    int getIdFactura() const;
    Reservation* getReserva() const;
    std::vector<Pago*> getPagos() const;
    std::string getFechaEmision() const;
    double getSubtotal() const;
    double getImpuestos() const;
    double getTotal() const;
    bool getPagada() const;
    double getSaldoPendiente() const;
    
    // Métodos
    void agregarPago(Pago* pago);
    void calcularTotales();
    void imprimirFactura() const;
    std::string generarDetalle() const;
};

#endif