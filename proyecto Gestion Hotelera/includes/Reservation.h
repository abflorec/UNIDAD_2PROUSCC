#ifndef RESERVATION_H
#define RESERVATION_H

#include "Cliente.h"
#include "Room.h"
#include "Servicio.h"
#include <string>
#include<vector>

class Reservation {
private:
    int idReserva;
    Cliente* cliente;
    Room* habitacion;
    std::string fechaCheckIn;  // Formato: "15/06/2024"
    std::string fechaCheckOut; // Formato: "20/06/2024"
    int numNoches;
    int numPersonas;
    bool checkInRealizado;
    bool checkOutRealizado;
    std::string observaciones;
    std::vector<Servicio> serviciosConsumidos;
    static int contadorReservas;
    
public:
    Reservation(Cliente* cliente, Room* habitacion, 
                std::string fechaCheckIn, std::string fechaCheckOut,
                int numPersonas, std::string observaciones = "");
    
    // Getters
    int getIdReserva() const;
    Cliente* getCliente() const;
    Room* getHabitacion() const;
    std::string getFechaCheckIn() const;
    std::string getFechaCheckOut() const;
    int getNumNoches() const;
    int getNumPersonas() const;
    bool getCheckInRealizado() const;
    bool getCheckOutRealizado() const;
    std::string getObservaciones() const;
    double getCostoTotal() const;
    
    // Setters
    void setObservaciones(std::string nuevasObservaciones);
    void agregarServicio(Servicio servicio);
    std::vector<Servicio> getServiciosConsumidos() const;
    
    // Métodos
    void realizarCheckIn();
    void realizarCheckOut();
    bool estaActiva() const;
    void mostrarInfo() const;
    void modificarFechas(std::string nuevaCheckIn, std::string nuevaCheckOut);
};

#endif