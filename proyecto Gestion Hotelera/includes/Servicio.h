#ifndef SERVICIO_H
#define SERVICIO_H

#include <string>
#include<vector>

enum class TipoServicio {
    RESTAURANTE,
    SPA,
    LAVANDERIA,
    TRANSPORTE,
    GIMNASIO,
    PISCINA,
    MINIBAR,
    ROOM_SERVICE
};

class Servicio {
private:
    int idServicio;
    TipoServicio tipo;
    std::string nombre;
    std::string descripcion;
    double precio;
    bool disponible;
    
public:
    Servicio(int id, TipoServicio tipo, std::string nombre, 
             std::string descripcion, double precio);
    
    // Getters
    int getIdServicio() const;
    TipoServicio getTipo() const;
    std::string getTipoString() const;
    std::string getNombre() const;
    std::string getDescripcion() const;
    double getPrecio() const;
    bool getDisponible() const;
    
    // Setters
    void setPrecio(double nuevoPrecio);
    void setDisponible(bool disponible);
    void setDescripcion(std::string nuevaDescripcion);
    
    // Métodos
    void mostrarInfo() const;
    void aplicarDescuento(double porcentaje);
};

#endif
