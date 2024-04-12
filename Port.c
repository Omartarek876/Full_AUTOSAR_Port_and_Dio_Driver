 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: omar tarek
 ******************************************************************************/


#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT  == STD_ON)
#include "Det.h"

/* AUTOSAR checking between DET and PORT.h */
#if (DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
    ||(DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
    ||(DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION)

#error "The AR version of PORT.h does not match the expected version"

#endif

#endif

/*
 * static pointer used to setup all the configurations
 * */
STATIC const Port_ConfigPins * Port_PortPins = NULL_PTR;

/*
 * static variable to save the status of the port initialization ( INITIALIZED / NOT INITIALIZED )
 * */
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;


/*
 * Port_Init function
 * */
void Port_Init(const Port_ConfigType* Port_Configuration)
{
    /* point to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULL_PTR;
    volatile uint32 delay = 0;
    /* for loop variable */
    uint8 Pin_Id;

#if (PORT_DEV_ERROR_DETECT  == STD_ON)
    if (NULL_PTR == Port_Configuration)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_POINTER);
    }
    else
#endif
    {
        Port_PortPins = Port_Configuration->Pins;
    }


    /* loop on all the pins to setup their configurations */
    for (Pin_Id = 0; Pin_Id<PORT_CONFIGURED_CHANNLES ; Pin_Id++)
    {
         /* setup the configurations for all pins expect the 4 JTAG pins to avoid any damage on it */
         if ((Pin_Id < 16 ) || (Pin_Id > 19))
         {

                     /*
                      * (port configuration)
                      * switch case to determine the current port base address to be
                      * able to access the port registers easlly by their offset
                      */
                      switch (Port_PortPins[Pin_Id].Port_Num)
                      {
                      case 0:
                          PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                      break;
                       case 1 :
                          PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                           break;
                       case 2 :
                          PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                           break;
                       case 3 :
                          PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                           break;
                       case 4 :
                          PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                           break;
                       case 5 :
                          PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                           break;
                       default :
                           // do nothing
                           break;
                      } /* end of the switch case */


                   /*
                    * unlock the commit for specific pins (port3.pin7 ans port5.pin0
                    * to be configurable
                    * */
                   if ( ((Port_PortPins[Pin_Id].Port_Num == 3) && (Port_PortPins[Pin_Id].Pin_Num == 7))
                       || ((Port_PortPins[Pin_Id].Port_Num == 5) && (Port_PortPins[Pin_Id].Pin_Num == 0)) )
                   {
                     /* Unlock the GPIOCR register */
                      *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;
                     /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
                     SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_PortPins[Pin_Id].Pin_Num);
                   }


                   /*
                    * Check direction ,initial value and resistor configurations
                    * */
                      if (Port_PortPins[Pin_Id].Pin_Direction == PORT_OUTPUT_PIN)
                      {
                          /* set the direction to be output */
                          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_DIR_REG_OFFSET ), Port_PortPins[Pin_Id].Pin_Num);
                          /* set the initial value to one */
                          if (Port_PortPins[Pin_Id].initial_value == STD_HIGH)
                          {
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_DATA_REG_OFFSET) , Port_PortPins[Pin_Id].Pin_Num);
                          }
                          /* set the initial value to zero */
                          else
                          {
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_DATA_REG_OFFSET) , Port_PortPins[Pin_Id].Pin_Num);
                          }
                      }
                      else if (Port_PortPins[Pin_Id].Pin_Direction == PORT_INPUT_PIN)
                      {
                          /* set the direction to be input */
                          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_DIR_REG_OFFSET ), Port_PortPins[Pin_Id].Pin_Num);
                          /* set the internal resistor to be pull up */
                          if (Port_PortPins[Pin_Id].Resistor == PULL_UP)
                          {
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_PULL_UP_REG_OFFSET) , Port_PortPins[Pin_Id].Pin_Num);
                          }
                          /* set the internal resistor to be pull down */
                          else if (Port_PortPins[Pin_Id].Resistor == PULL_DOWN)
                          {
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_PULL_DOWN_REG_OFFSET) , Port_PortPins[Pin_Id].Pin_Num);
                          }
                          /* set the internal resistor to be off */
                          else
                          {
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_PULL_DOWN_REG_OFFSET) , Port_PortPins[Pin_Id].Pin_Num);
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_PULL_UP_REG_OFFSET ), Port_PortPins[Pin_Id].Pin_Num);
                          }
                      }
                      else
                      {
                          /* do nothing */
                      }


                      /*
                       * Check modes configuration
                       * */
                      /* setup the basic setting in all the modes */
                      if (Port_PortPins[Pin_Id].Pin_Mode == PORT_PIN_MODE_DIO )
                      {
                          /* clear the PMCx bit for this pin to use it as GPIO pin*/
                          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) &= ~(0x0000000F <<(Port_PortPins[Pin_Id].Pin_Num * 4));
                          /* clear certain bit in the GPIOAFSEL register to disable alternative fuction on this pin */
                          CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_ALT_FUNC_REG_OFFSET ) , Port_PortPins[Pin_Id].Pin_Num);
                          /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortPins[Pin_Id].Pin_Num);
                      }
                      else if (Port_PortPins[Pin_Id].Pin_Mode == PORT_PIN_MODE_ADC)
                      {
                          /* clear certain bit in the GPIOAFSEL register to disable alternative fuction on this pin */
                          CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_ALT_FUNC_REG_OFFSET ) , Port_PortPins[Pin_Id].Pin_Num);
                          /* set certain bit in the GPIOAMSEL register to enable analog functionality on this pin */
                          SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortPins[Pin_Id].Pin_Num ) ;
                          /* clear certain bit in the GPIODIR register to set the pin as input */
                          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PortPins[Pin_Id].Pin_Num);
                      }
                      else
                      {
                          /* set certain bit in the GPIOAFSEL register to enable alternative fuction on those pins */
                          SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_ALT_FUNC_REG_OFFSET ) , Port_PortPins[Pin_Id].Pin_Num);
                          /* Set the corresponding bit in the GPIODEN register to enable digital functionality on those pins */
                          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortPins[Pin_Id].Pin_Num);
                      }


                      /* setup the setting of each mode */
                      switch (Port_PortPins[Pin_Id].Pin_Mode)
                      {
                        /* DIO MODE */
                        case PORT_PIN_MODE_DIO :
                        /* do nothing */
                            break;

                        /* ADC MODE */
                        case PORT_PIN_MODE_ADC :
                            if ((Pin_Id == 12) || (Pin_Id == 13) || ((Pin_Id >= 24) && (Pin_Id <= 27)) ||
                                ((Pin_Id >= 32) && (Pin_Id <= 37))) /* PB4,5 ,PD0--3 ,PE0--5 */
                            {
                                 if (Port_PortPins[Pin_Id].Pin_Direction != PORT_INPUT_PIN)
                                 {
                                     Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                                 }
                            }
                            else
                            {
                                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                            }
                            break;

                        /* UART MODE */
                        case PORT_PIN_MODE_UART :
                            if ( (Pin_Id == 20) || (Pin_Id == 21) )  /* PC4,5 */
                            {
                                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000002 <<(Port_PortPins[Pin_Id].Pin_Num * 4));
                            }
                            else if ( (Pin_Id == 0) || (Pin_Id == 1) || (Pin_Id == 8) || (Pin_Id == 9)
                                    || ( (Pin_Id >=20) && (Pin_Id <=23) ) || ( (Pin_Id >=28) && (Pin_Id <=33) )
                                    || (Pin_Id == 36) || (Pin_Id == 37) ) /* PA0,1 ,PB0,1 ,PC4--7 ,PD4--7 ,PE0,1 ,PE4,5*/
                            {
                                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000001 <<(Port_PortPins[Pin_Id].Pin_Num * 4));
                            }
                            else
                            {
                                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                            }
                            break;

                         /* SSI MODE */
                        case PORT_PIN_MODE_SSI :
                            if ( (Pin_Id <= 24) && (Pin_Id >= 27) ) /* PD0--3 */
                            {
                                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000001 <<(Port_PortPins[Pin_Id].Pin_Num * 4));
                            }
                            else if ( ( (Pin_Id >=2) && (Pin_Id <=5) ) ||  ( (Pin_Id >=12) && (Pin_Id <=15) )
                                    ||  ( (Pin_Id >=38) && (Pin_Id <=41) ) ) /* PA2--5 ,PB4--7 ,PF0--3 */
                            {
                                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000002 <<(Port_PortPins[Pin_Id].Pin_Num * 4));
                            }
                            else
                            {
                                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                            }
                            break;

                         /* I2C MODE */
                        case PORT_PIN_MODE_I2C :
                            if ( (Pin_Id == 6) || (Pin_Id == 7) || (Pin_Id == 10) || (Pin_Id == 11)
                                 || (Pin_Id == 24) || (Pin_Id == 25) || (Pin_Id == 36)
                                 || (Pin_Id == 37) ) /* PA6,7 ,PB2,3 ,PD0,1 ,PE4,5 */
                            {
                                /* set the PMCx bit for this pin by 3 to use it as IIC pin*/
                                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000003 <<(Port_PortPins[Pin_Id].Pin_Num * 4));
                            }
                            else
                            {
                                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                            }
                            /* oPen drain select */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_OPEN_DRAIN), Port_PortPins[Pin_Id].Pin_Num);
                            break;

                        /* M0PWM MODE */
                        case PORT_PIN_MODE_M0PWM :
                            if ( ( (Pin_Id >=12 ) && (Pin_Id <=15) ) || (Pin_Id==20 )|| (Pin_Id==21 ) || (Pin_Id==24 )
                                    || (Pin_Id==25) ||( Pin_Id==36) || (Pin_Id==37) ) /*PB4--PB7 ,PC4,5 ,PD0,1 ,PE4,5*/
                            {
                               *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000004 << Port_PortPins[Pin_Id].Pin_Num * 4);
                            }
                            else
                            {
                                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                            }
                            break;

                        /* MOFAULT MODE */
                        case PORT_PIN_MODE_M0FAULT :
                            if ( (Pin_Id==26)  || ( Pin_Id==30 ) || (Pin_Id==40) )/*PD2 , PC6  ,PF2 */
                            {
                               *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000004 << Port_PortPins[Pin_Id].Pin_Num * 4);
                            }
                            else
                            {
                                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                            }
                            break;

                        /* M1PWM MODE */
                        case PORT_PIN_MODE_M1PWM :
                            if ( (Pin_Id==6)  || ( Pin_Id==7 ) || ( Pin_Id==24) || (Pin_Id==25)
                                    || ( (Pin_Id>=36) || (Pin_Id<=41) ) ) /*PA6,7 , PD0,1  ,PE4,5 ,PF0-4 */
                            {
                                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000005 << Port_PortPins[Pin_Id].Pin_Num * 4);
                            }
                            else
                            {
                                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                            }
                            break;

                        /* M1FAULT MODE */
                        case PORT_PIN_MODE_M1FAULT :
                            if ( (Pin_Id==42) )/* PF4 */
                            {
                               *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000005 << Port_PortPins[Pin_Id].Pin_Num * 4);
                            }
                            else
                            {
                                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                            }
                            break;

                        /* PHASE MODE*/
                        case PORT_PIN_MODE_IDX_PHASE :
                            if ( (Pin_Id==21)  || ( Pin_Id==22 ) || ( Pin_Id==30) || (Pin_Id==31)
                                    || (Pin_Id==38) || (Pin_Id==39) )/*PC6,7 , PD6,7 ,PF0,1 */
                            {
                                /* set the PMCx bit for this pin by 8 to use it as NMI pin*/
                                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000006 << Port_PortPins[Pin_Id].Pin_Num * 4);
                            }
                            else
                            {
                                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                            }
                            break;

                        /* TIMER MODE */
                        case PORT_PIN_MODE_TIMER :
                            if ( ( (Pin_Id>= 8)  && ( Pin_Id<= 15 ) ) || ( (Pin_Id>= 20)  && ( Pin_Id<= 31 ) )
                            || ( (Pin_Id>= 36)  && ( Pin_Id<= 42 ) ) )/* PB0--7 ,PC4--7 ,PD0--7 ,PF0--4 */
                            {
                                /* set the PMCx bit for this pin by 8 to use it as NMI pin*/
                                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000007 << Port_PortPins[Pin_Id].Pin_Num * 4);
                            }
                            else
                            {
                                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                            }
                            break;

                        /* CAN MODE */
                        case PORT_PIN_MODE_CAN :
                            if ( (Pin_Id == 38) || (Pin_Id == 41) ) /* PF0,3 */
                            {
                                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000003 << Port_PortPins[Pin_Id].Pin_Num * 4);
                            }
                            else if ( (Pin_Id == 0) || (Pin_Id == 1) || (Pin_Id == 12) || (Pin_Id == 13)
                                    || (Pin_Id == 36) || (Pin_Id == 37) ) /* PA0,1 ,PB4,5 ,PE4,5 */
                            {
                                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000008 << Port_PortPins[Pin_Id].Pin_Num * 4);
                            }
                            else
                            {
                                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                            }
                             break;

                        /* USB MODE */
                        case PORT_PIN_MODE_USB :
                            if ( (Pin_Id==22)  || ( Pin_Id==23 ) || ( Pin_Id==26) || (Pin_Id==27) || (Pin_Id==42)) /* PC6,7 ,PD2,3 ,PF4 */
                            {
                                /* set the PMCx bit for this pin by 8 to use it as NMI pin*/
                                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000008 << Port_PortPins[Pin_Id].Pin_Num * 4);
                            }
                            else
                            {
                                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                            }
                            break;

                        /* NMI MODE */
                        case PORT_PIN_MODE_NMI :
                            if ( (Pin_Id==31)  || ( Pin_Id==38 ) )/*PD7 , PF0 */
                            {
                                /* set the PMCx bit for this pin by 8 to use it as NMI pin*/
                                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000008 << Port_PortPins[Pin_Id].Pin_Num * 4);
                            }
                            else
                            {
                                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                            }
                            break;

                      } /* end of switch case of check modes */

         } /* end of if */

    } /* end of the for loop */

    Port_Status = PORT_INITIALIZED;
} /* end of the function */




/* Port_SetPinDirection function */
#if (PORT_SET_PIN_DIRECTION_API == STD_ON )
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{

#if (PORT_DEV_ERROR_DETECT == STD_ON )
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_UNINIT);
    }
    else
    {
        /* do nothing */
    }

    if (Pin >= PORT_CONFIGURED_CHANNLES)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_PIN);
    }
    else
    {
        /* do nothing */
    }

    if (Port_PortPins[Pin].Pin_DirectionChangable == STD_OFF)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_MODE_UNCHANGEABLE);
    }
    else
    {
        /* do nothing */
    }
#endif

    /* point to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULL_PTR;

    /* switch case to determine the current port base assress to be
     * able to access the registers easlly by their offset
     */
      switch (Port_PortPins[Pin].Port_Num)
        {
        case 0:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        break;
         case 1 :
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
             break;
         case 2 :
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
             break;
         case 3 :
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
             break;
         case 4 :
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
             break;
         case 5 :
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
             break;
         default :
             // do nothing
             break;
        } /* end of the switch case */

        /* set the pin required direction */
        if (Direction == PORT_OUTPUT_PIN)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_DIR_REG_OFFSET ), Port_PortPins[Pin].Pin_Num);
        }
        else if (Direction == PORT_INPUT_PIN)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_DIR_REG_OFFSET ), Port_PortPins[Pin].Pin_Num);
        }
        else
        {
            /* do nothing */
        }

} /* end of the function */
#endif


/* Port_RefreshPortDirection function */
void Port_RefreshPortDirection(void)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON )
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_UNINIT);
    }
    else
#endif
    {
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    uint8 Pin_Index ;
    for (Pin_Index = 0; Pin_Index<=PORT_CONFIGURED_CHANNLES ; Pin_Index++)
     {
            /* switch case to determine the current port base assress to be
             * able to access the registers easlly by their offset
             */
            switch (Port_PortPins[Pin_Index].Port_Num)
            {
            case 0:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
             case 1 :
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                 break;
             case 2 :
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                 break;
             case 3 :
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                 break;
             case 4 :
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                 break;
             case 5 :
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                 break;
             default :
                 // do nothing
                 break;
            } /* end of the switch case */

        if (Port_PortPins[Pin_Index].Pin_DirectionChangable == STD_ON)
        {
            /* set the direction of the pin to the default case (INPUT) */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_DIR_REG_OFFSET ), Port_PortPins[Pin_Index].Pin_Num);
        }
        else
        {
            /* do nothing ... the pin dose not be changed */
        }

    } /* end of for loob */
  } /* end of else */
} /* end of the function */


/* Port_GetVersionInfo function */
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON )
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_UNINIT);
    }
    else
    {
        /* do nothing */
    }

    if (versioninfo == NULL_PTR)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,PORT_GET_VERSION_INFO_SID ,PORT_E_PARAM_POINTER);
    }
    else
    {
        /* do nothing */
    }
#endif

    /* get the version info :
     *  - vendorID
     *  - moduleID
     *  - sw_major_version
     *  - sw_minor_version
     *  - sw_patch_version
     * */
    versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
    versioninfo->moduleID = (uint16)PORT_MODULE_ID;
    versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;

 }  /* end of the function */
#endif


/* Port_SetPinMode function */
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin_Id, Port_PinModeType Mode)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON )
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_UNINIT);
    }
    else
    {
        /* do nothing */
    }

    if (Pin_Id >= PORT_CONFIGURED_CHANNLES)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_PIN);
    }
    else
    {
        /* do nothing */
    }

    if ( (Mode > PORT_PIN_MODE_NMI) || (Mode < PORT_PIN_MODE_DIO) )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_INVALID_MODE);
    }
    else
    {
        /* do nothing */
    }

    if (PORT_PIN_MODE_CHANGEABLE == STD_OFF)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_MODE_UNCHANGEABLE);
    }
    else
    {
        /* do nothing */
    }
#endif

    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    /* switch case to determine the current port base assress to be
     * able to access the registers easlly by their offset
     */
      switch (Port_PortPins[Pin_Id].Port_Num)
        {
        case 0:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        break;
         case 1 :
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
             break;
         case 2 :
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
             break;
         case 3 :
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
             break;
         case 4 :
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
             break;
         case 5 :
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
             break;
         default :
             // do nothing
             break;
        } /* end of the switch case */


                                               /* check mode */
      /* setup the basic setting in all the modes */
       if (Port_PortPins[Pin_Id].Pin_Mode == PORT_PIN_MODE_DIO )
       {
           /* clear certain bit in the GPIOAFSEL register to disable alternative fuction on this pin */
           CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_ALT_FUNC_REG_OFFSET ) , Port_PortPins[Pin_Id].Pin_Num);
           /* clear the PMCx bit for this pin to use it as GPIO pin*/
           *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) &= ~(0x0000000F <<(Port_PortPins[Pin_Id].Pin_Num * 4));
           /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortPins[Pin_Id].Pin_Num);
       }
       else if (Port_PortPins[Pin_Id].Pin_Mode == PORT_PIN_MODE_ADC)
       {
           /* clear certain bit in the GPIOAFSEL register to disable alternative fuction on this pin */
           CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_ALT_FUNC_REG_OFFSET ) , Port_PortPins[Pin_Id].Pin_Num);
           /* set certain bit in the GPIOAMSEL register to enable analog functionality on this pin */
           SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortPins[Pin_Id].Pin_Num ) ;
           /* clear certain bit in the GPIODIR register to set the pin as input */
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PortPins[Pin_Id].Pin_Num);
       }
       else
       {
           /* set certain bit in the GPIOAFSEL register to enable alternative fuction on those pins */
           SET_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_ALT_FUNC_REG_OFFSET ) , Port_PortPins[Pin_Id].Pin_Num);
           /* Set the corresponding bit in the GPIODEN register to enable digital functionality on those pins */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortPins[Pin_Id].Pin_Num);
       }


       /* setup the setting of each mode */
       switch (Port_PortPins[Pin_Id].Pin_Mode)
       {
         /* DIO MODE */
         case PORT_PIN_MODE_DIO :
             /* do nothing */
             break;

         /* ADC MODE */
         case PORT_PIN_MODE_ADC :
             if ((Pin_Id == 12) || (Pin_Id == 13) || ((Pin_Id >= 24) && (Pin_Id <= 27)) ||
                 ((Pin_Id >= 32) && (Pin_Id <= 37))) /* PB4,5 ,PD0--3 ,PE0--5 */
             {
                  if (Port_PortPins[Pin_Id].Pin_Direction != PORT_INPUT_PIN)
                  {
                      Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                  }
             }
             else
             {
                 Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
             }
             break;

         /* UART MODE */
         case PORT_PIN_MODE_UART :
             if ( (Pin_Id == 20) || (Pin_Id == 21) )  /* PC4,5 */
             {
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000002 <<(Port_PortPins[Pin_Id].Pin_Num * 4));
             }
             else if ( (Pin_Id == 0) || (Pin_Id == 1) || (Pin_Id == 8) || (Pin_Id == 9)
                     || ( (Pin_Id >=20) && (Pin_Id <=23) ) || ( (Pin_Id >=28) && (Pin_Id <=33) )
                     || (Pin_Id == 36) || (Pin_Id == 37) ) /* PA0,1 ,PB0,1 ,PC4--7 ,PD4--7 ,PE0,1 ,PE4,5*/
             {
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000001 <<(Port_PortPins[Pin_Id].Pin_Num * 4));
             }
             else
             {
                 Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
             }
             break;

          /* SSI MODE */
         case PORT_PIN_MODE_SSI :
             if ( (Pin_Id <= 24) && (Pin_Id >= 27) ) /* PD0--3 */
             {
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000001 <<(Port_PortPins[Pin_Id].Pin_Num * 4));
             }
             else if ( ( (Pin_Id >=2) && (Pin_Id <=5) ) ||  ( (Pin_Id >=12) && (Pin_Id <=15) )
                     ||  ( (Pin_Id >=38) && (Pin_Id <=41) ) ) /* PA2--5 ,PB4--7 ,PF0--3 */
             {
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000002 <<(Port_PortPins[Pin_Id].Pin_Num * 4));
             }
             else
             {
                 Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
             }
             break;

          /* I2C MODE */
         case PORT_PIN_MODE_I2C :
             if ( (Pin_Id == 6) || (Pin_Id == 7) || (Pin_Id == 10) || (Pin_Id == 11)
                  || (Pin_Id == 24) || (Pin_Id == 25) || (Pin_Id == 36)
                  || (Pin_Id == 37) ) /* PA6,7 ,PB2,3 ,PD0,1 ,PE4,5 */
             {
                 /* set the PMCx bit for this pin by 3 to use it as IIC pin*/
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000003 <<(Port_PortPins[Pin_Id].Pin_Num * 4));
             }
             else
             {
                 Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
             }
             /* oPen drain select */
             SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_OPEN_DRAIN), Port_PortPins[Pin_Id].Pin_Num);
             break;

         /* M0PWM MODE */
         case PORT_PIN_MODE_M0PWM :
             if ( ( (Pin_Id >=12 ) && (Pin_Id <=15) ) || (Pin_Id==20 )|| (Pin_Id==21 ) || (Pin_Id==24 )
                     || (Pin_Id==25) ||( Pin_Id==36) || (Pin_Id==37) ) /*PB4--PB7 ,PC4,5 ,PD0,1 ,PE4,5*/
             {
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000004 << Port_PortPins[Pin_Id].Pin_Num* 4);
             }
             else
             {
                 Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
             }
             break;

         /* MOFAULT MODE */
         case PORT_PIN_MODE_M0FAULT :
             if ( (Pin_Id==26)  || ( Pin_Id==30 ) || (Pin_Id==40) )/*PD2 , PC6  ,PF2 */
             {
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000004 << Port_PortPins[Pin_Id].Pin_Num * 4);
             }
             else
             {
                 Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
             }
             break;

         /* M1PWM MODE */
         case PORT_PIN_MODE_M1PWM :
             if ( (Pin_Id==6)  || ( Pin_Id==7 ) || ( Pin_Id==24) || (Pin_Id==25)
                     || ( (Pin_Id>=36) || (Pin_Id<=41) ) ) /*PA6,7 , PD0,1  ,PE4,5 ,PF0-4 */
             {
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000005 << Port_PortPins[Pin_Id].Pin_Num * 4);
             }
             else
             {
                 Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
             }
             break;

         /* M1FAULT MODE */
         case PORT_PIN_MODE_M1FAULT :
             if ( (Pin_Id==42) )/* PF4 */
             {
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (0x00000005 << Port_PortPins[Pin_Id].Pin_Num * 4);
             }
             else
             {
                 Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
             }
             break;

         /* PHASE MODE*/
         case PORT_PIN_MODE_IDX_PHASE :
             if ( (Pin_Id==21)  || ( Pin_Id==22 ) || ( Pin_Id==30) || (Pin_Id==31)
                     || (Pin_Id==38) || (Pin_Id==39) )/*PC6,7 , PD6,7 ,PF0,1 */
             {
                 /* set the PMCx bit for this pin by 8 to use it as NMI pin*/
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000006 << Port_PortPins[Pin_Id].Pin_Num * 4);
             }
             else
             {
                 Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
             }
             break;

         /* TIMER MODE */
         case PORT_PIN_MODE_TIMER :
             if ( ( (Pin_Id>= 8)  && ( Pin_Id<= 15 ) ) || ( (Pin_Id>= 20)  && ( Pin_Id<= 31 ) )
             || ( (Pin_Id>= 36)  && ( Pin_Id<= 42 ) ) )/* PB0--7 ,PC4--7 ,PD0--7 ,PF0--4 */
             {
                 /* set the PMCx bit for this pin by 8 to use it as NMI pin*/
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000007 << Port_PortPins[Pin_Id].Pin_Num * 4);
             }
             else
             {
                 Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
             }
             break;

         /* CAN MODE */
         case PORT_PIN_MODE_CAN :
             if ( (Pin_Id == 38) || (Pin_Id == 41) ) /* PF0,3 */
             {
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000003 << Port_PortPins[Pin_Id].Pin_Num * 4);
             }
             else if ( (Pin_Id == 0) || (Pin_Id == 1) || (Pin_Id == 12) || (Pin_Id == 13)
                     || (Pin_Id == 36) || (Pin_Id == 37) ) /* PA0,1 ,PB4,5 ,PE4,5 */
             {
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000008 << Port_PortPins[Pin_Id].Pin_Num * 4);
             }
             else
             {
                 Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
             }
              break;

         /* USB MODE */
         case PORT_PIN_MODE_USB :
             if ( (Pin_Id==22)  || ( Pin_Id==23 ) || ( Pin_Id==26) || (Pin_Id==27) || (Pin_Id==42)) /* PC6,7 ,PD2,3 ,PF4 */
             {
                 /* set the PMCx bit for this pin by 8 to use it as NMI pin*/
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000008 << Port_PortPins[Pin_Id].Pin_Num * 4);
             }
             else
             {
                 Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
             }
             break;

         /* NMI MODE */
         case PORT_PIN_MODE_NMI :
             if ( (Pin_Id==31)  || ( Pin_Id==38 ) )/*PD7 , PF0 */
             {
                 /* set the PMCx bit for this pin by 8 to use it as NMI pin*/
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr+PORT_CTL_REG_OFFSET ) |= (0x00000008 << Port_PortPins[Pin_Id].Pin_Num * 4);
             }
             else
             {
                 Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
             }
             break;

       } /* end of switch case of check modes */


}
#endif

