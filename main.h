#define VOLTS 0x00
#define AMPS 0x06
#define TOTAL_ACT_POW 0x56
#define TOTAL_REACT_POW 0x58


#define LOG_FLO(exp) printf("%.2f\n", exp)

typedef struct{
	char name[15];
	int reg_addr;
	float reg_value;
}reg_t;


reg_t rgs[100];

float get_flo(uint16_t *regs);
