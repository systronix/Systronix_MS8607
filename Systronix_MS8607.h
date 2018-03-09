#ifndef SYSTRONIX_MS8607_h
#define SYSTRONIX_MS8607_h


/******************************************************************************/
/*!
	@file		SYSTRONIX_MS8607.h
	
	@author		B Boyes (Systronix Inc)
    @license	BSD (see license.txt)	
    @section	HISTORY

	v1.00	2018 Mar 08	Dummy file so Arduino compiler doesn't whine

*/
/******************************************************************************/

/** TODO LIST



**/

/** --------  Description ------------------------------------------------------



------------------------------------------------------------------------------*/


/** --------  Device Addressing --------

-------------------------------------*/

#include <Arduino.h>

#if defined (__MK20DX256__) || defined (__MK20DX128__) 	// Teensy 3.1 or 3.2 || Teensy 3.0
#include <i2c_t3.h>		
#else
#include <Wire.h>	// for AVR I2C library
#endif

#define		SUCCESS	0
#define		FAIL	(~SUCCESS)
#define		ABSENT	0xFD

#define		MS8607_BASE_MIN 	0x00					// 7-bit address not including R/W bit
#define		MS8607_BASE_MAX 	0x00					// 7-bit address not including R/W bit

#define		WR_INCOMPLETE		11
#define		SILLY_PROGRAMMER	12


/** --------  Register Addresses --------

*/


class Systronix_MS8607
{
	protected:
		uint8_t		_base;								// base address for this instance; four possible values
														// private copies of these register values
		void		tally_transaction (uint8_t);		// maintains the i2c_t3 error counters
		
	public:
		// Instance-specific properties


		uint8_t		setup (uint8_t base);				// constructor
		void		begin (void);
		uint8_t		init (uint16_t);					// device present and communicating detector
		uint8_t		base_get(void);

	private:

};


#endif /* SYSTRONIX_MS8607_h */
