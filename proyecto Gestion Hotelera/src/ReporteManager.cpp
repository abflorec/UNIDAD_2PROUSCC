#include "ReporteManager.h"
#include "FileManager.h"
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

void ReporteManager::generarReportesCompletos(
    const vector<Cliente>& clientes,
    const vector<Room>& habitaciones,
    const vector<Reservation>& reservas,
    const vector<Pago>& pagos,
    const vector<Facture>& facturas,
    const vector<Servicio>& servicios,
    const vector<Empleado>& empleados) {
    
    // Crear directorio de reportes
    string fecha = FileManager::obtenerFechaActual();
    string hora = FileManager::obtenerHoraActual();
    string carpetaReportes = "reportes/reporte_" + fecha + "_" + hora;
    
    FileManager::crearDirectorio("reportes");
    FileManager::crearDirectorio(carpetaReportes.c_str());
    
    cout << "\nGenerando reportes en: " << carpetaReportes << "\n";
    
    // Generar todos los reportes
    generarReporteClientes(clientes);
    generarReporteHabitaciones(habitaciones);
    generarReporteReservas(reservas);
    generarReportePagos(pagos);
    generarReporteFacturas(facturas);
    generarReporteServicios(servicios);
    generarReporteEmpleados(empleados);
    generarReporteConsolidado(clientes, reservas, pagos);
    
    cout << " Reportes generados exitosamente!\n";
}

string ReporteManager::generarCabeceraReporte(const string& titulo) {
    stringstream ss;
    ss << "<!DOCTYPE html>\n"
       << "<html>\n"
       << "<head>\n"
       << "    <meta charset='UTF-8'>\n"
       << "    <title>" << titulo << "</title>\n"
       << "    <style>\n"
       << "        body { font-family: Arial, sans-serif; margin: 40px; }\n"
       << "        h1 { color: #2c3e50; border-bottom: 3px solid #3498db; padding-bottom: 10px; }\n"
       << "        table { width: 100%; border-collapse: collapse; margin-top: 20px; }\n"
       << "        th { background-color: #3498db; color: white; padding: 12px; text-align: left; }\n"
       << "        td { padding: 10px; border-bottom: 1px solid #ddd; }\n"
       << "        tr:hover { background-color: #f5f5f5; }\n"
       << "        .total { font-weight: bold; color: #e74c3c; }\n"
       << "        .resaltado { background-color: #fffacd; }\n"
       << "        .footer { margin-top: 30px; color: #7f8c8d; font-size: 12px; }\n"
       << "        .estadistica { display: inline-block; margin: 10px; padding: 15px; background: #f8f9fa; border-radius: 5px; }\n"
       << "    </style>\n"
       << "</head>\n"
       << "<body>\n"
       << "    <h1>" << titulo << "</h1>\n"
       << "    <p>Fecha de generacion: " << FileManager::obtenerFechaActual() 
       << " " << FileManager::obtenerHoraActual() << "</p>\n";
    return ss.str();
}

string ReporteManager::generarPieReporte() {
    return "\n    <div class='footer'>\n"
           "        Reporte generado automaticamente por Sistema de Gestion Hotelera\n"
           "    </div>\n"
           "</body>\n"
           "</html>";
}

void ReporteManager::generarReporteClientes(const vector<Cliente>& clientes) {
    string fecha = FileManager::obtenerFechaActual();
    string hora = FileManager::obtenerHoraActual();
    string carpeta = "reportes/reporte_" + fecha + "_" + hora;
    
    ofstream file(carpeta + "/reporte_clientes.html");
    file << generarCabeceraReporte("Reporte de Clientes");
    file << "    <h2>Total de Clientes: " << clientes.size() << "</h2>\n"
         << "    <table>\n"
         << "        <tr>\n"
         << "            <th>ID</th>\n"
         << "            <th>Nombre Completo</th>\n"
         << "            <th>DNI</th>\n"
         << "            <th>Teléfono</th>\n"
         << "        </tr>\n";
    
    for (const auto& cliente : clientes) {
        file << "        <tr>\n"
             << "            <td>" << cliente.getId() << "</td>\n"
             << "            <td>" << cliente.getNombre() << " " << cliente.getApellido() << "</td>\n"
             << "            <td>" << cliente.getDni() << "</td>\n"
             << "            <td>" << cliente.getTelefono() << "</td>\n"
             << "        </tr>\n";
    }
    
    file << "    </table>\n" << generarPieReporte();
    file.close();
    
    // También guardar como CSV
    ofstream csv(carpeta + "/clientes.csv");
    csv << "ID,Nombre,Apellido,DNI,Telefono\n";
    for (const auto& cliente : clientes) {
        csv << cliente.getId() << ","
            << cliente.getNombre() << ","
            << cliente.getApellido() << ","
            << cliente.getDni() << ","
            << cliente.getTelefono() << ",";
    }
    csv.close();
}

void ReporteManager::generarReporteHabitaciones(const vector<Room>& habitaciones) {
    string fecha = FileManager::obtenerFechaActual();
    string hora = FileManager::obtenerHoraActual();
    string carpeta = "reportes/reporte_" + fecha + "_" + hora;
    
    ofstream file(carpeta + "/reporte_habitaciones.html");
    file << generarCabeceraReporte("Reporte de Habitaciones");
    file << "    <h2>Total de Habitaciones: " << habitaciones.size() << "</h2>\n"
         << "    <table>\n"
         << "        <tr>\n"
         << "            <th>Numero</th>\n"
         << "            <th>Tipo</th>\n"
         << "            <th>Estado</th>\n"
         << "            <th>Precio/Noche</th>\n"
         << "            <th>Capacidad</th>\n"
         << "            <th>Vista</th>\n"
         << "            <th>Características</th>\n"
         << "        </tr>\n";
    
    for (const auto& habitacion : habitaciones) {
        file << "        <tr>\n"
             << "            <td>" << habitacion.getNumero() << "</td>\n"
             << "            <td>" << habitacion.getTipoString() << "</td>\n"
             << "            <td>" << habitacion.getEstadoString() << "</td>\n"
             << "            <td>$" << fixed << setprecision(2) << habitacion.getPrecioNoche() << "</td>\n"
             << "            <td>" << habitacion.getCapacidad() << " personas</td>\n"
             << "            <td>" << (habitacion.getTieneVista() ? "Si" : "No") << "</td>\n"
             << "            <td>" << habitacion.getCaracteristicas() << "</td>\n"
             << "        </tr>\n";
    }
    
    file << "    </table>\n" << generarPieReporte();
    file.close();
}

void ReporteManager::generarReporteReservas(const vector<Reservation>& reservas) {
    string fecha = FileManager::obtenerFechaActual();
    string hora = FileManager::obtenerHoraActual();
    string carpeta = "reportes/reporte_" + fecha + "_" + hora;
    
    ofstream file(carpeta + "/reporte_reservas.html");
    file << generarCabeceraReporte("Reporte de Reservas");
    file << "    <h2>Total de Reservas: " << reservas.size() << "</h2>\n"
         << "    <table>\n"
         << "        <tr>\n"
         << "            <th>ID Reserva</th>\n"
         << "            <th>Cliente</th>\n"
         << "            <th>Habitación</th>\n"
         << "            <th>Check-In</th>\n"
         << "            <th>Check-Out</th>\n"
         << "            <th>Noches</th>\n"
         << "            <th>Total</th>\n"
         << "            <th>Estado</th>\n"
         << "        </tr>\n";
    
    double totalIngresos = 0.0;
    int reservasActivas = 0;
    int reservasCompletadas = 0;
    
    for (const auto& reserva : reservas) {
        double costo = reserva.getCostoTotal();
        totalIngresos += costo;
        
        string estado;
        if (!reserva.getCheckInRealizado()) {
            estado = "Pendiente";
        } else if (!reserva.getCheckOutRealizado()) {
            estado = "Activa";
            reservasActivas++;
        } else {
            estado = "Completada";
            reservasCompletadas++;
        }
        
        file << "        <tr>\n"
             << "            <td>" << reserva.getIdReserva() << "</td>\n"
             << "            <td>" << reserva.getCliente()->getNombreCompleto() << "</td>\n"
             << "            <td>" << reserva.getHabitacion()->getNumero() << "</td>\n"
             << "            <td>" << reserva.getFechaCheckIn() << "</td>\n"
             << "            <td>" << reserva.getFechaCheckOut() << "</td>\n"
             << "            <td>" << reserva.getNumNoches() << "</td>\n"
             << "            <td>$" << fixed << setprecision(2) << costo << "</td>\n"
             << "            <td>" << estado << "</td>\n"
             << "        </tr>\n";
    }
    
    file << "    </table>\n"
         << "    <h3>Estadísticas:</h3>\n"
         << "    <div class='estadistica'>Reservas Activas: " << reservasActivas << "</div>\n"
         << "    <div class='estadistica'>Reservas Completadas: " << reservasCompletadas << "</div>\n"
         << "    <div class='estadistica'>Reservas Pendientes: " << (reservas.size() - reservasActivas - reservasCompletadas) << "</div>\n"
         << "    <h3 class='total'>Total Ingresos por Reservas: $" 
         << fixed << setprecision(2) << totalIngresos << "</h3>\n"
         << generarPieReporte();
    file.close();
}

void ReporteManager::generarReportePagos(const vector<Pago>& pagos) {
    string fecha = FileManager::obtenerFechaActual();
    string hora = FileManager::obtenerHoraActual();
    string carpeta = "reportes/reporte_" + fecha + "_" + hora;
    
    ofstream file(carpeta + "/reporte_pagos.html");
    file << generarCabeceraReporte("Reporte de Pagos");
    file << "    <h2>Total de Pagos: " << pagos.size() << "</h2>\n"
         << "    <table>\n"
         << "        <tr>\n"
         << "            <th>ID Pago</th>\n"
         << "            <th>Reserva</th>\n"
         << "            <th>Monto</th>\n"
         << "            <th>Metodo</th>\n"
         << "            <th>Estado</th>\n"
         << "            <th>Fecha</th>\n"
         << "            <th>Transacción</th>\n"
         << "        </tr>\n";
    
    double totalRecaudado = 0.0;
    double totalPendiente = 0.0;
    double totalReembolsado = 0.0;
    
    for (const auto& pago : pagos) {
        if (pago.estaCompletado()) {
            totalRecaudado += pago.getMonto();
        } else if (pago.getEstadoString() == "Pendiente") {
            totalPendiente += pago.getMonto();
        } else if (pago.getEstadoString() == "Reembolsado") {
            totalReembolsado += pago.getMonto();
        }
        
        file << "        <tr>\n"
             << "            <td>" << pago.getIdPago() << "</td>\n"
             << "            <td>#" << pago.getReserva()->getIdReserva() << "</td>\n"
             << "            <td>$" << fixed << setprecision(2) << pago.getMonto() << "</td>\n"
             << "            <td>" << pago.getMetodoString() << "</td>\n"
             << "            <td>" << pago.getEstadoString() << "</td>\n"
             << "            <td>" << pago.getFechaPago() << "</td>\n"
             << "            <td>" << pago.getNumeroTransaccion() << "</td>\n"
             << "        </tr>\n";
    }
    
    file << "    </table>\n"
         << "    <h3>Resumen Financiero:</h3>\n"
         << "    <div class='estadistica'>Total Recaudado: $" << fixed << setprecision(2) << totalRecaudado << "</div>\n"
         << "    <div class='estadistica'>Pendiente: $" << fixed << setprecision(2) << totalPendiente << "</div>\n"
         << "    <div class='estadistica'>Reembolsado: $" << fixed << setprecision(2) << totalReembolsado << "</div>\n"
         << generarPieReporte();
    file.close();
}

void ReporteManager::generarReporteFacturas(const vector<Facture>& facturas) {
    string fecha = FileManager::obtenerFechaActual();
    string hora = FileManager::obtenerHoraActual();
    string carpeta = "reportes/reporte_" + fecha + "_" + hora;
    
    ofstream file(carpeta + "/reporte_facturas.html");
    file << generarCabeceraReporte("Reporte de Facturas");
    file << "    <h2>Total de Facturas: " << facturas.size() << "</h2>\n"
         << "    <table>\n"
         << "        <tr>\n"
         << "            <th>ID Factura</th>\n"
         << "            <th>Reserva</th>\n"
         << "            <th>Cliente</th>\n"
         << "            <th>Subtotal</th>\n"
         << "            <th>Impuestos</th>\n"
         << "            <th>Total</th>\n"
         << "            <th>Pagada</th>\n"
         << "            <th>Saldo Pendiente</th>\n"
         << "        </tr>\n";
    
    double totalFacturado = 0.0;
    double totalImpuestos = 0.0;
    double totalSaldoPendiente = 0.0;
    int facturasPagadas = 0;
    
    for (const auto& factura : facturas) {
        totalFacturado += factura.getTotal();
        totalImpuestos += factura.getImpuestos();
        double saldo = factura.getSaldoPendiente();
        totalSaldoPendiente += saldo;
        
        if (factura.getPagada()) {
            facturasPagadas++;
        }
        
        file << "        <tr>\n"
             << "            <td>" << factura.getIdFactura() << "</td>\n"
             << "            <td>#" << factura.getReserva()->getIdReserva() << "</td>\n"
             << "            <td>" << factura.getReserva()->getCliente()->getNombreCompleto() << "</td>\n"
             << "            <td>$" << fixed << setprecision(2) << factura.getSubtotal() << "</td>\n"
             << "            <td>$" << fixed << setprecision(2) << factura.getImpuestos() << "</td>\n"
             << "            <td>$" << fixed << setprecision(2) << factura.getTotal() << "</td>\n"
             << "            <td>" << (factura.getPagada() ? "Si" : "No") << "</td>\n"
             << "            <td>$" << fixed << setprecision(2) << saldo << "</td>\n"
             << "        </tr>\n";
    }
    
    file << "    </table>\n"
         << "    <h3>Resumen de Facturación:</h3>\n"
         << "    <div class='estadistica'>Total Ganancias: $" << fixed << setprecision(2) << totalFacturado << "</div>\n"
         << "    <div class='estadistica'>Total Impuestos: $" << fixed << setprecision(2) << totalImpuestos << "</div>\n"
         << "    <div class='estadistica'>Saldo Pendiente: $" << fixed << setprecision(2) << totalSaldoPendiente << "</div>\n"
         << "    <div class='estadistica'>Facturas Pagadas: " << facturasPagadas << "/" << facturas.size() << "</div>\n"
         << generarPieReporte();
    file.close();
}

void ReporteManager::generarReporteServicios(const vector<Servicio>& servicios) {
    string fecha = FileManager::obtenerFechaActual();
    string hora = FileManager::obtenerHoraActual();
    string carpeta = "reportes/reporte_" + fecha + "_" + hora;
    
    ofstream file(carpeta + "/reporte_servicios.html");
    file << generarCabeceraReporte("Reporte de Servicios");
    file << "    <h2>Total de Servicios: " << servicios.size() << "</h2>\n"
         << "    <table>\n"
         << "        <tr>\n"
         << "            <th>ID</th>\n"
         << "            <th>Nombre</th>\n"
         << "            <th>Tipo</th>\n"
         << "            <th>Descripcion</th>\n"
         << "            <th>Precio</th>\n"
         << "            <th>Disponible</th>\n"
         << "        </tr>\n";
    
    for (const auto& servicio : servicios) {
        file << "        <tr>\n"
             << "            <td>" << servicio.getIdServicio() << "</td>\n"
             << "            <td>" << servicio.getNombre() << "</td>\n"
             << "            <td>" << servicio.getTipoString() << "</td>\n"
             << "            <td>" << servicio.getDescripcion() << "</td>\n"
             << "            <td>$" << fixed << setprecision(2) << servicio.getPrecio() << "</td>\n"
             << "            <td>" << (servicio.getDisponible() ? "Si" : "No") << "</td>\n"
             << "        </tr>\n";
    }
    
    file << "    </table>\n" << generarPieReporte();
    file.close();
}

void ReporteManager::generarReporteEmpleados(const vector<Empleado>& empleados) {
    string fecha = FileManager::obtenerFechaActual();
    string hora = FileManager::obtenerHoraActual();
    string carpeta = "reportes/reporte_" + fecha + "_" + hora;
    
    ofstream file(carpeta + "/reporte_empleados.html");
    file << generarCabeceraReporte("Reporte de Empleados");
    file << "    <h2>Total de Empleados: " << empleados.size() << "</h2>\n"
         << "    <table>\n"
         << "        <tr>\n"
         << "            <th>ID</th>\n"
         << "            <th>Nombre Completo</th>\n"
         << "            <th>DNI</th>\n"
         << "            <th>Cargo</th>\n"
         << "            <th>Telefono</th>\n"
         << "            <th>Salario</th>\n"
         << "            <th>Antigüedad</th>\n"
         << "            <th>Estado</th>\n"
         << "        </tr>\n";
    
    double totalSalarios = 0.0;
    int empleadosActivos = 0;
    
    for (const auto& empleado : empleados) {
        totalSalarios += empleado.getSalario();
        if (empleado.getActivo()) {
            empleadosActivos++;
        }
        
        file << "        <tr>\n"
             << "            <td>" << empleado.getIdEmpleado() << "</td>\n"
             << "            <td>" << empleado.getNombreCompleto() << "</td>\n"
             << "            <td>" << empleado.getDni() << "</td>\n"
             << "            <td>" << empleado.getCargoString() << "</td>\n"
             << "            <td>" << empleado.getTelefono() << "</td>\n"
             << "            <td>-</td>\n"
             << "            <td>$" << fixed << setprecision(2) << empleado.getSalario() << "</td>\n"
             << "            <td>" << empleado.calcularAntiguedad() << " años</td>\n"
             << "            <td>" << (empleado.getActivo() ? "Activo" : "Inactivo") << "</td>\n"
             << "        </tr>\n";
    }
    
    file << "    </table>\n"
         << "    <h3>Resumen de Personal:</h3>\n"
         << "    <div class='estadistica'>Empleados Activos: " << empleadosActivos << "</div>\n"
         << "    <div class='estadistica'>Total Salarios: $" << fixed << setprecision(2) << totalSalarios << "/mes</div>\n"
         << "    <div class='estadistica'>Salario Promedio: $" << fixed << setprecision(2) 
         << (empleados.empty() ? 0 : totalSalarios / empleados.size()) << "/mes</div>\n"
         << generarPieReporte();
    file.close();
}

void ReporteManager::generarReporteConsolidado(
    const vector<Cliente>& clientes,
    const vector<Reservation>& reservas,
    const vector<Pago>& pagos) {
    
    string fecha = FileManager::obtenerFechaActual();
    string hora = FileManager::obtenerHoraActual();
    string carpeta = "reportes/reporte_" + fecha + "_" + hora;
    
    ofstream file(carpeta + "/reporte_consolidado.html");
    file << generarCabeceraReporte("Reporte Consolidado del Sistema");
    
    // Estadisticas
    int totalClientes = clientes.size();
    int totalReservas = reservas.size();
    int totalPagos = pagos.size();
    
    double totalRecaudado = 0.0;
    for (const auto& pago : pagos) {
        if (pago.estaCompletado()) {
            totalRecaudado += pago.getMonto();
        }
    }
    
    // Calcular ocupacion
    int reservasActivas = 0;
    for (const auto& reserva : reservas) {
        if (reserva.estaActiva()) {
            reservasActivas++;
        }
    }
    
    file << "    <div style='display: flex; flex-wrap: wrap; justify-content: space-around; margin: 30px 0;'>\n"
         << "        <div style='background-color: #3498db; color: white; padding: 20px; border-radius: 10px; width: 200px; text-align: center; margin: 10px;'>\n"
         << "            <h3>Clientes</h3>\n"
         << "            <h1>" << totalClientes << "</h1>\n"
         << "        </div>\n"
         << "        <div style='background-color: #2ecc71; color: white; padding: 20px; border-radius: 10px; width: 200px; text-align: center; margin: 10px;'>\n"
         << "            <h3>Reservas</h3>\n"
         << "            <h1>" << totalReservas << "</h1>\n"
         << "        </div>\n"
         << "        <div style='background-color: #e74c3c; color: white; padding: 20px; border-radius: 10px; width: 200px; text-align: center; margin: 10px;'>\n"
         << "            <h3>Recaudado</h3>\n"
         << "            <h1>$" << fixed << setprecision(2) << totalRecaudado << "</h1>\n"
         << "        </div>\n"
         << "        <div style='background-color: #9b59b6; color: white; padding: 20px; border-radius: 10px; width: 200px; text-align: center; margin: 10px;'>\n"
         << "            <h3>Reservas Activas</h3>\n"
         << "            <h1>" << reservasActivas << "</h1>\n"
         << "        </div>\n"
         << "        <div style='background-color: #f39c12; color: white; padding: 20px; border-radius: 10px; width: 200px; text-align: center; margin: 10px;'>\n"
         << "            <h3>Pagos</h3>\n"
         << "            <h1>" << totalPagos << "</h1>\n"
         << "        </div>\n"
         << "    </div>\n";
    
    // Gráfico de distribución (simulado con HTML)
    file << "    <h3>Distribucion de Reservas por Estado:</h3>\n"
         << "    <div style='background-color: #ecf0f1; padding: 10px; border-radius: 5px; margin: 20px 0;'>\n"
         << "        <div style='background-color: #2ecc71; width: "
         << (totalReservas > 0 ? (reservasActivas * 100 / totalReservas) : 0)
         << "%; height: 30px; border-radius: 5px; text-align: center; color: white; line-height: 30px;'>\n"
         << "            Activas: " << reservasActivas << "\n"
         << "        </div>\n"
         << "    </div>\n";
    
    file << generarPieReporte();
    file.close();
    
    // Crear archivo README con resumen
    ofstream readme(carpeta + "/README.txt");
    readme << "REPORTE DEL SISTEMA DE GESTION HOTELERA\n"
           << "========================================\n"
           << "Fecha: " << fecha << "\n"
           << "Hora: " << hora << "\n"
           << "\n"
           << "RESUMEN ESTADISTICO:\n"
           << "--------------------\n"
           << "Total Clientes: " << totalClientes << "\n"
           << "Total Reservas: " << totalReservas << "\n"
           << "Total Pagos: " << totalPagos << "\n"
           << "Total Recaudado: $" << fixed << setprecision(2) << totalRecaudado << "\n"
           << "\n"
           << "ARCHIVOS GENERADOS:\n"
           << "-------------------\n"
           << "1. reporte_clientes.html - Listado completo de clientes\n"
           << "2. reporte_habitaciones.html - Estado de habitaciones\n"
           << "3. reporte_reservas.html - Reservas activas y completadas\n"
           << "4. reporte_pagos.html - Estado financiero de pagos\n"
           << "5. reporte_facturas.html - Facturas emitidas\n"
           << "6. reporte_servicios.html - Servicios disponibles\n"
           << "7. reporte_empleados.html - Personal del hotel\n"
           << "8. reporte_consolidado.html - Vista general del sistema\n"
           << "9. clientes.csv - Datos de clientes en formato CSV\n"
           << "\n"
           << "Para abrir los reportes, simplemente haga doble clic en los archivos .html\n";
    readme.close();
}