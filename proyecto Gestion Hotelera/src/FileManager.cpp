#include "FileManager.h"
#include <windows.h> // Para CreateDirectory en Windows

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(a) _mkdir(a)
#else
    #include <sys/stat.h>
    #include <sys/types.h>
    #define MKDIR(a) mkdir(a, 0755)
#endif

bool FileManager::crearDirectorio(const std::string& nombre) {
    // Crear directorio (funciona en Windows y Linux)
    #ifdef _WIN32
        return CreateDirectory(nombre.c_str(), NULL) != 0 || 
               GetLastError() == ERROR_ALREADY_EXISTS;
    #else
        return MKDIR(nombre.c_str()) == 0 || errno == EEXIST;
    #endif
}

std::string FileManager::obtenerFechaActual() {
    time_t ahora = time(0);
    tm* tiempo = localtime(&ahora);
    
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", tiempo);
    return std::string(buffer);
}

std::string FileManager::obtenerHoraActual() {
    time_t ahora = time(0);
    tm* tiempo = localtime(&ahora);
    
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%H-%M-%S", tiempo);
    return std::string(buffer);
}

bool FileManager::guardarTexto(const std::string& archivo, const std::string& contenido) {
    std::ofstream file(archivo);
    if (file.is_open()) {
        file << contenido;
        file.close();
        return true;
    }
    return false;
}

std::string FileManager::leerTexto(const std::string& archivo) {
    std::ifstream file(archivo);
    std::string contenido, linea;
    
    if (file.is_open()) {
        while (getline(file, linea)) {
            contenido += linea + "\n";
        }
        file.close();
    }
    return contenido;
}

bool FileManager::existeArchivo(const std::string& archivo) {
    std::ifstream file(archivo);
    return file.good();
}