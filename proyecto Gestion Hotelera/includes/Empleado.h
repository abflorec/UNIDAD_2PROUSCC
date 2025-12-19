#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <string>
#include<vector>

enum class CargoEmpleado {
    RECEPCIONISTA,
    GERENTE,
    LIMPIEZA,
    SEGURIDAD,
    MANTENIMIENTO,
    CHEF,
    CAMARERO
};

class Empleado {
private:
    int idEmpleado;
    std::string nombre;
    std::string apellido;
    std::string dni;
    CargoEmpleado cargo;
    std::string telefono;
    double salario;
    bool activo;
    std::string fechaContratacion;  // Formato: "15/01/2020"
    int anioContratacion;
    
public:
    Empleado(int id, std::string nombre, std::string apellido, 
             std::string dni, CargoEmpleado cargo, std::string telefono,
             double salario, std::string fechaContratacion);
    
    // Getters
    int getIdEmpleado() const;
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getNombreCompleto() const;
    std::string getDni() const;
    CargoEmpleado getCargo() const;
    std::string getCargoString() const;
    std::string getTelefono() const;
    double getSalario() const;
    bool getActivo() const;
    std::string getFechaContratacion() const;
    int getAnioContratacion() const;
    
    // Setters
    void setCargo(CargoEmpleado nuevoCargo);
    void setTelefono(std::string nuevoTelefono);
    void setSalario(double nuevoSalario);
    void setActivo(bool activo);
    
    // Métodos
    void mostrarInfo() const;
    int calcularAntiguedad() const; // En anios (simplificado)
    void aumentarSalario(double porcentaje);
};
#endif