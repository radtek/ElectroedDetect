#ifndef LIBMODBUS_TCP_H
#define LIBMODBUS_TCP_H

#include "LibModbus/LibModbus-TCP.h"

#include <winsock2.h>
#if !defined(ECONNRESET)
#define ECONNRESET   WSAECONNRESET
#endif
#if !defined(ECONNREFUSED)
#define ECONNREFUSED WSAECONNREFUSED
#endif
#if !defined(ETIMEDOUT)
#define ETIMEDOUT    WSAETIMEDOUT
#endif
#if !defined(ENOPROTOOPT)
#define ENOPROTOOPT  WSAENOPROTOOPT
#endif
#if !defined(EINPROGRESS)
#define EINPROGRESS  WSAEINPROGRESS
#endif

#define MODBUS_TCP_DEFAULT_PORT   502
#define MODBUS_TCP_SLAVE          0xFF

/* Modbus_Application_Protocol_V1_1b.pdf Chapter 4 Section 1 Page 5
* TCP MODBUS ADU = 253 bytes + MBAP (7 bytes) = 260 bytes*/
#define MODBUS_TCP_MAX_ADU_LENGTH  260

DLLAPI int STDCALL modbus_tcp_init_win();
DLLAPI void STDCALL modbus_tcp_uninit_win();

DLLAPI modbus_t* STDCALL modbus_new_tcp(const char *ip_address, int port);
DLLAPI int STDCALL modbus_tcp_listen(modbus_t *ctx, int nb_connection);
DLLAPI int STDCALL modbus_tcp_accept(modbus_t *ctx, int *s);

DLLAPI modbus_t* STDCALL modbus_new_tcp_pi(const char *node, const char *service);
DLLAPI int STDCALL modbus_tcp_pi_listen(modbus_t *ctx, int nb_connection);
DLLAPI int STDCALL modbus_tcp_pi_accept(modbus_t *ctx, int *s);

#ifdef UPPROCESS
#ifndef LIBMODBUS_IMPLEMENT
#pragma comment(lib, "LibModbus.lib")
#endif
#endif

#endif /* LIBMODBUS_TCP_H */