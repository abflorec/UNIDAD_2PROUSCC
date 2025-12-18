#include <iostream>
#include <vector>
#include "includes/Cliente.h"
#include "includes/Room.h"
#include "includes/Reservation.h"
#include "includes/Pago.h"
#include "includes/Facture.h"
#include "includes/Servicio.h"
#include "includes/Empleado.h"
#include "includes/FileManager.h"
#include "includes/ReporteManager.h"

using namespace std;

// Vectores globales para almacenar datos
vector<Cliente> clientes;
vector<Room> habitaciones;
vector<Reservation*> reservas;  // Usamos punteros por las relaciones
vector<Pago*> pagos;
vector<Facture*> facturas;
vector<Servicio> servicios;
vector<Empleado> empleados;

void mostrarMenu() {
    cout << "\n=== SISTEMA DE GESTION HOTELERA ===\n";
    cout << "1. Agregar Cliente\n";
    cout << "2. Agregar Habitacion\n";
    cout << "3. Crear Reserva\n";
    cout << "4. Registrar Pago\n";
    cout << "5. Ver Todos los Datos\n";
    cout << "6. Guardar Datos en Archivos\n";
    cout << "7. Cargar Datos de Archivos\n";
    cout << "8. Generar Reportes\n";
    cout << "9. Salir\n";
    cout << "Seleccione una opcion: ";
}

void agregarCliente() {
    int id;
    string nombre, apellido, dni, telefono;
    
    cout << "\n--- AGREGAR NUEVO CLIENTE ---\n";
    cout << "ID: ";
    cin >> id;
    cin.ignore();
    
    cout << "Nombre: ";
    getline(cin, nombre);
    
    cout << "Apellido: ";
    getline(cin, apellido);
    
    cout << "DNI: ";
    getline(cin, dni);
    
    cout << "Telefono: ";
    getline(cin, telefono);
    
    Cliente nuevoCliente(id, nombre, apellido, dni, telefono);
    clientes.push_back(nuevoCliente);
    
    // Guardar automáticamente
    nuevoCliente.guardarEnArchivo();
    
    cout << "✅ Cliente agregado y guardado exitosamente!\n";
}

void agregarHabitacion() {
    int numero, capacidad;
    double precio;
    string caracteristicas;
    char tieneVista;
    
    cout << "\n--- AGREGAR NUEVA HABITACION ---\n";
    cout << "Numero: ";
    cin >> numero;
    
    cout << "Precio por noche: ";
    cin >> precio;
    
    cout << "Capacidad: ";
    cin >> capacidad;
    
    cout << "Tiene vista (s/n): ";
    cin >> tieneVista;
    
    cin.ignore();
    cout << "Caracteristicas: ";
    getline(cin, caracteristicas);
    
    Room nuevaHabitacion(numero, TipoHabitacion::DOBLE, precio, capacidad, 
                         (tieneVista == 's' || tieneVista == 'S'), caracteristicas);
    habitaciones.push_back(nuevaHabitacion);
    
    cout << "✅ Habitacion agregada exitosamente!\n";
}

void crearReserva() {
    if (clientes.empty() || habitaciones.empty()) {
        cout << "❌ Error: Necesita clientes y habitaciones primero.\n";
        return;
    }
    
    cout << "\n--- CREAR NUEVA RESERVA ---\n";
    
    // Mostrar clientes
    cout << "Clientes disponibles:\n";
    for (size_t i = 0; i < clientes.size(); i++) {
        cout << i+1 << ". " << clientes[i].getNombreCompleto() << " (ID: " << clientes[i].getId() << ")\n";
    }
    
    int clienteIdx;
    cout << "Seleccione cliente (numero): ";
    cin >> clienteIdx;
    clienteIdx--; // Ajustar a índice base 0
    
    if (clienteIdx < 0 || clienteIdx >= (int)clientes.size()) {
        cout << "❌ Seleccion invalida.\n";
        return;
    }
    
    // Mostrar habitaciones disponibles
    cout << "\nHabitaciones disponibles:\n";
    for (size_t i = 0; i < habitaciones.size(); i++) {
        if (habitaciones[i].estaDisponible()) {
            cout << i+1 << ". Habitacion " << habitaciones[i].getNumero() 
                 << " - $" << habitaciones[i].getPrecioNoche() << "/noche\n";
        }
    }
    
    int habitacionIdx;
    cout << "Seleccione habitacion (numero): ";
    cin >> habitacionIdx;
    habitacionIdx--;
    
    if (habitacionIdx < 0 || habitacionIdx >= (int)habitaciones.size() || 
        !habitaciones[habitacionIdx].estaDisponible()) {
        cout << "❌ Seleccion invalida o habitacion no disponible.\n";
        return;
    }
    
    string fechaIn, fechaOut;
    int personas;
    
    cout << "Fecha Check-in (DD/MM/AAAA): ";
    cin >> fechaIn;
    
    cout << "Fecha Check-out (DD/MM/AAAA): ";
    cin >> fechaOut;
    
    cout << "Numero de personas: ";
    cin >> personas;
    
    cin.ignore();
    string observaciones;
    cout << "Observaciones: ";
    getline(cin, observaciones);
    
    // Crear reserva
    Reservation* nuevaReserva = new Reservation(&clientes[clienteIdx], 
                                                &habitaciones[habitacionIdx],
                                                fechaIn, fechaOut, personas, observaciones);
    reservas.push_back(nuevaReserva);
    
    cout << "✅ Reserva creada exitosamente! ID: #" << nuevaReserva->getIdReserva() << "\n";
}

void registrarPago() {
    if (reservas.empty()) {
        cout << "❌ Error: No hay reservas para pagar.\n";
        return;
    }
    
    cout << "\n--- REGISTRAR PAGO ---\n";
    cout << "Reservas pendientes:\n";
    
    for (size_t i = 0; i < reservas.size(); i++) {
        cout << i+1 << ". Reserva #" << reservas[i]->getIdReserva() 
             << " - " << reservas[i]->getCliente()->getNombreCompleto()
             << " - Total: $" << reservas[i]->getCostoTotal() << "\n";
    }
    
    int reservaIdx;
    cout << "Seleccione reserva (numero): ";
    cin >> reservaIdx;
    reservaIdx--;
    
    if (reservaIdx < 0 || reservaIdx >= (int)reservas.size()) {
        cout << "❌ Seleccion invalida.\n";
        return;
    }
    
    cout << "Metodo de pago:\n";
    cout << "1. Efectivo\n";
    cout << "2. Tarjeta de Credito\n";
    cout << "3. Tarjeta de Debito\n";
    cout << "4. Transferencia\n";
    cout << "5. PayPal\n";
    
    int metodo;
    cout << "Seleccione metodo (1-5): ";
    cin >> metodo;
    
    MetodoPago metodoPago;
    switch(metodo) {
        case 1: metodoPago = MetodoPago::EFECTIVO; break;
        case 2: metodoPago = MetodoPago::TARJETA_CREDITO; break;
        case 3: metodoPago = MetodoPago::TARJETA_DEBITO; break;
        case 4: metodoPago = MetodoPago::TRANSFERENCIA; break;
        case 5: metodoPago = MetodoPago::PAYPAL; break;
        default: metodoPago = MetodoPago::EFECTIVO;
    }
    
    Pago* nuevoPago = new Pago(reservas[reservaIdx], 
                              reservas[reservaIdx]->getCostoTotal(), 
                              metodoPago);
    nuevoPago->procesarPago();
    pagos.push_back(nuevoPago);
    
    // Crear factura automáticamente
    Facture* nuevaFactura = new Facture(reservas[reservaIdx]);
    nuevaFactura->agregarPago(nuevoPago);
    nuevaFactura->calcularTotales();
    facturas.push_back(nuevaFactura);
    
    cout << "Pago registrado y factura generada!\n";
}

void verDatos() {
    cout << "\n=== DATOS DEL SISTEMA ===\n";
    
    cout << "\n CLIENTES (" << clientes.size() << "):\n";
    for (const auto& cliente : clientes) {
        cout << "  - " << cliente.getNombreCompleto() << " (ID: " << cliente.getId() << ")\n";
    }
    
    cout << "\nHABITACIONES (" << habitaciones.size() << "):\n";
    for (const auto& habitacion : habitaciones) {
        cout << "  - Habitacion " << habitacion.getNumero() 
             << " (" << habitacion.getEstadoString() << ") - $" 
             << habitacion.getPrecioNoche() << "/noche\n";
    }
    
    cout << "\n RESERVAS (" << reservas.size() << "):\n";
    for (const auto& reserva : reservas) {
        cout << "  - Reserva #" << reserva->getIdReserva()
             << " - " << reserva->getCliente()->getNombreCompleto()
             << " - Habitacion " << reserva->getHabitacion()->getNumero()
             << " - Total: $" << reserva->getCostoTotal() << "\n";
    }
    
    cout << "\n PAGOS (" << pagos.size() << "):\n";
    for (const auto& pago : pagos) {
        cout << "  - Pago #" << pago->getIdPago()
             << " - Reserva #" << pago->getReserva()->getIdReserva()
             << " - $" << pago->getMonto() 
             << " - Estado: " << pago->getEstadoString() << "\n";
    }
    
    cout << "\n FACTURAS (" << facturas.size() << "):\n";
    for (const auto& factura : facturas) {
        cout << "  - Factura #" << factura->getIdFactura()
             << " - Reserva #" << factura->getReserva()->getIdReserva()
             << " - Total: $" << factura->getTotal() << "\n";
    }
}

void guardarDatos() {
    cout << "\n GUARDANDO DATOS...\n";
    
    // Crear directorio data si no existe
    FileManager::crearDirectorio("data");
    
    // Guardar clientes
    for (const auto& cliente : clientes) {
        cliente.guardarEnArchivo();
    }
    
    // (Agregar aquí guardado para las otras clases)
    
    cout << " Datos guardados en carpeta 'data/'\n";
}

void cargarDatos() {
    cout << "\n CARGANDO DATOS...\n";
    
    // Cargar clientes
    clientes = Cliente::cargarClientes();
    
    cout << " Cargados " << clientes.size() << " clientes\n";
    // (Agregar aquí carga para las otras clases)
}

void generarReportes() {
    cout << "\n GENERANDO REPORTES...\n";
    
    // Convertir vectores de punteros a objetos para reportes
    vector<Reservation> reservasObjetos;
    for (auto r : reservas) {
        // Necesitaríamos un constructor de copia o método para obtener objeto
    }
    
    // Generar reportes completos
    ReporteManager::generarReportesCompletos(
        clientes,
        habitaciones,
        {}, // reservasObjetos - implementar conversión
        {}, // pagosObjetos
        {}, // facturasObjetos
        servicios,
        empleados);
}

int main() {
    // Cargar datos existentes al iniciar
    cargarDatos();
    
    // Datos de ejemplo si no hay datos cargados
    if (clientes.empty()) {
        clientes.push_back(Cliente(1, "Juan", "Perez", "12345678A", "555-1234"));
        clientes.push_back(Cliente(2, "Maria", "Gonzalez", "87654321B", "555-5678"));
    }
    
    if (habitaciones.empty()) {
        habitaciones.push_back(Room(101, TipoHabitacion::DOBLE, 120.50, 2, true, 
                                    "TV, Aire acondicionado, Mini-bar"));
        habitaciones.push_back(Room(102, TipoHabitacion::INDIVIDUAL, 80.00, 1, false, 
                                    "TV, WiFi"));
    }
    
    if (servicios.empty()) {
        servicios.push_back(Servicio(1, TipoServicio::SPA, "Masaje Relajante", 
                                     "Masaje de 60 minutos", 75.00));
        servicios.push_back(Servicio(2, TipoServicio::RESTAURANTE, "Desayuno Buffet", 
                                     "Desayuno completo buffet", 25.00));
    }
    
    if (empleados.empty()) {
        empleados.push_back(Empleado(1, "Carlos", "Rodríguez", "11223344C", 
                                     CargoEmpleado::RECEPCIONISTA, "555-9876",
                                     "carlos@hotel.com", 25000.00, "15/01/2020"));
    }
    
    // Menú principal
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                agregarCliente();
                break;
            case 2:
                agregarHabitacion();
                break;
            case 3:
                crearReserva();
                break;
            case 4:
                registrarPago();
                break;
            case 5:
                verDatos();
                break;
            case 6:
                guardarDatos();
                break;
            case 7:
                cargarDatos();
                break;
            case 8:
                generarReportes();
                break;
            case 9:
                cout << "\n Saliendo del sistema...\n";
                break;
            default:
                cout << " Opcion invalida. Intente de nuevo.\n";
        }
        
        // Pausa para ver resultados
        if (opcion != 9) {
            cout << "\nPresione Enter para continuar...";
            cin.get();
        }
        
    } while (opcion != 9);
    
    // Liberar memoria de punteros
    for (auto r : reservas) delete r;
    for (auto p : pagos) delete p;
    for (auto f : facturas) delete f;
    
    return 0;
}