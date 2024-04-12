 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_cfg.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: omar tarek
 ******************************************************************************/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION           (1U)
#define PORT_CFG_SW_MINOR_VERSION           (0U)
#define PORT_CFG_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION   (3U)


/* Switches the Development Error Detection and Notification on or off
. STD_ON  : Enabled.
  STD_OFF : Disabled */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-processor switch to enable / disable the use of the function Port_SetPinDirection().
 STD_ON  : Enabled - Function Port_SetPinDirection() is available.
 STD_OFF : Disabled - Function Port_SetPinDirection() is not available. */
#define PORT_SET_PIN_DIRECTION_API           (STD_ON)

/* Pre-processor switch to enable / disable the use of the function Port_SetPinMode().
 STD_ON  : Enabled - Function Port_SetPinMode() is available.
 STD_OFF : Disabled - Function Port_SetPinMode() is not available. */
#define PORT_SET_PIN_MODE_API                (STD_ON)

/* Pre-processor switch to enable / disable the API to read out the modules version information.
 STD_ON  : Version info API enabled.
 STD_OFF : Version info API disabled. */
#define PORT_VERSION_INFO_API                (STD_ON)
/*
 The initial direction of the pin (IN or OUT).
 If the direction is not changeable, the value configured here is fixed.
 The direction must match the pin mode.
 E.g. a pin used for an ADC must be configured to be an in port.
 Implementation Type: Port_PinDirectionType
*/
#define PORT_PIN_DIRECTION                   (STD_ON)

/* Number of the configured Port PINs */
#define PORT_CONFIGURED_CHANNLES             (43U)

/*Parameter to indicate if the direction is changeable on a port pin during runtime.
 STD_ON  : Port Pin direction changeable enabled.
 STD_OFF : Port Pin direction changeable disabled.*/
#define PORT_PIN_MODE_CHANGEABLE             (STD_ON)


                           /* Port Modes */
/* Default Mode Of Configuration */
#define PORT_PIN_MODE_DIO        (uint8)1     /* GPIO Mode */
#define PORT_PIN_MODE_ADC        (uint8)2     /* ADC Mode */
#define PORT_PIN_MODE_UART       (uint8)3     /* UART Mode */
#define PORT_PIN_MODE_SSI        (uint8)4     /* SPI Mode */
#define PORT_PIN_MODE_I2C        (uint8)5     /* I2C Mode */
#define PORT_PIN_MODE_M0PWM      (uint8)6     /*M0PWM Mode */
#define PORT_PIN_MODE_M0FAULT    (uint8)7     /*Motion Control Module  Mode 0*/
#define PORT_PIN_MODE_M1PWM      (uint8)8     /*M1PWM Mode */
#define PORT_PIN_MODE_M1FAULT    (uint8)9     /*Motion Control Module  Mode 1*/
#define PORT_PIN_MODE_IDX_PHASE  (uint8)10     /* IDX AND PHASE Mode */
#define PORT_PIN_MODE_TIMER      (uint8)11     /* TIMER  Mode */
#define PORT_PIN_MODE_CAN        (uint8)12   /* CAN Mode */
#define PORT_PIN_MODE_USB        (uint8)13    /* USB Mode */
#define PORT_PIN_MODE_NMI        (uint8)14    /*Non-Maskable Interrupt*/


/*
 * - configure the settings for all pins
 * - the defult settings is :
 *    - DIRECTION           -> INPUT
 *    - INITIAL VALUE       -> LOW
 *    - RESISTOR            -> OFF
 *    - MODE                -> DIO
 *    - DIRECTION CHANGABLE -> OFF
 *    - MODE CHANGABLE      -> OFF
 */

                    /* Pins Direction */
                     /* PORTA PINS */
#define PORTA_PIN0_DIRECTION     (PORT_INPUT_PIN)
#define PORTA_PIN1_DIRECTION     (PORT_INPUT_PIN)
#define PORTA_PIN2_DIRECTION     (PORT_INPUT_PIN)
#define PORTA_PIN3_DIRECTION     (PORT_INPUT_PIN)
#define PORTA_PIN4_DIRECTION     (PORT_INPUT_PIN)
#define PORTA_PIN5_DIRECTION     (PORT_INPUT_PIN)
#define PORTA_PIN6_DIRECTION     (PORT_INPUT_PIN)
#define PORTA_PIN7_DIRECTION     (PORT_INPUT_PIN)
                     /* PORTB PINS */
#define PORTB_PIN0_DIRECTION     (PORT_INPUT_PIN)
#define PORTB_PIN1_DIRECTION     (PORT_INPUT_PIN)
#define PORTB_PIN2_DIRECTION     (PORT_INPUT_PIN)
#define PORTB_PIN3_DIRECTION     (PORT_INPUT_PIN)
#define PORTB_PIN4_DIRECTION     (PORT_INPUT_PIN)
#define PORTB_PIN5_DIRECTION     (PORT_INPUT_PIN)
#define PORTB_PIN6_DIRECTION     (PORT_INPUT_PIN)
#define PORTB_PIN7_DIRECTION     (PORT_INPUT_PIN)
                     /* PORTC PINS */
#define PORTC_PIN0_DIRECTION     (PORT_INPUT_PIN)
#define PORTC_PIN1_DIRECTION     (PORT_INPUT_PIN)
#define PORTC_PIN2_DIRECTION     (PORT_INPUT_PIN)
#define PORTC_PIN3_DIRECTION     (PORT_INPUT_PIN)
#define PORTC_PIN4_DIRECTION     (PORT_INPUT_PIN)
#define PORTC_PIN5_DIRECTION     (PORT_INPUT_PIN)
#define PORTC_PIN6_DIRECTION     (PORT_INPUT_PIN)
#define PORTC_PIN7_DIRECTION     (PORT_INPUT_PIN)
                     /* PORTD PINS */
#define PORTD_PIN0_DIRECTION     (PORT_INPUT_PIN)
#define PORTD_PIN1_DIRECTION     (PORT_INPUT_PIN)
#define PORTD_PIN2_DIRECTION     (PORT_INPUT_PIN)
#define PORTD_PIN3_DIRECTION     (PORT_INPUT_PIN)
#define PORTD_PIN4_DIRECTION     (PORT_INPUT_PIN)
#define PORTD_PIN5_DIRECTION     (PORT_INPUT_PIN)
#define PORTD_PIN6_DIRECTION     (PORT_INPUT_PIN)
#define PORTD_PIN7_DIRECTION     (PORT_INPUT_PIN)
                     /* PORTE PINS */
#define PORTE_PIN0_DIRECTION     (PORT_INPUT_PIN)
#define PORTE_PIN1_DIRECTION     (PORT_INPUT_PIN)
#define PORTE_PIN2_DIRECTION     (PORT_INPUT_PIN)
#define PORTE_PIN3_DIRECTION     (PORT_INPUT_PIN)
#define PORTE_PIN4_DIRECTION     (PORT_INPUT_PIN)
#define PORTE_PIN5_DIRECTION     (PORT_INPUT_PIN)
                     /* PORTF PINS */
#define PORTF_PIN0_DIRECTION     (PORT_INPUT_PIN)
#define PORTF_PIN1_DIRECTION     (PORT_OUTPUT_PIN) /* LED */
#define PORTF_PIN2_DIRECTION     (PORT_INPUT_PIN)
#define PORTF_PIN3_DIRECTION     (PORT_INPUT_PIN)
#define PORTF_PIN4_DIRECTION     (PORT_INPUT_PIN)  /* SWITCH */

                    /* Pins Initial value */
                     /* PORTA */
#define PORTA_PIN0_DATA          (STD_LOW)
#define PORTA_PIN1_DATA          (STD_LOW)
#define PORTA_PIN2_DATA          (STD_LOW)
#define PORTA_PIN3_DATA          (STD_LOW)
#define PORTA_PIN4_DATA          (STD_LOW)
#define PORTA_PIN5_DATA          (STD_LOW)
#define PORTA_PIN6_DATA          (STD_LOW)
#define PORTA_PIN7_DATA          (STD_LOW)
                     /* PORTB */
#define PORTB_PIN0_DATA          (STD_LOW)
#define PORTB_PIN1_DATA          (STD_LOW)
#define PORTB_PIN2_DATA          (STD_LOW)
#define PORTB_PIN3_DATA          (STD_LOW)
#define PORTB_PIN4_DATA          (STD_LOW)
#define PORTB_PIN5_DATA          (STD_LOW)
#define PORTB_PIN6_DATA          (STD_LOW)
#define PORTB_PIN7_DATA          (STD_LOW)
                     /* PORTC */
#define PORTC_PIN0_DATA          (STD_LOW)
#define PORTC_PIN1_DATA          (STD_LOW)
#define PORTC_PIN2_DATA          (STD_LOW)
#define PORTC_PIN3_DATA          (STD_LOW)
#define PORTC_PIN4_DATA          (STD_LOW)
#define PORTC_PIN5_DATA          (STD_LOW)
#define PORTC_PIN6_DATA          (STD_LOW)
#define PORTC_PIN7_DATA          (STD_LOW)
                     /* PORTD */
#define PORTD_PIN0_DATA          (STD_LOW)
#define PORTD_PIN1_DATA          (STD_LOW)
#define PORTD_PIN2_DATA          (STD_LOW)
#define PORTD_PIN3_DATA          (STD_LOW)
#define PORTD_PIN4_DATA          (STD_LOW)
#define PORTD_PIN5_DATA          (STD_LOW)
#define PORTD_PIN6_DATA          (STD_LOW)
#define PORTD_PIN7_DATA          (STD_LOW)
                     /* PORTE */
#define PORTE_PIN0_DATA          (STD_LOW)
#define PORTE_PIN1_DATA          (STD_LOW)
#define PORTE_PIN2_DATA          (STD_LOW)
#define PORTE_PIN3_DATA          (STD_LOW)
#define PORTE_PIN4_DATA          (STD_LOW)
#define PORTE_PIN5_DATA          (STD_LOW)

                     /* PORTF */
#define PORTF_PIN0_DATA          (STD_LOW)
#define PORTF_PIN1_DATA          (STD_LOW) /* LED */
#define PORTF_PIN2_DATA          (STD_LOW)
#define PORTF_PIN3_DATA          (STD_LOW)
#define PORTF_PIN4_DATA          (STD_LOW) /* SWITCH */

                  /* Pins Alternate Function */
                     /* PORTA */
#define PORTA_PIN0_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTA_PIN1_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTA_PIN2_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTA_PIN3_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTA_PIN4_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTA_PIN5_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTA_PIN6_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTA_PIN7_MODE_TYPE      (PORT_PIN_MODE_DIO)
                     /* PORTB */
#define PORTB_PIN0_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTB_PIN1_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTB_PIN2_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTB_PIN3_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTB_PIN4_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTB_PIN5_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTB_PIN6_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTB_PIN7_MODE_TYPE      (PORT_PIN_MODE_DIO)
                     /* PORTC */
#define PORTC_PIN0_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTC_PIN1_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTC_PIN2_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTC_PIN3_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTC_PIN4_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTC_PIN5_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTC_PIN6_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTC_PIN7_MODE_TYPE      (PORT_PIN_MODE_DIO)
                     /* PORTD */
#define PORTD_PIN0_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTD_PIN1_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTD_PIN2_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTD_PIN3_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTD_PIN4_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTD_PIN5_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTD_PIN6_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTD_PIN7_MODE_TYPE      (PORT_PIN_MODE_DIO)
                     /* PORTE */
#define PORTE_PIN0_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTE_PIN1_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTE_PIN2_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTE_PIN3_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTE_PIN4_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTE_PIN5_MODE_TYPE      (PORT_PIN_MODE_DIO)
                     /* PORTF */
#define PORTF_PIN0_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTF_PIN1_MODE_TYPE      (PORT_PIN_MODE_DIO) /* LED */
#define PORTF_PIN2_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTF_PIN3_MODE_TYPE      (PORT_PIN_MODE_DIO)
#define PORTF_PIN4_MODE_TYPE      (PORT_PIN_MODE_DIO) /* SWITCH */

                  /* Pins Internal Resistor */
                     /* PORTA */
#define PORTA_PIN0_RESISTOR       (OFF)
#define PORTA_PIN1_RESISTOR       (OFF)
#define PORTA_PIN2_RESISTOR       (OFF)
#define PORTA_PIN3_RESISTOR       (OFF)
#define PORTA_PIN4_RESISTOR       (OFF)
#define PORTA_PIN5_RESISTOR       (OFF)
#define PORTA_PIN6_RESISTOR       (OFF)
#define PORTA_PIN7_RESISTOR       (OFF)
                     /* PORTB */
#define PORTB_PIN0_RESISTOR       (OFF)
#define PORTB_PIN1_RESISTOR       (OFF)
#define PORTB_PIN2_RESISTOR       (OFF)
#define PORTB_PIN3_RESISTOR       (OFF)
#define PORTB_PIN4_RESISTOR       (OFF)
#define PORTB_PIN5_RESISTOR       (OFF)
#define PORTB_PIN6_RESISTOR       (OFF)
#define PORTB_PIN7_RESISTOR       (OFF)
                     /* PORTC */
#define PORTC_PIN0_RESISTOR       (OFF)
#define PORTC_PIN1_RESISTOR       (OFF)
#define PORTC_PIN2_RESISTOR       (OFF)
#define PORTC_PIN3_RESISTOR       (OFF)
#define PORTC_PIN4_RESISTOR       (OFF)
#define PORTC_PIN5_RESISTOR       (OFF)
#define PORTC_PIN6_RESISTOR       (OFF)
#define PORTC_PIN7_RESISTOR       (OFF)
                     /* PORTD */
#define PORTD_PIN0_RESISTOR       (OFF)
#define PORTD_PIN1_RESISTOR       (OFF)
#define PORTD_PIN2_RESISTOR       (OFF)
#define PORTD_PIN3_RESISTOR       (OFF)
#define PORTD_PIN4_RESISTOR       (OFF)
#define PORTD_PIN5_RESISTOR       (OFF)
#define PORTD_PIN6_RESISTOR       (OFF)
#define PORTD_PIN7_RESISTOR       (OFF)
                     /* PORTE */
#define PORTE_PIN0_RESISTOR       (OFF)
#define PORTE_PIN1_RESISTOR       (OFF)
#define PORTE_PIN2_RESISTOR       (OFF)
#define PORTE_PIN3_RESISTOR       (OFF)
#define PORTE_PIN4_RESISTOR       (OFF)
#define PORTE_PIN5_RESISTOR       (OFF)
                     /* PORTF */
#define PORTF_PIN0_RESISTOR       (OFF)
#define PORTF_PIN1_RESISTOR       (OFF)     /* LED */
#define PORTF_PIN2_RESISTOR       (OFF)
#define PORTF_PIN3_RESISTOR       (OFF)
#define PORTF_PIN4_RESISTOR       (PULL_UP) /* SWITCH */

                  /* Pins Direction Changable */
                     /* PORTA */
#define PORTA_PIN0_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTA_PIN1_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTA_PIN2_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTA_PIN3_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTA_PIN4_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTA_PIN5_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTA_PIN6_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTA_PIN7_DIRECTION_CHANGABLE         (STD_OFF)
                     /* PORTB */
#define PORTB_PIN0_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTB_PIN1_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTB_PIN2_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTB_PIN3_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTB_PIN4_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTB_PIN5_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTB_PIN6_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTB_PIN7_DIRECTION_CHANGABLE         (STD_OFF)
                     /* PORTC */
#define PORTC_PIN0_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTC_PIN1_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTC_PIN2_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTC_PIN3_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTC_PIN4_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTC_PIN5_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTC_PIN6_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTC_PIN7_DIRECTION_CHANGABLE         (STD_OFF)
                     /* PORTD */
#define PORTD_PIN0_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTD_PIN1_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTD_PIN2_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTD_PIN3_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTD_PIN4_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTD_PIN5_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTD_PIN6_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTD_PIN7_DIRECTION_CHANGABLE         (STD_OFF)
                     /* PORTE */
#define PORTE_PIN0_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTE_PIN1_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTE_PIN2_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTE_PIN3_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTE_PIN4_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTE_PIN5_DIRECTION_CHANGABLE         (STD_OFF)
                     /* PORTF */
#define PORTF_PIN0_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTF_PIN1_DIRECTION_CHANGABLE         (STD_OFF) /* LED */
#define PORTF_PIN2_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTF_PIN3_DIRECTION_CHANGABLE         (STD_OFF)
#define PORTF_PIN4_DIRECTION_CHANGABLE         (STD_OFF) /* SWITCH */

                  /* Pins Mode Changable */
                     /* PORTA */
#define PORTA_PIN0_MODE_CHANGABLE         (STD_OFF)
#define PORTA_PIN1_MODE_CHANGABLE         (STD_OFF)
#define PORTA_PIN2_MODE_CHANGABLE         (STD_OFF)
#define PORTA_PIN3_MODE_CHANGABLE         (STD_OFF)
#define PORTA_PIN4_MODE_CHANGABLE         (STD_OFF)
#define PORTA_PIN5_MODE_CHANGABLE         (STD_OFF)
#define PORTA_PIN6_MODE_CHANGABLE         (STD_OFF)
#define PORTA_PIN7_MODE_CHANGABLE         (STD_OFF)
                     /* PORTB */
#define PORTB_PIN0_MODE_CHANGABLE         (STD_OFF)
#define PORTB_PIN1_MODE_CHANGABLE         (STD_OFF)
#define PORTB_PIN2_MODE_CHANGABLE         (STD_OFF)
#define PORTB_PIN3_MODE_CHANGABLE         (STD_OFF)
#define PORTB_PIN4_MODE_CHANGABLE         (STD_OFF)
#define PORTB_PIN5_MODE_CHANGABLE         (STD_OFF)
#define PORTB_PIN6_MODE_CHANGABLE         (STD_OFF)
#define PORTB_PIN7_MODE_CHANGABLE         (STD_OFF)
                     /* PORTC */
#define PORTC_PIN0_MODE_CHANGABLE         (STD_OFF)
#define PORTC_PIN1_MODE_CHANGABLE         (STD_OFF)
#define PORTC_PIN2_MODE_CHANGABLE         (STD_OFF)
#define PORTC_PIN3_MODE_CHANGABLE         (STD_OFF)
#define PORTC_PIN4_MODE_CHANGABLE         (STD_OFF)
#define PORTC_PIN5_MODE_CHANGABLE         (STD_OFF)
#define PORTC_PIN6_MODE_CHANGABLE         (STD_OFF)
#define PORTC_PIN7_MODE_CHANGABLE         (STD_OFF)
                     /* PORTD */
#define PORTD_PIN0_MODE_CHANGABLE         (STD_OFF)
#define PORTD_PIN1_MODE_CHANGABLE         (STD_OFF)
#define PORTD_PIN2_MODE_CHANGABLE         (STD_OFF)
#define PORTD_PIN3_MODE_CHANGABLE         (STD_OFF)
#define PORTD_PIN4_MODE_CHANGABLE         (STD_OFF)
#define PORTD_PIN5_MODE_CHANGABLE         (STD_OFF)
#define PORTD_PIN6_MODE_CHANGABLE         (STD_OFF)
#define PORTD_PIN7_MODE_CHANGABLE         (STD_OFF)
                     /* PORTE */
#define PORTE_PIN0_MODE_CHANGABLE         (STD_OFF)
#define PORTE_PIN1_MODE_CHANGABLE         (STD_OFF)
#define PORTE_PIN2_MODE_CHANGABLE         (STD_OFF)
#define PORTE_PIN3_MODE_CHANGABLE         (STD_OFF)
#define PORTE_PIN4_MODE_CHANGABLE         (STD_OFF)
#define PORTE_PIN5_MODE_CHANGABLE         (STD_OFF)
                     /* PORTF */
#define PORTF_PIN0_MODE_CHANGABLE         (STD_OFF)
#define PORTF_PIN1_MODE_CHANGABLE         (STD_OFF) /* LED */
#define PORTF_PIN2_MODE_CHANGABLE         (STD_OFF)
#define PORTF_PIN3_MODE_CHANGABLE         (STD_OFF)
#define PORTF_PIN4_MODE_CHANGABLE         (STD_OFF) /* SWITCH */

#endif /* PORT_CFG_H_ */
