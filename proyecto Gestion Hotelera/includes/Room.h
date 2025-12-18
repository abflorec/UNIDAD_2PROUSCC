#ifndef ROOM_H
#define ROOM_H

#include <string>
#include<vector>

enum class TipoHabitacion {
    INDIVIDUAL,
    DOBLE,
    SUITE,
    PRESIDENCIAL
};

enum class EstadoHabitacion {
    DISPONIBLE,
    OCUPADA,
    MANTENIMIENTO,
    RESERVADA
};

class Room {
private:
    int numero;
    TipoHabitacion tipo;
    EstadoHabitacion estado;
    double precioNoche;
    int capacidad;
    bool tieneVista;
    std::string caracteristicas;
    
public:
    Room(int numero, TipoHabitacion tipo, double precioNoche, 
         int capacidad, bool tieneVista, std::string caracteristicas);
    
    // Getters
    int getNumero() const;
    TipoHabitacion getTipo() const;
    std::string getTipoString() const;
    EstadoHabitacion getEstado() const;
    std::string getEstadoString() const;
    double getPrecioNoche() const;
    int getCapacidad() const;
    bool getTieneVista() const;
    std::string getCaracteristicas() const;
    
    // Setters
    void setEstado(EstadoHabitacion nuevoEstado);
    void setPrecioNoche(double nuevoPrecio);
    void setCaracteristicas(std::string nuevasCaracteristicas);
    
    // Métodos
    bool estaDisponible() const;
    void mostrarInfo() const;
    double calcularCosto(int numNoches) const;
};

#endif