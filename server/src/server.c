#include "server.h"

int main(void) {
	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor(); //inicia servidor en ese fd (file descriptos)
	log_info(logger, "Servidor listo para recibir al cliente"); //logea
	int cliente_fd = esperar_cliente(server_fd); //se pone a esperar cliente

	t_list* lista;
	while (1) {
		int cod_op = recibir_operacion(cliente_fd); //bloqueante: se queda esperando sin avanzar
		switch (cod_op) { //recibe cod de operacion q indica si voy a enviar mensaje o paquete
		case MENSAJE:
			recibir_mensaje(cliente_fd);
			break;
		case PAQUETE:
			lista = recibir_paquete(cliente_fd);
			log_info(logger, "Me llegaron los siguientes valores:\n");
			list_iterate(lista, (void*) iterator);
			break;
		case -1:
			log_error(logger, "el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
	return EXIT_SUCCESS;
}

void iterator(char* value) {
	log_info(logger,"%s", value);
}
