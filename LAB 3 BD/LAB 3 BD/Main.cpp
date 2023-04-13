#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

using namespace std;

const string server = "localhost";
const string username = "tecnologo";
const string password = "tecnologo";

int main(int argc, char* argv[]) {

	sql::Driver* driver;
	sql::Connection* con;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "No se pudo conectar al servidor. Mensaje de error:: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("vehiculo");

	int option = 0;
	while (option != 6) {
		string vin = "";
		string marca = "";
		string modelo = "";
		string fecha_fab = "";
		float precio = 0;
		cout << "===Menu===\n";
		cout << "==========\n";
		cout << "-->1-Ingreso.\n";
		cout << "-->2-Elimino.\n";
		cout << "-->3-Modifico.\n";
		cout << "-->4-Consulto.\n";
		cout << "-->5-Listo.\n";
		cout << "-->6-Fin.\n";
		cin >> option;
		switch (option) {

		case 1:
			cout << "Ingrese el VIN:\n";
			cin >> vin;
			cout << "Ingrese la marca:\n";
			cin >> marca;
			cout << "Ingrese el modelo:\n";
			cin >> modelo;
			cout << "Ingrese fecha de fabricacion (formato YYYY-MM-DD):\n";
			cin >> fecha_fab;
			cout << "Ingrese el precio:\n";
			cin >> precio;


			pstmt = con->prepareStatement("SELECT * FROM auto where vin = ?;");
			pstmt->setString(1, vin);
			result = pstmt->executeQuery();


			if (result->next() == false) {
				pstmt = con->prepareStatement("INSERT INTO auto(vin, marca, modelo,fecha_fab,precio) VALUES(?,?,?,?,?)");
				pstmt->setString(1, vin);
				pstmt->setString(2, marca);
				pstmt->setString(3, modelo);
				pstmt->setString(4, fecha_fab);
				pstmt->setDouble(5, precio);
				pstmt->execute();
				cout << "One row inserted." << endl;
				system("pause");
				system("clear");
			}
			else {
				pstmt = con->prepareStatement("SELECT * FROM auto where vin = ?;");
				pstmt->setString(1, vin);
				result = pstmt->executeQuery();

				while (result->next())
				printf("Ya existe un auto con ese VIN:  -->%s, %s, %s, %s, %i\n", result->getString(1).c_str(), result->getString(2).c_str(), result->getString(3).c_str(), result->getString(4).c_str(), result->getInt(5));
				system("pause");
				system("clear");
			}
			delete result;
			delete pstmt;
			option = 0;
			break;

		case 2:
			cout << "Ingrese el VIN:\n\n";
			cin >> vin;
			pstmt = con->prepareStatement("SELECT * FROM auto where vin = ?;");
			pstmt->setString(1, vin);
			result = pstmt->executeQuery();

			if (result->next() == true) {
				delete result;
				delete pstmt;
				pstmt = con->prepareStatement("SELECT * FROM auto where vin = ?;");
				pstmt->setString(1, vin);
				result = pstmt->executeQuery();
				while (result->next())
					printf("-->%s, %s, %s, %s, %i\n\n", result->getString(1).c_str(), result->getString(2).c_str(), result->getString(3).c_str(), result->getString(4).c_str(), result->getInt(5));
				char res;
				cout << "Desea confirmar? Si= s/S No= Any Tecla\n";
				cin >> res;
				if (res == 's' || res == 'S') {
					pstmt = con->prepareStatement("DELETE FROM auto WHERE vin = ?");
					pstmt->setString(1, vin);
					result = pstmt->executeQuery();
					printf("Row deleted...\n");
					delete pstmt;
					delete result;
				}
				else {
					cout << "Eligio no eliminar el auto\n";
				}
				system("pause");
				system("clear");
			}
			else {
				cout << "Ese VIN no existe\n\n";
			}
			option = 0;
			break;
		case 3:
			cout << "Ingrese VIN del auto a cambiar:\n";
			cin >> vin;
			pstmt = con->prepareStatement("SELECT * FROM auto where vin = ?;");
			pstmt->setString(1, vin);
			result = pstmt->executeQuery();
			if (result->next() == true) {
				delete result;
				delete pstmt;
				pstmt = con->prepareStatement("SELECT * FROM auto where vin = ?;");
				pstmt->setString(1, vin);
				result = pstmt->executeQuery();
				while (result->next())
					printf("-->%s, %s, %s, %s, %i\n\n", result->getString(1).c_str(), result->getString(2).c_str(), result->getString(3).c_str(), result->getString(4).c_str(), result->getInt(5));
				char res;
				cout << "Desea modificar? Si= s/S No= Any Tecla\n";
				cin >> res;
				if (res == 's' || res == 'S') {
					cout << "Ingrese nueva marca:\n";
					cin >> marca;
					cout << "Ingrese nuevo modelo:\n";
					cin >> modelo;
					cout << "Ingrese nueva fecha de fabricacion (formato YYYY-MM-DD):\n";
					cin >> fecha_fab;
					cout << "Ingrese nuevo precio:\n";
					cin >> precio;
					pstmt = con->prepareStatement("UPDATE auto SET marca = ?, modelo = ?, fecha_fab = ?, precio = ? WHERE vin = ?");
					pstmt->setString(1, marca);
					pstmt->setString(2, modelo);
					pstmt->setString(3, fecha_fab);
					pstmt->setDouble(4, precio);
					pstmt->setString(5, vin);
					pstmt->executeQuery();
					printf("Row updated\n");
					delete pstmt;
				}
				else {
					cout << "Eligio no modificar el auto\n";
				}
			}
			else {
				cout << "Ese VIN no existe\n";
			}
			system("pause");
			system("clear");
			option = 0;
			break;

		case 4:
			cout << "Ingrese el VIN a consultar:\n";
			cin >> vin;
			pstmt = con->prepareStatement("SELECT * FROM auto where vin = ?;");
			pstmt->setString(1, vin);
			result = pstmt->executeQuery();

			if (result->next() == true) {
				delete result;
				delete pstmt;
				pstmt = con->prepareStatement("SELECT * FROM auto where vin = ?;");
				pstmt->setString(1, vin);
				result = pstmt->executeQuery();
				while (result->next())
					printf("-->%s, %s, %s, %s, %i\n", result->getString(1).c_str(), result->getString(2).c_str(), result->getString(3).c_str(), result->getString(4).c_str(), result->getInt(5));
			}
			else {
				cout << "Ese VIN no existe\n\n";
			}
			delete result;
			delete pstmt;

			system("pause");
			system("clear");

			option = 0;
			break;

		case 5:

			pstmt = con->prepareStatement("SELECT * FROM auto;");
			result = pstmt->executeQuery();

			while (result->next())
				printf("-->%s, %s, %s, %s, %i\n\n", result->getString(1).c_str(), result->getString(2).c_str(), result->getString(3).c_str(), result->getString(4).c_str(), result->getInt(5));

			delete result;
			delete pstmt;

			system("pause");
			system("clear");
			option = 0;
			break;

		case 6:
			system("clear");
			cout << "===Hasta luego! :) ==\n";
			cout << "=====================\n\n\n";
			break;
		default:
			cout << "ERROR - Opcion no valida\n\n";
		}
	}
	return 0;
}
