/*
 * Client.hh
 *
 *  Created on: Oct 13, 2018
 *      Author: maximiliano
 */

#ifndef MODEL_CLIENT_HH_
#define MODEL_CLIENT_HH_

#include <string>
#include <queue>
#include <thread>
#include <errno.h>

#include "../../Utils/MessageServer.hh"

extern pthread_mutex_t server_clients_mutex;

enum CLIENT_STATE {
	CLIENT_ONLINE,
	CLIENT_OFFLINE
};

class Client
{
	public:

		Client(int _socket, std::string _ip, int _port, std::string _username, std::string _password);
		virtual ~Client();

		int getSocket();

		bool isOnline();
		bool isOffline();

		void setOffline();
		void setOnline(int connection_socket);

		std::string getIp() { return ip; }
		int getPort() { return port; }

		int getClientId() { return id; }
		std::string getUsername() { return username; }
		std::string getPassword() { return password; }

		pthread_t* getRecieveMessagesThread() { return &receive_messages_thread; }

	private:

		static int CLIENT_ID_COUNTER;

		int socket, port, id;
		std::string ip;

		CLIENT_STATE state;

		std::string username;
		std::string password;

		std::queue<MessageServer*> sending_messages; // Aca se irían encolando los mensajes que quearmos ir enviando al cliente.
		// El asunto es que si a todos los clientes mando lo mismo, sería al pedo tener 4 colas iguales, quizas convenga una sola en Server,
		// aunque el envio va a ser distinto para cada cliente en la fase previa a que el cliente comience a jugar (pedido de datos de login, etc)

		pthread_t receive_messages_thread;
};

#endif /* MODEL_CLIENT_HH_ */
