#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include<vector>

class Cliente {
private:
    int id;
    std::string nombre;
    std::string apellido;
    std::string dni;
    std::string telefono;
    
public:
    Cliente(int id, std::string nombre, std::string apellido, 
            std::string dni, std::string telefono);
    
    // Getters
    int getId() const;
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getDni() const;
    std::string getTelefono() const;
    std::string getNombreCompleto() const;
    
    // Setters
    void setTelefono(std::string nuevoTelefono);
    
    void mostrarInfo() const;
    std::string toCSV() const;  // Convertir a formato CSV
    static Cliente fromCSV(const std::string& csv);  // Crear desde CSV
    void guardarEnArchivo() const;  // Guardar en archivo individual
    static std::vector<Cliente> cargarClientes();  // Cargar todos los clientes
};

#endif