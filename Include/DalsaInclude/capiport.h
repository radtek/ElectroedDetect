//
// Coreco API - Port functions.
//

#ifndef _CAPIPORT_H_
#define _CAPIPORT_H_

#include <capidef.h>

#define CORPORT_SYSTEM	   0x00     // 0
#define CORPORT_COBRA	   0xFF     // 255
#define CORPORT_PYTHON	   0xFE     // 254
#define CORPORT_VIPERRGB   0xFD     // 253
#define CORPORT_VIPERDIG   0xFC     // 252
#define CORPORT_ICESTORM   0xFB     // 251
#define CORPORT_VIPERQUAD  0xFA     // 250
#define CORPORT_X64AN2     0xF9     // 249   // Old Rebel slot
#define CORPORT_MAMBA      0xF8     // 248
#define CORPORT_BANDIT     0xF7     // 247
#define CORPORT_VIPERCAMLINK  0xF6  // 246
#define CORPORT_BANDITII   0xF5     // 245
#define CORPORT_X64        0xF4     // 244
#define CORPORT_ANACONDA   0xF3     // 243
#define CORPORT_X64AN      0xF2     // 242
#define CORPORT_PC2V			0xF1     // 241
#define CORPORT_PC2C			0xF0     // 240
#define CORPORT_X64LVDS    0xEF     // 239
#define CORPORT_BOARD_NAME 0xEE     // 238: Driver Template, used by example
#define CORPORT_PC2V_NS		0xED     // 237
#define CORPORT_X64CHL     0xEC     // 236
#define CORPORT_NEXUS      0xEB     // 235
#define CORPORT_ARIES      0xEA     // 234
#define CORPORT_X64NS      0xE9     // 233
#define CORPORT_X64IPRO    0xE8     // 232
#define CORPORT_ANACONDALVDS  0xE7  // 231
#define CORPORT_X64ANX2    0xE6     // 230
#define CORPORT_X64IPROE   0xE5     // 229
#define CORPORT_XRICL      0xE4     // 228
#define CORPORT_XRILVDS    0xE3     // 227
#define CORPORT_X64INET    0xE2     // 226
#define CORPORT_NEXUSCV    0xE1     // 225
#define CORPORT_CAM_GIGE   0xE0     // 224
#define CORPORT_X64CZM     0xDF     // 223
#define CORPORT_X64IPROE4X 0xDE     // 222
#define CORPORT_PC2COMP    0xDD     // 221
#define CORPORT_XCELERAL4X 0xDC     // 220
#define CORPORT_XCELERAV4XCL		0xDB     // 219 Obsolete
#define CORPORT_BUNGEECLVX4		0xDB     // 219
#define CORPORT_XCELERAV4XLVDS	0xDA     // 218
#define CORPORT_XCELERAPX4LVDS	0xD9     // 217
#define CORPORT_XCELERAXRICL		0xD8     // 216
#define CORPORT_XCELERAXRILVDS	0xD7     // 215
#define CORPORT_X64ANLX1         0xD6     // 214
#define CORPORT_XCELERALX1CL		0xD5     // 213
#define CORPORT_XCELERAHSPX8		0xD4     // 212
#define CORPORT_XCELERACLpPX8		0xD3     // 211
#define CORPORT_BUNGEECLPX4			0xD2     // 210
#define CORPORT_BUNGEECLPX4OPTO		0xD1     // 209
#define CORPORT_CLPROTOCOL          0xD0     // 208
#define CORPORT_XCELERACLHSPX8		0xCF     // 207
#define CORPORT_BUNGEELVDSLX1			0xCE     // 206
#define CORPORT_XTIUMCLHSPX8		   0xCD		// 205
#define CORPORT_XTIUMCLPX4			   0xCC     // 204
#define CORPORT_XTIUMCXPPX8		   0xCB     // 203
#define CORPORT_XTIUMCLHSPX4		   0xCA		// 202
#define CORPORT_XTIUMSFPMPX4			0xC9		// 201
#define CORPORT_XTIUMSFPXPX4			0xC8		// 200
#define CORPORT_XTIUMCLMX4			   0xC7     // 199
#define CORPORT_XTIUMCLCZM			   0xC6     // 198

// NOTE: These definitions are now obsolete. They are only kept for backward
//       compatibility. Use the CORPORT_xxx definitions above instead.
#define CORBOARD_SYSTEM       CORPORT_SYSTEM
#define CORBOARD_COBRA        CORPORT_COBRA
#define CORBOARD_PYTHON       CORPORT_PYTHON
#define CORBOARD_VIPERRGB     CORPORT_VIPERRGB
#define CORBOARD_VIPERDIG     CORPORT_VIPERDIG
#define CORBOARD_ICESTORM     CORPORT_ICESTORM
#define CORBOARD_VIPERQUAD    CORPORT_VIPERQUAD
#define CORBOARD_MAMBA        CORPORT_MAMBA
#define CORBOARD_VIPERCAMLINK CORPORT_VIPERCAMLINK
//
// DO NOT ADD ANY MORE DEFINES HERE. THEY ARE OBSOLETE AND ARE NOT USED ANYMORE.
//

//
// Entry in this table is only needed if driver is to be supported with a Sapera
// version < 5.00. If only Sapera versions 5.00 and greater support is needed, do not
// add the CXM name below.
//

#if !defined(POSIX_HOSTPC)

#define GET_DRIVER_FILE_NAME_AND_PROC(module,proc)\
		case CORPORT_COBRA:\
			module= "CORCOBRA.CXM";\
			proc= "CorCobraGetControl";\
		break;\
		case CORPORT_PYTHON:\
			module= "CORPYTH.CXM";\
			proc= "CorPythGetControl";\
		break;\
		case CORPORT_VIPERRGB:\
			module= "CORVRGB.CXM";\
			proc= "CorVRgbGetControl";\
		break;\
		case CORPORT_VIPERDIG:\
			module= "CORVDIG.CXM";\
			proc= "CorVDigGetControl";\
		break;\
		case CORPORT_VIPERCAMLINK:\
			module= "CORVCAMLINK.CXM";\
			proc= "CorVCamLinkGetControl";\
		break;\
		case CORPORT_VIPERQUAD:\
			module= "CORVQUAD.CXM";\
			proc= "CorVQuadGetControl";\
		break;\
		case CORPORT_ICESTORM:\
			module= "CORICE.CXM";\
			proc= "CorIceGetControl";\
		break;\
		case CORPORT_MAMBA:\
			module= "CORMAMBA.CXM";\
			proc= "CorMambaGetControl";\
		break;\
		case CORPORT_BANDITII:\
			module= "CORBDII.CXM";\
			proc= "CorBdIIGetControl";\
		break;\
		case CORPORT_X64:\
			module= "CORX64x.CXM";\
			proc= "CorX64GetControl";\
		break;\
		case CORPORT_X64AN:\
			module= "CORX64ANx.CXM";\
			proc= "";\
		break;\
		case CORPORT_PC2V:\
			module= "CORPC2Vx.CXM";\
			proc= "";\
		break;\
		case CORPORT_PC2V_NS:\
			module= "CORNSPx.CXM";\
			proc= "";\
		break;\
		case CORPORT_PC2C:\
			module= "CORPC2Cx.CXM";\
			proc= "";\
		break;\
		case CORPORT_ANACONDA:\
			module= "CORANCx.CXM";\
			proc= "";\
		break;\
		case CORPORT_X64LVDS:\
			module= "CORX64LVDSx.CXM";\
			proc= "CorX64LVDSGetControl";\
		break;\
		case CORPORT_X64NS:\
			module= "CORX64NSx.CXM";\
			proc= "";\
		break;\
		case CORPORT_X64CHL:\
			module= "CORX64CHLx.CXM";\
			proc= "CorX64CHLGetControl";\
		break;\
		case CORPORT_NEXUS:\
			module= "CORNexusX.CXM";\
			proc= "";\
		break;\
		case CORPORT_X64IPRO:\
			module= "CORX64IPROx.CXM";\
			proc= "";\
		break;\
		case CORPORT_ANACONDALVDS:\
			module= "CORANCLVDSx.CXM";\
			proc= "";\
		break;\
		case CORPORT_X64IPROE:\
			module= "CORX64IPROEx.CXM";\
			proc= "";\
		break;\
		case CORPORT_XRICL:\
			module= "CORXRICLx.CXM";\
			proc= "";\
		break;\
		case CORPORT_XRILVDS:\
			module= "CORXRILVDSx.CXM";\
			proc= "";\
		break;\
		case CORPORT_X64INET:\
			module= "CORX64INETx.CXM";\
			proc= "";\
		break;\
		case CORPORT_NEXUSCV:\
			module= "CORNexusCVX.CXM";\
			proc= "";\
		break;\
		case CORPORT_CAM_GIGE:\
			module= "CORCamGigeX.CXM";\
			proc= "";\
		break;\
		case CORPORT_X64IPROE4X:\
			module= "CORX64IPROE4Xx.CXM";\
			proc= "";\
		break;\
		case CORPORT_PC2COMP:\
			module= "CORPC2COMPX.CXM";\
			proc= "";\
		break;\

#else
#define GET_DRIVER_FILE_NAME_AND_PROC(module,proc)\
		case CORPORT_BANDITII:\
			module= "libCorBdIICXM.so";\
			proc= "CorBdIIGetControl";\
		break;\
		case CORPORT_X64:\
			module= "libCorX64xCXM.so";\
			proc= "CorX64GetControl";\
		break;\
		case CORPORT_X64AN:\
			module= "libCorX64ANxCXM.so";\
			proc= "";\
		break;\
		case CORPORT_PC2V:\
			module= "libCorPc2vxCXM.so";\
			proc= "";\
		break;\
		case CORPORT_PC2V_NS:\
			module= "libCorPc2vNSPxCXM.so";\
			proc= "";\
		break;\
		case CORPORT_PC2C:\
			module= "libCorPc2cxCXM.so";\
			proc= "";\
		break;\
		case CORPORT_ANACONDA:\
			module= "libCorAncxCXM.so";\
			proc= "";\
		break;\
		case CORPORT_X64LVDS:\
			module= "libCorX64LVDSxCXM.so";\
			proc= "CorX64LVDSGetControl";\
		break;\
		case CORPORT_X64NS:\
			module= "libCor64NSxCXM.so";\
			proc= "";\
		break;\
		case CORPORT_X64CHL:\
			module= "libCorX64CHLxCXM.so";\
			proc= "CorX64CHLGetControl";\
		break;\
		case CORPORT_NEXUS:\
			module= "libCorNexusxCXM.so";\
			proc= "";\
		break;\
		case CORPORT_X64IPRO:\
			module= "libCorX64iProxCXM.so";\
			proc= "";\
		break;\
		case CORPORT_ANACONDALVDS:\
			module= "libCorAncLVDSxCXM.so";\
			proc= "";\
		break;\
		case CORPORT_X64IPROE:\
			module= "libCorX64iProExCXM.so";\
			proc= "";\
		break;\
		case CORPORT_XRICL:\
			module= "libCorXRICLxCXM.so";\
			proc= "";\
		break;\
		case CORPORT_XRILVDS:\
			module= "libCorXRILVDSxCXM.so";\
			proc= "";\
		break;\
		case CORPORT_X64INET:\
			module= "libCorX64INETxCXM.so";\
			proc= "";\
		break;\
		case CORPORT_NEXUSCV:\
			module= "libCorNexusCVxCXM.so";\
			proc= "";\
		break;\
		case CORPORT_CAM_GIGE:\
			module= "CORCamGigeXCXM.so";\
			proc= "";\
		break;\
		case CORPORT_X64IPROE4X:\
			module= "libCorX64iProE4xxCXM.so";\
			proc= "";\
		break;\
		case CORPORT_XCELERAHSPX8:\
			module= "libCorX64XceleraHSPX8xCXM.so";\
			proc= "";\
		break;\

#endif

#ifdef __cplusplus
extern "C" {
#endif

CORSTATUS CORAPIFUNC CorPortOpen (CORSERVER hServer, CORSERVER hDestServer, UINT32 porttype, PSTR params);
CORSTATUS CORAPIFUNC CorPortClose(CORSERVER hServer, CORSERVER hDestServer);

#ifdef __cplusplus
}
#endif

#endif   // _CAPIPORT_H_
