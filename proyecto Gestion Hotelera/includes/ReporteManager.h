#ifndef REPORTEMANAGER_H
#define REPORTEMANAGER_H

#include "Cliente.h"
#include "Room.h"
#include "Reservation.h"
#include "Pago.h"
#include "Facture.h"
#include "Servicio.h"
#include "Empleado.h"
#include <vector>
#include <string>

class ReporteManager {
public:
    // Generar todos los reportes
    static void generarReportesCompletos(
        const std::vector<Cliente>& clientes,
        const std::vector<Room>& habitaciones,
        const std::vector<Reservation>& reservas,
        const std::vector<Pago>& pagos,
        const std::vector<Facture>& facturas,
        const std::vector<Servicio>& servicios,
        const std::vector<Empleado>& empleados);
    
    // Generar reporte individual
    static void generarReporteClientes(const std::vector<Cliente>& clientes);
    static void generarReporteHabitaciones(const std::vector<Room>& habitaciones);
    static void generarReporteReservas(const std::vector<Reservation>& reservas);
    static void generarReportePagos(const std::vector<Pago>& pagos);
    static void generarReporteFacturas(const std::vector<Facture>& facturas);
    static void generarReporteServicios(const std::vector<Servicio>& servicios);
    static void generarReporteEmpleados(const std::vector<Empleado>& empleados);
    
    // Generar reporte consolidado
    static void generarReporteConsolidado(
        const std::vector<Cliente>& clientes,
        const std::vector<Reservation>& reservas,
        const std::vector<Pago>& pagos);
    
private:
    static std::string generarCabeceraReporte(const std::string& titulo);
    static std::string generarPieReporte();
};

#endif