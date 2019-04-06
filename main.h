#define VOLTS 0x00
#define AMPS 0x06
#define TOTAL_ACT_POW 0x56
#define TOTAL_REACT_POW 0x58


#define LOG_FLO(exp) printf("%.2f\n", exp)

float get_flo(uint16_t *regs);
