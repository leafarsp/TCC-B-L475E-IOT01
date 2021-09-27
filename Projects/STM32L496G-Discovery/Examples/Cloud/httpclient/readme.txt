/**
  @page HTTPClient HTTPClient example

  @verbatim
  ******************************************************************************
  * @file    readme.txt
  * @author  MCD Application Team
  * @brief   Description of HTTP Client example.
  ******************************************************************************
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  @endverbatim

@par Example Description


This example implements a HTTP Library client for the STM32L496G-Discovery board
using an external UG96 (or BG96) Quectel cellular modem connected via the STmod+ connector,
and mbedTLS for secure network communication.

The firmware connects to httpbin.org and gives examples of HTTP Library commands (Post, Put, ...).

@par Directory contents

---> in .

Inc
  flash.h                            Management of the internal flash memory.
  main.h                             Header containing config parameters for the example and globals.
  stm32l4xx_hal_conf.h               HAL configuration file.
  stm32l4xx_it.h                     STM32 interrupt handlers header file.

Src
  main.c                             Main example file.
  stm32l4xx_hal_msp.c                Specific initializations.
  stm32l4xx_it.c                     STM32 interrupt handlers.
  system_stm32l4xx.c                 System initialization.

---> in Projects/Common/httpclient
Inc:
  httpclient.h                       Include file for the application.
  exosite_mbedtls_config.h           Application-specific mbedTLS configuration.

Src:
  httpclient.c                       httpclient main functions.


---> in Projects/Common/Shared
Inc
  cloud.h                            Cloud header file
  heap.h                             Heap check functions
  http_lib.h                         HTTP library functions
  iot_flash_config.h                 Header for configuration
  mbedtls_net.h                      MbedTLS network callbacks declaration
  msg.h                              Trace message API
  net.h                              Network API
  net_internal.h                     Network abstraction at transport layer level.
                                     Internal definitions
  rfu.h                              Remote firmare upate over TCP/IP
  sensors_data.h                     Sensors header
  timedate.h                         Configuration of the RTC
  timer.h                            Timer basic functions
  timingSystem.h                     Header file for timingSystem.c
  version.h                          STM32 FW version definition

Src
  c2c_net.c                           C2C-LL init/deinit functions. (cellular modem).
  cloud.c                             Common cloud application functions.
  entropy_hardware_poll.c             RNG entropy source for mbedTLS.
  heap.c                              Heap check functions.
  http_lib.c                          HTTP Client library.
  iot_flash_config.c                  Dialog and storage management utils for the user-configured settings.
  mbedtls_net.c                       Network adapter for mbedTLS on NET.
  net.c                               Network socket API.
  net_tcp_c2c.c                       NET TCP / C2C-LL implementation (cellular modem).
  net_tls_mbedtls.c                   NET TLS / mbedTLS implementation.
  rfu.c                               Remote firmare upate over TCP/IP.
  sensors_data.c                      Board-specific file to retrieve and format sensors data.
  STM32CubeRTCInterface.c             Std. time port to the RTC.
  timedate.c                          Initialization of the RTC from the network.
  timingSystem.c                      Wrapper to STM32 timing.

@par Hardware and Software environment
  - STM32L496G-Discovery board.
  - Quectel UG96 or BG96 daughterboard connected to the MCU board IO expander: Modem package upside, SIM card slot downside.  
    * UG96 is the modem used by default. In case you have BG96, you will need
      to define USE_BG96 compilation switch in your project.
	  
  - Activate the UG96 or BG96 embedded SIM card	  
    * The kit comes with a 3-months free of charge subscription with a 15MB of data using the UG96 embedded SIM
    * The user must go to the stm32-c2c.com portal and enter a voucher to activate this subscription.
    * The Voucher is found by connecting the board to an hyperterminal as specified in the blister.
    * If the board needs to be reinitialized with the original firmware, this one is available at https://stm32-c2c.com, see “Restore factory firmware”
    * When the board has been recorded on the https://stm32-c2c.com portal with its voucher, proceed with the EMnify button available on this portal

  - Active cellular SIM card fit in the slot.

    In order to activate the EMnify SIM card:
    * Follow the EMnify Setup Guide available in the Knowledge Base section of https://support.emnify.com

      Note for corporate users: Your card may have already been registered by the person who received the batch.
      You can skip the account creation, and:
      * get your email address added to the list of users of the EMnify corporate account;
      * click on the activation link you will receive by email;
      * login and activate your card from its IccID;
      * create your endpoint.
      See the details in "Enabling SIMs" section and below of the EMnify Setup Guide.

    If you are not sure if the IccID printed on your card is valid, you can cross-check with the "SIM Id (IccID):" value
    displayed on the console during the application startup.
    Alternatively, you can use the AT+QCCID command in the QNavigator on the Brisk card.
 
  - A Cellular access point is required.



@par How to use it ?

In order to make the program work, you must do the following:

 - WARNING: Before opening the project with any toolchain be sure your folder
   installation path is not too in-depth since the toolchain may report errors
   after building.

 - Open the IAR IDE and compile the project (see the release note for detailed 
   information about the version). Alternatively you can use the Keil uVision 
   toolchain (see the release note for detailed information about the version). 
   Alternatively you can use the System Workbench for STM32 (see the release note 
   for detailed information about the version). 

 - Program the firmware on the STM32 board: If you generated a raw binary file, 
   you can copy (or drag and drop) it from Projects\STM32L496G-Discovery\Examples\Cloud\httpclient\EWARM\STM32L496G-Discovery\Exe
   to the USB mass storage location created when you plug the STM32 
   board to your PC. If the host is a Linux PC, the STM32 device can be found in 
   the /media folder with the name e.g. "DIS_L4IOT". For example, if the created mass 
   storage location is "/media/DIS_L4IOT", then the command to program the board 
   with a binary file named "my_firmware.bin" is simply: cp my_firmware.bin 
   /media/DIS_L4IOT. 

   Alternatively, you can program the STM32 board directly through one of the 
   supported development toolchains, or thanks to the STM32 ST-Link Utility.
  
 - Configure the required settings (to be done only once): 
   - When the board is connected to a PC with USB (ST-LINK USB port), 
     open a serial terminal emulator, find the board's COM port and configure it with:
      - 8N1, 115200 bauds, no HW flow control
      - set the line endings to LF or CR-LF (Transmit) and LF (receive).

   - At first boot, enter the required parameters:

     - C2C network configuration (SIM operator access point code, username and password).
       Example:
         with Emnify SIM:  access point: "EM",     username: "", password: ""
         with Eseye SIM:   access point: "ESEYE1", username: "", password: ""


   - After the parameters are configured, it is possible to change them by restarting the board 
     and pushing User button (blue button) when prompted during the initialization.

@par Connectivity test

  - By default the project tries to automatically connect to httpbin.org.
    It tries various HTTP commands (GET, POST, PUT ...).
    The test passes if every HTTP command status is equal to 200.


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
