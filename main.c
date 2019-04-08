#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <modbus/modbus.h>
#include <string.h>
#include "main.h"
//#include "mysql_save.h"
//#include <mysql.h>
//#include <my_global.h>

//#include "tcp_client.h"

int main(int argc, char *argv[]){
	modbus_t *ctx;

	int dev_adr = 1, dev_cmd = 4, reg = 0, reg_cnt = 2, baud = 2400, flt = 0, tcp = 0;
	char port[20] = {"/dev/ttyUSB0"};
	char net_adr[16] = {"127.0.0.1"};
	uint16_t regs[4];

	int argcnt = 0;
		if(argc > 1){
			while(argcnt < argc){
				if(argv[argcnt][0] == '-'){	//This is atribute of parametr.
					switch(argv[argcnt][1]){
//						case 'c':	reg_cnt = atoi(argv[argcnt + 1]);				//Задание номера порта вручную
										break;
						case 'a':	dev_adr = atoi(argv[argcnt + 1]); //Ручное задание адреса устройства.
										break;
//						case 'r': 	dev_cmd = (atoi(argv[argcnt + 1]))/1000;
//										reg = (atoi(argv[argcnt + 1]))%1000;
//										break;
//						case 'b':	baud = atoi(argv[argcnt + 1]); //Ручное скорости обмена..
//										break;
//						case 'p':	strcpy(port, argv[argcnt + 1]); //Порт обмена.
//										break;
						case 'f':	flt = 1; //Значение с плавающей точкой
										reg_cnt = 4;
										break;
//						case 't':	tcp = 1; //Соединение TCP
//										break;
//						case 'n':	strcpy(net_adr, argv[argcnt + 1]); //Адрес соединенияTCP
//										break;

					}
				}
				if(argv[argcnt][0] == '?'){
					printf("Ключи программы:\n\t-a\t Задание адреса подчиненного устройства в режиме RTU.\n\t-с\t Задание колличества читаемых регистров.\n\t-r\t Команда и адрес регистра (например: 3006, где 3 - команда чтения входного регистра, 6 - адрес этого регистра в приборе).\n\t-b\t Задание скорости обмена в режиме RTU.\n\t-f\t Чтение значения с плавающеей точкой.\n\t-t\t Работа в режиме TCP.\n\t-n\t Сетевой адрес подчиненного в режиме TCP.\n\t-?\t Данная справка.\n");
					return 0;
				}
				argcnt++;
			}
		}


	printf("%d\n", sizeof(device));
//	device = (reg_t *)set_shmem(6767, sizeof(reg_t));



	if(tcp == 0){
		ctx = modbus_new_rtu(port, baud, 'N', 8, 1);

		if (ctx == NULL) {
	   	 fprintf(stderr, "Unable to create the libmodbus context\n");
	      	  return -1;
	    	}

		//Устанавливаем соединение, определяем подчиненное устройство
		if(modbus_connect(ctx) != 0){
			printf("Error while connect.\n");
		}
		modbus_set_slave(ctx, dev_adr);

		if((dev_cmd == 3) || (dev_cmd == 4)){
			if(flt){
				modbus_read_input_registers(ctx, reg, reg_cnt, regs);
//				printf("%.2f\n", get_flo(regs));
			}else{
				modbus_read_input_registers(ctx, reg, reg_cnt, regs);
				printf("%d\n", regs[1] || (regs[0] <<8));
			}
		}

	}else{
		short unsigned int tab_reg[32];

		ctx = modbus_new_tcp(net_adr, 1502);
		modbus_connect(ctx);
		if (modbus_connect(ctx) == -1) {
    		printf("Connection failed.\n");
    		modbus_free(ctx);
   		 return -1;
		}
		/* Read 5 registers from the address 0 */
		modbus_read_registers(ctx, reg, reg_cnt, tab_reg);
		printf("tab_reg[0]: %d\n", tab_reg[0]);
	}


	//Освобождаем ресурсы 
	modbus_close(ctx);
	modbus_free(ctx);


return 0;
}


float get_flo(uint16_t *regs){
	float dig;
	int tmp;
	
	tmp = (regs[0] << 16) | regs[1];
	memcpy(&dig, &tmp, sizeof(tmp));

	return dig;
}

/*
int save_to_database(mysql_conn_res *con_res, char *query, char *table){
	MYSQL *ms;

	ms = mysql_init(NULL);

	if(0 == mysql_real_connect(ms, con_res->host, con_res->user, con_res->passwd, con_res->d_base, 0, NULL, 0)){
		fprintf(stderr, "%s\n", mysql_error(ms));
	}

	if(0 == mysql_query(ms, "USE home;")){
		if(0 != mysql_query(ms, query)){
			fprintf(stderr, "%s\n", mysql_error(ms));
		}
	}

	mysql_close(ms);
	return 0;
}
*/
