@echo off
echo Compilando Sistema Hotelero Completo...
echo.

REM Compilar todos los archivos
g++ -std=c++11 -Iincludes ^
    src/Cliente.cpp ^
    src/Room.cpp ^
    src/Reservation.cpp ^
    src/Pago.cpp ^
    src/Facture.cpp ^
    src/Servicio.cpp ^
    src/Empleado.cpp ^
    src/FileManager.cpp ^
    src/ReporteManager.cpp ^
    main.cpp ^
    -o sistema_hotelero.exe

if exist sistema_hotelero.exe (
    echo.
    echo ✅ COMPILACIÓN EXITOSA!
    echo.
    echo Directorios creados:
    echo   data/        - Para guardar datos
    echo   reportes/    - Para reportes generados
    echo.
    echo Ejecutar: sistema_hotelero.exe
) else (
    echo.
    echo ❌ ERROR EN LA COMPILACIÓN
)

pause