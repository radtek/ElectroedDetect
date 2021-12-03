//
// Coreco API - PCI functions.
//

#ifndef _CAPIPCI_H_
#define _CAPIPCI_H_

#include <capidef.h>

#define CORPCI_VENDOR_ID						0x00
#define CORPCI_DEVICE_ID						0x02
#define CORPCI_COMMAN_REG						0x04
#define CORPCI_STATUS_REG						0x06
#define CORPCI_REVISION_ID						0x08
#define CORPCI_CLASS_CODE						0x09
#define CORPCI_CACHE_LINE_SIZE				0x0C
#define CORPCI_LATENCY_TIMER					0x0D
#define CORPCI_HEADER_TYPE						0x0E
#define CORPCI_BIST								0x0F

#define CORPCI_REGISTERS						0x10

#define CORPCI_CARDBUS_CIS_POINTER			0x28
#define CORPCI_SUBSYSTEM_VENDOR_ID			0x2C
#define CORPCI_SUBSYSTEM_ID					0x2E
#define CORPCI_EXPANSION_ROM_BASE_ADDRESS	0x30
#define CORPCI_RESERVED_1						0x34
#define CORPCI_RESERVED_2						0x38
#define CORPCI_INTERRUPT_LINE					0x3C
#define CORPCI_INTERRUPT_PIN					0x3D
#define CORPCI_MIN_GRANT						0x3E
#define CORPCI_MAX_LATENCY						0x3F

#ifdef __cplusplus
extern "C" {
#endif

CORSTATUS CORAPIFUNC CorPciGetInfo      (CORSERVER hServer, PUINT16 version, PUINT8 mechanism, PUINT8 nbuses);
CORSTATUS CORAPIFUNC CorPciSetBusNumber (CORSERVER hServer, PUINT8 nbuses);
CORSTATUS CORAPIFUNC CorPciFindDevice   (CORSERVER hServer, UINT16 vendorid, UINT16 deviceid, UINT16 index, CORPCIDEVICE *hPciDevice);
CORSTATUS CORAPIFUNC CorPciNewDevice    (CORSERVER hServer, UINT8  bus, UINT8  slot, UINT8  func, CORPCIDEVICE *hPciDevice);
CORSTATUS CORAPIFUNC CorPciFindClassCode(CORSERVER hServer, UINT32 classcode, UINT16 index, CORPCIDEVICE *hPciDevice);
CORSTATUS CORAPIFUNC CorPciGetVGADevice (CORSERVER hServer, UINT16 index, CORPCIDEVICE *hPciDevice);
CORSTATUS CORAPIFUNC CorPciRelease   (CORPCIDEVICE hPciDevice);

CORSTATUS CORAPIFUNC CorPciGetByte   (CORPCIDEVICE hPciDevice, UINT16 reg, PUINT8 data);
CORSTATUS CORAPIFUNC CorPciGetWord	 (CORPCIDEVICE hPciDevice, UINT16 reg, PUINT16 data);
CORSTATUS CORAPIFUNC CorPciGetDword  (CORPCIDEVICE hPciDevice, UINT16 reg, PUINT32 data);
CORSTATUS CORAPIFUNC CorPciPutByte	 (CORPCIDEVICE hPciDevice, UINT16 reg, UINT8  data);
CORSTATUS CORAPIFUNC CorPciPutWord	 (CORPCIDEVICE hPciDevice, UINT16 reg, UINT16 data);
CORSTATUS CORAPIFUNC CorPciPutDword  (CORPCIDEVICE hPciDevice, UINT16 reg, UINT32 data);
CORSTATUS CORAPIFUNC CorPciGetAddrLen(CORPCIDEVICE hPciDevice, UINT8  reg, PSIZE_T len);
CORSTATUS CORAPIFUNC CorPciGetData   (CORPCIDEVICE hPciDevice, UINT16 basereg, UINT16 nbytes, void* data);

#ifdef __cplusplus
}
#endif

#endif   // _CAPIPCI_H_
