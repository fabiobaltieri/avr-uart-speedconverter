/* general */

#define F_CPU 8000000UL

#define UART_SPEED 38400
#define UOUT_SPEED 4800

/* LED functions */
#define LED_PORT PORTD
#define LED_DDR  DDRD
#define LED_A    PORTD3

#define led_a_on()     LED_PORT |=  _BV(LED_A)
#define led_a_off()    LED_PORT &= ~_BV(LED_A)
#define led_a_toggle() LED_PORT ^=  _BV(LED_A)

/* UART_IN */
#define UIN_PORT PORTD
#define UIN_DDR  DDRD
#define UIN_PIN  PIND
#define UIN      PORTD0

#define uin_get()     (UIN_PIN & _BV(UIN))

/* UART_OUT */
#define UOUT_PORT PORTD
#define UOUT_DDR  DDRD
#define UOUT      PORTD2

#define uout_high()     UOUT_PORT |=  _BV(UOUT)
#define uout_low()      UOUT_PORT &= ~_BV(UOUT)
