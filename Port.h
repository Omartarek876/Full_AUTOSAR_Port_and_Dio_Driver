 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: omar tarek
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* PORT Module Id */
#define PORT_MODULE_ID    (124U)

/* PORT Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)


/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and PORT Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* PORT Pre-Compile Configuration Header file */
#include "Port_cfg.h"

/* AUTOSAR Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_cfg.h does not match the expected version"
#endif

/* Software Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PORT_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"


                             /* Module Data Types */
/* Type definition for the type of a pin (used by the PORT APIs) */
typedef uint8 Port_PinType;

/* Type definition for the type of a port (used by the DIO APIs) */
typedef uint8 Port_PortType;

/* Type definition for different port pin modes */
typedef uint8 Port_PinModeType;

/* Type definition for digital pin mode */
typedef uint8 Port_PinDigitalMode;

/* Type definition for whether pin direction is changable */
typedef uint8 Port_PinDirectionChangable;

/* Type definition for whether pin mode is changable */
typedef uint8 Port_PinModeChangable;

/* Type definition for setting the direction of a PORT Pin */
typedef enum
{
  PORT_INPUT_PIN,  /* INPUT */
  PORT_OUTPUT_PIN  /* OUTPUT */
}Port_PinDirectionType;

/* Type definition for setting internal resistor of a PORT Pin */
typedef enum
{
    OFF,              /* resistor is turned off */
    PULL_DOWN,        /* pull up resistor is active */
    PULL_UP           /* pull down resistor is active */
}Port_InternalResistor;


/* Structure containing initialization data for PORT module */
typedef struct {
    Port_PortType Port_Num;
    Port_PinType Pin_Num;
    Port_PinDirectionType Pin_Direction;
    uint8 initial_value;  /* Initial value of the pin */
    Port_PinModeType Pin_Mode;
    Port_InternalResistor Resistor;
    Port_PinDirectionChangable Pin_DirectionChangable;
    Port_PinModeChangable Pin_ModeChangable;
} Port_ConfigPins;


/* Structure containing initialization data for PORT module */
typedef struct {
    Port_ConfigPins Pins[PORT_CONFIGURED_CHANNLES];
} Port_ConfigType;


                                       /* Function Prototypes */

/*
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: non reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
*/
void Port_Init(const Port_ConfigType* Port_Configuration);


/*
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): - Pin       - Port Pin ID number
*                  - Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
*/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
#endif


/*
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: non reentrant
* Parameters (in): none
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
*/
void Port_RefreshPortDirection(void);


/*
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: non reentrant
* Parameters (in): none
* Parameters (inout): None
* Parameters (out): Version info - Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
*/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif


/*
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): - Pin       - Port Pin ID number
*                  - Mode      - New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
*/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#endif


                              /* API Service Id Macros */
/* Service ID for port init */
#define PORT_INIT_SID                               (uint8)0x00

/* Service ID for port Set pin direction */
#define PORT_SET_PIN_DIRECTION_SID                  (uint8)0x01

/* Service ID for port refresh port direction */
#define PORT_REFRESH_PORT_DIRECTION_SID             (uint8)0x02

/* Service ID for port get version info */
#define PORT_GET_VERSION_INFO_SID                   (uint8)0x03

/* Service ID for port set pin mode */
#define PORT_SET_PIN_MODE                           (uint8)0x04


                                 /* DET Error Codes */
/*Invalid Port Pin ID requested*/
#define PORT_E_PARAM_PIN                        (uint8)(0x0A)

/*Port Pin not configured as changeable*/
#define PORT_E_DIRECTION_UNCHANGEABLE           (uint8)(0x0B)

/*API Port_Init service called with wrong parameter*/
#define PORT_E_PARAM_CONFIG                     (uint8)(0x0C)

/*API Port_SetPinMode service called when mode is unchangeable.*/
#define PORT_E_PARAM_INVALID_MODE               (uint8)(0x0D)
#define PORT_E_MODE_UNCHANGEABLE                (uint8)(0x0E)

/*API service called without module initialization*/
#define PORT_E_UNINIT                           (uint8)(0x0F)

/*APIs called with a Null Pointer*/
#define PORT_E_PARAM_POINTER                    (uint8)(0x10)


                                /* External Variables */
/* Extern PB structures to be used by Dio and other modules */
extern const Port_ConfigType Port_Configuration;


                                 /* Definitions */
typedef enum {
  PORTA_ID,
  PORTB_ID,
  PORTC_ID,
  PORTD_ID,
  PORTE_ID,
  PORTF_ID,
}PORT_ID;
typedef enum {
 PIN0_ID,
 PIN1_ID,
 PIN2_ID,
 PIN3_ID,
 PIN4_ID,
 PIN5_ID,
 PIN6_ID,
 PIN7_ID,
}PIN_ID;

#endif /* PORT_H */



