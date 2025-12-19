#include "Empleado.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

Empleado::Empleado(int id, std::string nombre, std::string apellido, 
                   std::string dni, CargoEmpleado cargo, std::string telefono
                   , double salario, std::string fechaContratacion)
    : idEmpleado(id), nombre(nombre), apellido(apellido), dni(dni),
      cargo(cargo), telefono(telefono),salario(salario),
      activo(true), fechaContratacion(fechaContratacion), anioContratacion(2020) {}

int Empleado::getIdEmpleado() const { return idEmpleado; }
std::string Empleado::getNombre() const { return nombre; }
std::string Empleado::getApellido() const { return apellido; }
std::string Empleado::getDni() const { return dni; }
CargoEmpleado Empleado::getCargo() const { return cargo; }
std::string Empleado::getTelefono() const { return telefono; }
double Empleado::getSalario() const { return salario; }
bool Empleado::getActivo() const { return activo; }
std::string Empleado::getFechaContratacion() const { return fechaContratacion; }
int Empleado::getAnioContratacion() const { return anioContratacion; }

std::string Empleado::getNombreCompleto() const {
    return nombre + " " + apellido;
}

std::string Empleado::getCargoString() const {
    switch(cargo) {
        case CargoEmpleado::RECEPCIONISTA: return "Recepcionista";
        case CargoEmpleado::GERENTE: return "Gerente";
        case CargoEmpleado::LIMPIEZA: return "Limpieza";
        case CargoEmpleado::SEGURIDAD: return "Seguridad";
        case CargoEmpleado::MANTENIMIENTO: return "Mantenimiento";
        case CargoEmpleado::CHEF: return "Chef";
        case CargoEmpleado::CAMARERO: return "Camarero";
        default: return "Desconocido";
    }
}

void Empleado::setCargo(CargoEmpleado nuevoCargo) { cargo = nuevoCargo; }
void Empleado::setTelefono(std::string nuevoTelefono) { telefono = nuevoTelefono; }
void Empleado::setSalario(double nuevoSalario) { if (nuevoSalario > 0) salario = nuevoSalario; }
void Empleado::setActivo(bool activo) { this->activo = activo; }

void Empleado::mostrarInfo() const {
    std::cout << "=== INFORMACION DEL EMPLEADO ===\n";
    std::cout << "ID: " << idEmpleado << "\n";
    std::cout << "Nombre: " << getNombreCompleto() << "\n";
    std::cout << "DNI: " << dni << "\n";
    std::cout << "Cargo: " << getCargoString() << "\n";
    std::cout << "Telefono: " << telefono << "\n";
    std::cout << "Salario: $" << std::fixed << std::setprecision(2) << salario << "\n";
    std::cout << "Estado: " << (activo ? "Activo" : "Inactivo") << "\n";
    std::cout << "Fecha de contratacion: " << fechaContratacion << "\n";
    std::cout << "Antiguedad: " << calcularAntiguedad() << " anios\n";
}

int Empleado::calcularAntiguedad() const {
    // Simplificado: asumimos anio actual 2024
    return 2024 - anioContratacion;
}

void Empleado::aumentarSalario(double porcentaje) {
    if (porcentaje > 0) {
        double aumento = salario * (porcentaje / 100);
        salario += aumento;
    }
}