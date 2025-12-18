#include "Facture.h"
#include <iostream>
#include <iomanip>

int Facture::contadorFacturas = 3000;

Facture::Facture(Reservation* reserva)
    : idFactura(++contadorFacturas), reserva(reserva), 
      fechaEmision("15/06/2024"), subtotal(0.0), impuestos(0.0), total(0.0), pagada(false) {
    
    calcularTotales();
}

int Facture::getIdFactura() const { return idFactura; }
Reservation* Facture::getReserva() const { return reserva; }
std::vector<Pago*> Facture::getPagos() const { return pagos; }
std::string Facture::getFechaEmision() const { return fechaEmision; }
double Facture::getSubtotal() const { return subtotal; }
double Facture::getImpuestos() const { return impuestos; }
double Facture::getTotal() const { return total; }
bool Facture::getPagada() const { return pagada; }

double Facture::getSaldoPendiente() const {
    double pagado = 0.0;
    for (const auto& pago : pagos) {
        if (pago->estaCompletado()) {
            pagado += pago->getMonto();
        }
    }
    return total - pagado;
}

void Facture::agregarPago(Pago* pago) {
    pagos.push_back(pago);
    
    double pagado = 0.0;
    for (const auto& p : pagos) {
        if (p->estaCompletado()) {
            pagado += p->getMonto();
        }
    }
    
    if (pagado >= total) {
        pagada = true;
    }
}

void Facture::calcularTotales() {
    subtotal = reserva->getCostoTotal();
    impuestos = subtotal * 0.10; // 10% de impuestos
    total = subtotal + impuestos;
}

void Facture::imprimirFactura() const {
    std::cout << "========================================\n";
    std::cout << "           FACTURA HOTELERA            \n";
    std::cout << "========================================\n";
    std::cout << "Factura #: " << idFactura << "\n";
    std::cout << "Fecha: " << fechaEmision << "\n";
    std::cout << "Cliente: " << reserva->getCliente()->getNombreCompleto() << "\n";
    std::cout << "DNI: " << reserva->getCliente()->getDni() << "\n";
    std::cout << "Reserva #: " << reserva->getIdReserva() << "\n";
    std::cout << "----------------------------------------\n";
    std::cout << "CONCEPTO:\n";
    std::cout << "  Habitacion " << reserva->getHabitacion()->getNumero();
    std::cout << " (" << reserva->getNumNoches() << " noches)\n";
    std::cout << "  @ $" << std::fixed << std::setprecision(2) 
              << reserva->getHabitacion()->getPrecioNoche() << "/noche\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Subtotal: $" << std::setw(10) << subtotal << "\n";
    std::cout << "Impuestos: $" << std::setw(9) << impuestos << "\n";
    std::cout << "TOTAL: $" << std::setw(13) << total << "\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Estado: " << (pagada ? "PAGADA" : "PENDIENTE") << "\n";
    
    if (!pagos.empty()) {
        std::cout << "\nPAGOS REALIZADOS:\n";
        for (const auto& pago : pagos) {
            std::cout << "  - " << pago->getMetodoString() << ": $" 
                      << pago->getMonto() << " (" << pago->getEstadoString() << ")\n";
        }
        std::cout << "Saldo pendiente: $" << getSaldoPendiente() << "\n";
    }
    std::cout << "========================================\n";
}

std::string Facture::generarDetalle() const {
    return "Factura #" + std::to_string(idFactura) + " - Cliente: " + 
           reserva->getCliente()->getNombreCompleto() + " - Total: $" + 
           std::to_string(total);
}