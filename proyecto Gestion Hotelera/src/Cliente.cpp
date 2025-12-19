#include "Cliente.h"
#include "FileManager.h"
#include <iostream>
#include <sstream>
#include <vector>

Cliente::Cliente(int id, std::string nombre, std::string apellido, 
                 std::string dni, std::string telefono)
    : id(id), nombre(nombre), apellido(apellido), dni(dni), 
          telefono(telefono) {}

int Cliente::getId() const { return id; }
std::string Cliente::getNombre() const { return nombre; }
std::string Cliente::getApellido() const { return apellido; }
std::string Cliente::getDni() const { return dni; }
std::string Cliente::getTelefono() const { return telefono; }

std::string Cliente::getNombreCompleto() const {
    return nombre + " " + apellido;
}
void Cliente::setTelefono(std::string nuevoTelefono) { telefono = nuevoTelefono; }

void Cliente::mostrarInfo() const {
    std::cout << "=== INFORMACION DEL CLIENTE ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Nombre: " << getNombreCompleto() << "\n";
    std::cout << "DNI: " << dni << "\n";
    std::cout << "Telefono: " << telefono << "\n";
}
#include "FileManager.h"
#include <sstream>
#include <vector>

// ... código existente ...

// Convertir a formato CSV
std::string Cliente::toCSV() const {
    std::stringstream ss;
    ss << id << ","
       << nombre << ","
       << apellido << ","
       << dni << ","
       << telefono;
    return ss.str();
}

// Crear desde CSV
Cliente Cliente::fromCSV(const std::string& csv) {
    std::stringstream ss(csv);
    std::string item;
    std::vector<std::string> elementos;
    
    while (std::getline(ss, item, ',')) {
        elementos.push_back(item);
    }
    
    if (elementos.size() >= 7) {
        int id = std::stoi(elementos[0]);
        // Formato antiguo: id,nombre,apellido,dni,email,telefono,direccion
        return Cliente(id, elementos[1], elementos[2], elementos[3], elementos[5]);
    }
    if (elementos.size() >= 5) {
        int id = std::stoi(elementos[0]);
        // Formato nuevo: id,nombre,apellido,dni,telefono
        return Cliente(id, elementos[1], elementos[2], elementos[3], elementos[4]);
    }
    
    // Retornar cliente vacio si hay error
    return Cliente(0, "", "", "", "");
}

// Guardar en archivo individual
void Cliente::guardarEnArchivo() const {
    // Crear directorio de datos si no existe
    FileManager::crearDirectorio("data");
    FileManager::crearDirectorio("data/clientes");
    
    // Guardar como archivo individual
    std::string archivo = "data/clientes/cliente_" + std::to_string(id) + ".txt";
    std::string contenido = toCSV();
    FileManager::guardarTexto(archivo, contenido);
    
    // También agregar a archivo maestro
    std::string archivoMaestro = "data/clientes.txt";
    std::ofstream file(archivoMaestro, std::ios::app); // Append mode
    if (file.is_open()) {
        file << toCSV() << "\n";
        file.close();
    }
}

// Cargar todos los clientes
std::vector<Cliente> Cliente::cargarClientes() {
    std::vector<Cliente> clientes;
    std::string archivo = "data/clientes.txt";
    
    if (FileManager::existeArchivo(archivo)) {
        std::ifstream file(archivo);
        std::string linea;
        
        while (std::getline(file, linea)) {
            if (!linea.empty()) {
                Cliente cliente = fromCSV(linea);
                if (cliente.getId() != 0) { // Verificar que no sea vacío
                    clientes.push_back(cliente);
                }
            }
        }
        file.close();
    }
    
    return clientes;
}