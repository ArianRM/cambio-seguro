#include "Controller.h"
#include "Cuenta.h"
#include <iostream>
#include <string>

CController controller;

using namespace std;

void registrarUsuario() {
  int opcion = 1;
  string name, user, password;
  name = "";
  cout << "\n\t\tREGISTRAR USUARIO"
       << "\n\n";
  cout << "Ingrese su nombre: ";
  while (name.size() < 1) {
    getline(cin, name);
  }

  bool usuarioExiste = false;
  do {
    cout << "Ingrese su nombre de usuario: ";
    cin >> user;
    usuarioExiste = controller.buscarCuentaPorUsuario(user) != nullptr;
    if (usuarioExiste) {
      cout << "Usuario ya registrado, intente otra vez" << '\n';
    }
  } while (usuarioExiste);

  bool passwordAccepted = false;
  do {
    cout << "Ingrese su contrasena: ";
    cin >> password;
    passwordAccepted = password.size() >= 4;
    if (!passwordAccepted)
      cout << "Su contrasena debe tener mas de 4 digitos" << '\n';
  } while (!passwordAccepted);

  CCuenta *nuevaCuenta = new CCuenta(name, user, password);
  controller.registrarCuenta(nuevaCuenta);
}

CCuenta *iniciarSesion() {

  string user, password;
  cout << "\n\t\tINISIAR SESION"
       << "\n\n";
  cout << "Ingrese su usuario: ";
  cin >> user;
  cout << "Ingrese su contrasena: ";
  cin >> password;
  CCuenta *cuenta = controller.iniciarSesion(user, password);
  if (cuenta != nullptr)
    return cuenta;
  return nullptr;
}

void menuInisioSesion(CCuenta *cuenta) {

  int opcion = 1;
  do {
    cout << "\n\t\tBienvenido " << cuenta->getName() << "\n\n";
    cout << "1) Ingresar monto" << '\n';
    cout << "2) Ver saldo" << '\n';
    cout << "0) Salir" << '\n';
    cout << "\nElija una opcion: ";
    cin >> opcion;
    CCuenta *cuenta;
    string moneda;
    float monto;
    switch (opcion) {
    case 1:
      cout << "Seleccione el tipo de moneda:";
      cin >> moneda;
      cout << "Digite el monto: ";
      cin >> monto;
      cout << "monto ingresado: " << monto << '\n';
      cuenta->addSaldo(monto, moneda);
      break;
    case 2:
      cuenta->imprimirSaldos();
      break;
    }
  } while (opcion != 0);
}

void menu() {
  int opcion = 1;
  do {
    cout << "\n\t\tBIENVENIDO A CAMBIO SEGURO"
         << "\n\n";
    cout << "1) Inisiar sesion" << '\n';
    cout << "2) Registrarse" << '\n';
    cout << "0) Salir" << '\n';
    cout << "\nElija una opcion: ";
    cin >> opcion;
    CCuenta *cuenta;
    switch (opcion) {
    case 1:
      cuenta = iniciarSesion();
      if (cuenta != nullptr)
        menuInisioSesion(cuenta);
      if (cuenta == nullptr) {
        cout << "\nUsuario o contrasena incorrecta" << '\n';
      }
      break;
    case 2:
      registrarUsuario();
    }
  } while (opcion != 0);
}

int main(int argc, char *argv[]) {
  CCuenta *oliver = new CCuenta("oliver", "oliver", "1234");
  controller.registrarCuenta(oliver);
  // oliver->imprimirSaldos();
  // oliver->addSaldo(1, "USD");
  // oliver->imprimirSaldos();
  menu();
  return 0;
}
