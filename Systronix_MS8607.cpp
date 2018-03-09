/**

	See comments in header file 

*/

#include <Systronix_MS8607.h>	

//---------------------------< S E T U P >--------------------------------------------------------------------
/*!
	@brief  Instantiates a new class to use the given base address
	@todo	Test base address for legal range 
			Add constructor(void) for default address 
*/

uint8_t Systronix_MS8607::setup(uint8_t base)
	{
	if ((MS8607_BASE_MIN > base) || (MS8607_BASE_MAX < base))
		{
		tally_transaction (SILLY_PROGRAMMER);
		return FAIL;
		}

	_base = base;
	return SUCCESS;
	}


//---------------------------< B E G I N >--------------------------------------------------------------------
//
// TODO: add support for Wire1, Wire2, ... alternate pins, etc
//

void Systronix_MS8607::begin(void)
	{
	Wire.begin();	// join I2C as master
	}


//---------------------------< B A S E _ G E T >--------------------------------------------------------------
//
//	return the I2C base address for this instance
//

uint8_t Systronix_MS8607::base_get(void)
	{
	return _base;
	}


//---------------------------< I N I T >----------------------------------------------------------------------
//
// Attempts to write configuration register.  If successful, sets error.exists true, else false.
//

uint8_t Systronix_MS8607::init (uint16_t config)
	{
	error.exists = true;								// here, assume that the device exists

	return SUCCESS;
	}


void Systronix_MS8607::tally_transaction (uint8_t value)
	{
	if (value && (error.total_error_count < UINT64_MAX))
		error.total_error_count++; 			// every time here incr total error count

	error.error_val = value;

	switch (value)
		{
		case SUCCESS:
			if (error.successful_count < UINT64_MAX)
				error.successful_count++;
			break;
		case 1:								// i2c_t3 and Wire: data too long from endTransmission() (rx/tx buffers are 259 bytes - slave addr + 2 cmd bytes + 256 data)
			error.data_len_error_count++;
			break;
#if defined I2C_T3_H
		case I2C_TIMEOUT:
			error.timeout_count++;			// 4 from i2c_t3; timeout from call to status() (read)
#else
		case 4:
			error.other_error_count++;		// i2c_t3 and Wire: from endTransmission() "other error"
#endif
			break;
		case 2:								// i2c_t3 and Wire: from endTransmission()
		case I2C_ADDR_NAK:					// 5 from i2c_t3
			error.rcv_addr_nack_count++;
			break;
		case 3:								// i2c_t3 and Wire: from endTransmission()
		case I2C_DATA_NAK:					// 6 from i2c_t3
			error.rcv_data_nack_count++;
			break;
		case I2C_ARB_LOST:					// 7 from i2c_t3; arbitration lost from call to status() (read)
			error.arbitration_lost_count++;
			break;
		case I2C_BUF_OVF:
			error.buffer_overflow_count++;
			break;
		case I2C_SLAVE_TX:
		case I2C_SLAVE_RX:
			error.other_error_count++;		// 9 & 10 from i2c_t3; these are not errors, I think
			break;
		case WR_INCOMPLETE:					// 11; Wire.write failed to write all of the data to tx_buffer
			error.incomplete_write_count++;
			break;
		case SILLY_PROGRAMMER:				// 12
			error.silly_programmer_error++;
			break;
		default:
			error.unknown_error_count++;
			break;
		}
	}
