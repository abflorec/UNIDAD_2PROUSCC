#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>
#include <direct.h> // Para mkdir en Windows

class FileManager {
public:
    // Crear directorio si no existe
    static bool crearDirectorio(const std::string& nombre);
    
    // Obtener fecha actual como string
    static std::string obtenerFechaActual();
    
    // Obtener hora actual como string
    static std::string obtenerHoraActual();
    
    // Guardar texto en archivo
    static bool guardarTexto(const std::string& archivo, const std::string& contenido);
    
    // Leer texto de archivo
    static std::string leerTexto(const std::string& archivo);
    
    // Verificar si existe archivo
    static bool existeArchivo(const std::string& archivo);
};

#endif