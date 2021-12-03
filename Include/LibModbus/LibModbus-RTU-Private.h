#ifndef LIBMODBUS_RTU_PRIVATE_H
#define LIBMODBUS_RTU_PRIVATE_H

#include "stdint.h"
#include <windows.h>

#define _MODBUS_RTU_HEADER_LENGTH      1
#define _MODBUS_RTU_PRESET_REQ_LENGTH  6
#define _MODBUS_RTU_PRESET_RSP_LENGTH  2

#define _MODBUS_RTU_CHECKSUM_LENGTH    2

/* WIN32: struct containing serial handle and a receive buffer */
#define PY_BUF_SIZE 512
struct win32_ser {
	/* File handle */
	HANDLE fd;
	/* Receive buffer */
	uint8_t buf[PY_BUF_SIZE];
	/* Received chars */
	DWORD n_bytes;
};

typedef struct _modbus_rtu {
	/* Device: "/dev/ttyS0", "/dev/ttyUSB0" or "/dev/tty.USA19*" on Mac OS X. */
	char *device;
	/* Bauds: 9600, 19200, 57600, 115200, etc */
	int baud;
	/* Data bit */
	uint8_t data_bit;
	/* Stop bit */
	uint8_t stop_bit;
	/* Parity: 'N', 'O', 'E' */
	char parity;
#if defined(_WIN32)
	struct win32_ser w_ser;
	DCB old_dcb;
#else
	/* Save old termios settings */
	struct termios old_tios;
#endif
#if HAVE_DECL_TIOCSRS485
	int serial_mode;
#endif
#if HAVE_DECL_TIOCM_RTS
	int rts;
	int rts_delay;
	int onebyte_time;
	void(*set_rts) (modbus_t *ctx, int on);
#endif
	/* To handle many slaves on the same link */
	int confirmation_to_ignore;
} modbus_rtu_t;

#endif /* LIBMODBUS_RTU_PRIVATE_H */
