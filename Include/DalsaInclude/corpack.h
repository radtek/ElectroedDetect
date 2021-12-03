//
// Coreco format packing/unpacking macros.
//

#ifndef _CORPACK_H_
#define _CORPACK_H_

#include <corenv.h>

/****************************************************************************
*	Format Packing Macros
****************************************************************************/
#define CORDATA_PACK_MONO8(pData, pBuf) \
	{\
	*(UINT8 *)(pBuf) = (UINT8) (pData)->mono; \
	}

#define CORDATA_PACK_MONO16(pData, pBuf) \
	{\
	*(UINT16 *)(pBuf) = (UINT16) (pData)->mono; \
	}

#define CORDATA_PACK_MONO32(pData, pBuf) \
	{\
	*(UINT32 *)(pBuf) = (UINT32) (pData)->mono; \
	}

#define CORDATA_PACK_RGB5551(pData, pBuf) \
	{\
	*(UINT16 *)(pBuf)  = (UINT16) (((pData)->rgb.red   & 0x1F) << 10); \
	*(UINT16 *)(pBuf) |= (UINT16) (((pData)->rgb.green & 0x1F) <<  5); \
	*(UINT16 *)(pBuf) |= (UINT16) (((pData)->rgb.blue  & 0x1F)      ); \
	}

#define CORDATA_PACK_RGB565(pData, pBuf) \
	{\
	*(UINT16 *)(pBuf)  = (UINT16) (((pData)->rgb.red   & 0x1F) << 11); \
	*(UINT16 *)(pBuf) |= (UINT16) (((pData)->rgb.green & 0x3F) <<  5); \
	*(UINT16 *)(pBuf) |= (UINT16) (((pData)->rgb.blue  & 0x1F)      ); \
	}

#define CORDATA_PACK_RGB888(pData, pBuf) \
	{\
	*((UINT8 *)(pBuf)+2) = (UINT8) (pData)->rgb.red;   \
	*((UINT8 *)(pBuf)+1) = (UINT8) (pData)->rgb.green; \
	*((UINT8 *)(pBuf)  ) = (UINT8) (pData)->rgb.blue;  \
	}

#define CORDATA_PACK_RGBR888(pData, pBuf) \
	{\
	*((UINT8 *)(pBuf)  ) = (UINT8) (pData)->rgb.red;   \
	*((UINT8 *)(pBuf)+1) = (UINT8) (pData)->rgb.green; \
	*((UINT8 *)(pBuf)+2) = (UINT8) (pData)->rgb.blue;  \
	}

#define CORDATA_PACK_RGB8888(pData, pBuf) \
	{\
	*((UINT8 *)(pBuf)+3) = (UINT8) (pData)->rgba.alpha; \
	*((UINT8 *)(pBuf)+2) = (UINT8) (pData)->rgba.red;   \
	*((UINT8 *)(pBuf)+1) = (UINT8) (pData)->rgba.green; \
	*((UINT8 *)(pBuf)  ) = (UINT8) (pData)->rgba.blue;  \
	}

#define CORDATA_PACK_RGB101010(pData, pBuf) \
	{\
	*(UINT32 *)(pBuf)  = (UINT32) (((pData)->rgb.red & 0x3FF) << 20); \
	*(UINT32 *)(pBuf) |= (UINT32) (((pData)->rgb.green & 0x3FF) << 10); \
	*(UINT32 *)(pBuf) |= (UINT32) (((pData)->rgb.blue & 0x3FF)      ); \
	}

#define CORDATA_PACK_LAB101010(pData, pBuf) \
	{\
	*(UINT32 *)(pBuf)  = (UINT32) (((pData)->lab.l & 0x3FF) << 20); \
	*(UINT32 *)(pBuf) |= (UINT32) (((pData)->lab.a & 0x3FF) << 10); \
	*(UINT32 *)(pBuf) |= (UINT32) (((pData)->lab.b & 0x3FF)      ); \
	}

#define CORDATA_PACK_LAB888(pData, pBuf) \
	{\
	*((UINT8 *)(pBuf)+2) = (UINT8) (pData)->lab.l;   \
	*((UINT8 *)(pBuf)+1) = (UINT8) (pData)->lab.a; \
	*((UINT8 *)(pBuf)  ) = (UINT8) (pData)->lab.b;  \
	}

#define CORDATA_PACK_LAB8888(pData, pBuf) \
	{\
	*((UINT8 *)(pBuf)+2) = (UINT8) (pData)->lab.l;   \
	*((UINT8 *)(pBuf)+1) = (UINT8) (pData)->lab.a; \
	*((UINT8 *)(pBuf)  ) = (UINT8) (pData)->lab.b;  \
	}

#define CORDATA_PACK_RGB161616(pData, pBuf) \
	{\
	*((UINT16 *)(pBuf)+2) = (UINT16) (pData)->rgb.red;   \
	*((UINT16 *)(pBuf)+1) = (UINT16) (pData)->rgb.green; \
	*((UINT16 *)(pBuf)  ) = (UINT16) (pData)->rgb.blue;  \
	}

#define CORDATA_PACK_RGB16161616(pData, pBuf) \
	{\
   *((UINT16 *)(pBuf)+3) = (pData)->rgba.alpha;   \
	*((UINT16 *)(pBuf)+2) = (pData)->rgba.red;   \
	*((UINT16 *)(pBuf)+1) = (pData)->rgba.green; \
	*((UINT16 *)(pBuf)  ) = (pData)->rgba.blue;  \
	}

#define CORDATA_PACK_LAB16161616(pData, pBuf) \
	{\
   *((UINT16 *)(pBuf)+3) = (pData)->laba.alpha;   \
	*((UINT16 *)(pBuf)+2) = (pData)->laba.l;   \
	*((UINT16 *)(pBuf)+1) = (pData)->laba.a; \
	*((UINT16 *)(pBuf)  ) = (pData)->laba.b;  \
	}

#define CORDATA_PACK_FLOAT(pData, pBuf) \
	{\
	*(FLOAT *)(pBuf) = (pData)->flt; \
	}

#define CORDATA_PACK_COMPLEX(pData, pBuf) \
	{\
	*((FLOAT *)(pBuf)  ) = (pData)->cplx.real; \
	*((FLOAT *)(pBuf)+1) = (pData)->cplx.imag; \
	}

#define CORDATA_PACK_POINT(pData, pBuf) \
	{\
	*((INT32 *)(pBuf)  ) = (pData)->point.x; \
	*((INT32 *)(pBuf)+1) = (pData)->point.y; \
	}

#define CORDATA_PACK_FPOINT(pData, pBuf) \
	{\
	*((FLOAT *)(pBuf)  ) = (pData)->fpoint.x; \
	*((FLOAT *)(pBuf)+1) = (pData)->fpoint.y; \
	}

#define CORDATA_PACK_HSI(pData, pBuf) \
	{\
	*((UINT8 *)(pBuf)+2) = (UINT8) (pData)->hsi.h; \
	*((UINT8 *)(pBuf)+1) = (UINT8) (pData)->hsi.s; \
	*((UINT8 *)(pBuf)  ) = (UINT8) (pData)->hsi.i; \
	}

#define CORDATA_PACK_LAB(pData, pBuf) \
	{\
	*((UINT8 *)(pBuf)+2) = (UINT8) (pData)->lab.l; \
	*((UINT8 *)(pBuf)+1) = (UINT8) (pData)->lab.a; \
	*((UINT8 *)(pBuf)  ) = (UINT8) (pData)->lab.b; \
	}

#define CORDATA_PACK_HSV(pData, pBuf) \
	{\
	*((UINT8 *)(pBuf)+2) = (UINT8) (pData)->hsv.h; \
	*((UINT8 *)(pBuf)+1) = (UINT8) (pData)->hsv.s; \
	*((UINT8 *)(pBuf)  ) = (UINT8) (pData)->hsv.v; \
	}

#define CORDATA_PACK_YUV(pData, pBuf) \
	{\
	*((UINT8 *)(pBuf)+2) = (UINT8) (pData)->yuv.y; \
	*((UINT8 *)(pBuf)+1) = (UINT8) (pData)->yuv.u; \
	*((UINT8 *)(pBuf)  ) = (UINT8) (pData)->yuv.v; \
	}

#define CORDATA_PACK_UYVY(pData, pBuf, xPos) \
	{\
	*((UINT8 *)(pBuf)  ) = (UINT8) (pData)->yuv.u; \
	*((UINT8 *)(pBuf)+2) = (UINT8) (pData)->yuv.v; \
	*((UINT8 *)(pBuf)+1 + (((xPos) & 1) ? 2 : 0)) = (UINT8) (pData)->yuv.y; \
	}

#define CORDATA_PACK_YUY2(pData, pBuf, xPos) \
	{\
	*((UINT8 *)(pBuf)+1) = (UINT8) (pData)->yuv.u; \
	*((UINT8 *)(pBuf)+3) = (UINT8) (pData)->yuv.v; \
	*((UINT8 *)(pBuf) + (((xPos) & 1) ? 2 : 0)) = (UINT8) (pData)->yuv.y; \
	}

#define CORDATA_PACK_Y411(pData, pBuf, xPos) \
	{\
	*((UINT8 *)(pBuf)  ) = (UINT8) (pData)->yuv.u; \
	*((UINT8 *)(pBuf)+3) = (UINT8) (pData)->yuv.v; \
	*((UINT8 *)(pBuf)+1 + (xPos) + (((xPos) & 2) ? 1 : 0))= (UINT8) (pData)->yuv.y; \
	}

#define CORDATA_PACK_IYU1(pData, pBuf)		CORDATA_PACK_Y411(pData, pBuf, xPos)

#define CORDATA_PACK_IYU2(pData, pBuf) \
	{\
	*((UINT8 *)(pBuf)  ) = (UINT8) (pData)->yuv.u; \
	*((UINT8 *)(pBuf)+1) = (UINT8) (pData)->yuv.y; \
	*((UINT8 *)(pBuf)+2) = (UINT8) (pData)->yuv.v; \
	}

#define CORDATA_PACK_BICOLOR88_RG(pData, pBuf) \
   {\
	*((UINT8 *)(pBuf)  ) = (UINT8) (pData)->rgb.red;\
	*((UINT8 *)(pBuf)+1) = (UINT8) (pData)->rgb.green;\
   }

#define CORDATA_PACK_BICOLOR88_BG(pData, pBuf) \
   {\
	*((UINT8 *)(pBuf)  ) = (UINT8) (pData)->rgb.blue;\
	*((UINT8 *)(pBuf)+1) = (UINT8) (pData)->rgb.green;\
   }

#define CORDATA_PACK_BICOLOR1616_RG(pData, pBuf) \
   {\
	*((UINT16 *)(pBuf)  ) = (UINT16) (pData)->rgb.red;\
	*((UINT16 *)(pBuf)+1) = (UINT16) (pData)->rgb.green;\
   }

#define CORDATA_PACK_BICOLOR1616_BG(pData, pBuf) \
   {\
	*((UINT16 *)(pBuf)  ) = (UINT16) (pData)->rgb.blue;\
	*((UINT16 *)(pBuf)+1) = (UINT16) (pData)->rgb.green;\
   }

#define CORDATA_PACK_RGB888_MONO8(pData, pBuf) \
	{\
	*((UINT8 *)(pBuf)+3) = (UINT8) (pData)->rgba.alpha;   \
	*((UINT8 *)(pBuf)+2) = (UINT8) (pData)->rgba.red;   \
	*((UINT8 *)(pBuf)+1) = (UINT8) (pData)->rgba.green; \
	*((UINT8 *)(pBuf)  ) = (UINT8) (pData)->rgba.blue;  \
	}

#define CORDATA_PACK_RGB161616_MONO16(pData, pBuf) \
	{\
	*((UINT16 *)(pBuf)+3) = (UINT16) (pData)->rgba.alpha; \
	*((UINT16 *)(pBuf)+2) = (UINT16) (pData)->rgba.red;   \
	*((UINT16 *)(pBuf)+1) = (UINT16) (pData)->rgba.green; \
	*((UINT16 *)(pBuf)  ) = (UINT16) (pData)->rgba.blue;  \
	}

/****************************************************************************
*	Format Unpacking Macros
****************************************************************************/
#define CORDATA_UNPACK_MONO8_U(pBuf, pData) \
	{\
	(pData)->mono = (INT32) *(UINT8 *)(pBuf); \
	}

#define CORDATA_UNPACK_MONO8_S(pBuf, pData) \
	{\
	(pData)->mono = (INT32) *(INT8 *)(pBuf);\
	}

#define CORDATA_UNPACK_MONO16_U(pBuf, pData) \
	{\
	(pData)->mono = (INT32) *(UINT16 *)(pBuf);\
	}

#define CORDATA_UNPACK_MONO16_S(pBuf, pData) \
	{\
	(pData)->mono = (INT32) *(INT16 *)(pBuf);\
	}

#define CORDATA_UNPACK_MONO32_U(pBuf, pData) \
	{\
	(pData)->mono = (INT32) *(UINT32 *)(pBuf);\
	}

#define CORDATA_UNPACK_MONO32_S(pBuf, pData) \
	{\
	(pData)->mono = (INT32) *(INT32 *)(pBuf);\
	}

#define CORDATA_UNPACK_RGB5551(pBuf, pData) \
	{\
	(pData)->rgb.red  = (INT32) (*(UINT16 *)(pBuf) >> 10) & 0x1F; \
	(pData)->rgb.green= (INT32) (*(UINT16 *)(pBuf) >>  5) & 0x1F; \
	(pData)->rgb.blue = (INT32) (*(UINT16 *)(pBuf)      ) & 0x1F; \
	}

#define CORDATA_UNPACK_RGB565(pBuf, pData) \
	{\
	(pData)->rgb.red  = (INT32) (*(UINT16 *)(pBuf) >> 11) & 0x1F; \
	(pData)->rgb.green= (INT32) (*(UINT16 *)(pBuf) >>  5) & 0x3F; \
	(pData)->rgb.blue = (INT32) (*(UINT16 *)(pBuf)      ) & 0x1F; \
	}

#define CORDATA_UNPACK_RGB888(pBuf, pData) \
	{\
	(pData)->rgb.red  = (INT32) *((UINT8 *)(pBuf)+2); \
	(pData)->rgb.green= (INT32) *((UINT8 *)(pBuf)+1); \
	(pData)->rgb.blue = (INT32) *((UINT8 *)(pBuf)  ); \
	}

#define CORDATA_UNPACK_RGBR888(pBuf, pData) \
	{\
	(pData)->rgb.red  = (INT32) *((UINT8 *)(pBuf)  ); \
	(pData)->rgb.green= (INT32) *((UINT8 *)(pBuf)+1); \
	(pData)->rgb.blue = (INT32) *((UINT8 *)(pBuf)+2); \
	}

#define CORDATA_UNPACK_RGB8888(pBuf, pData) \
	{\
	(pData)->rgba.alpha = (INT32) *((UINT8 *)(pBuf)+3); \
	(pData)->rgba.red   = (INT32) *((UINT8 *)(pBuf)+2); \
	(pData)->rgba.green = (INT32) *((UINT8 *)(pBuf)+1); \
	(pData)->rgba.blue  = (INT32) *((UINT8 *)(pBuf));   \
	}

#define CORDATA_UNPACK_RGB101010(pBuf, pData) \
	{\
	(pData)->rgb.red  = (INT32) (*(UINT32 *)(pBuf) >> 20) & 0x3FF; \
	(pData)->rgb.green= (INT32) (*(UINT32 *)(pBuf) >> 10) & 0x3FF; \
	(pData)->rgb.blue = (INT32) (*(UINT32 *)(pBuf)      ) & 0x3FF; \
	}

#define CORDATA_UNPACK_LAB101010(pBuf, pData) \
	{\
	(pData)->lab.l = (INT32) (*(UINT32 *)(pBuf) >> 20) & 0x3FF; \
	(pData)->lab.a = (INT32) (*(UINT32 *)(pBuf) >> 10) & 0x3FF; \
	(pData)->lab.b = (INT32) (*(UINT32 *)(pBuf)      ) & 0x3FF; \
	}

#define CORDATA_UNPACK_LAB888(pBuf, pData) \
	{\
	(pData)->lab.l = (INT32) *((UINT8 *)(pBuf)+2); \
	(pData)->lab.a = (INT32) *((UINT8 *)(pBuf)+1); \
	(pData)->lab.b = (INT32) *((UINT8 *)(pBuf)  ); \
	}

#define CORDATA_UNPACK_LAB8888(pBuf, pData) \
	{\
	(pData)->lab.l = (INT32) *((UINT8 *)(pBuf)+2); \
	(pData)->lab.a = (INT32) *((UINT8 *)(pBuf)+1); \
	(pData)->lab.b = (INT32) *((UINT8 *)(pBuf)  ); \
	}

#define CORDATA_UNPACK_RGB161616(pBuf, pData) \
	{\
	(pData)->rgb.red  = (INT32) *((UINT16 *)(pBuf)+2); \
	(pData)->rgb.green= (INT32) *((UINT16 *)(pBuf)+1); \
	(pData)->rgb.blue = (INT32) *((UINT16 *)(pBuf)  ); \
	}

#define CORDATA_UNPACK_RGB16161616(pBuf, pData) \
	{\
	(pData)->rgba.alpha = (INT32) *((UINT16 *)(pBuf)+3); \
	(pData)->rgba.red   = (INT32) *((UINT16 *)(pBuf)+2); \
	(pData)->rgba.green = (INT32) *((UINT16 *)(pBuf)+1); \
	(pData)->rgba.blue  = (INT32) *((UINT16 *)(pBuf)  ); \
	}

#define CORDATA_UNPACK_LAB16161616(pBuf, pData) \
	{\
   (pData)->laba.alpha = *((UINT16 *)(pBuf)+3); \
	(pData)->laba.l = *((UINT16 *)(pBuf)+2); \
	(pData)->laba.a = *((UINT16 *)(pBuf)+1); \
	(pData)->laba.b = *((UINT16 *)(pBuf)  ); \
	}

#define CORDATA_UNPACK_FLOAT(pBuf, pData) \
	{\
	(pData)->flt = *(FLOAT *)(pBuf); \
	}

#define CORDATA_UNPACK_COMPLEX(pBuf, pData) \
	{\
	(pData)->cplx.real = *((FLOAT *)(pBuf)  ); \
	(pData)->cplx.imag = *((FLOAT *)(pBuf)+1); \
	}

#define CORDATA_UNPACK_POINT(pBuf, pData) \
	{\
	(pData)->point.x = *((INT32 *)(pBuf)  ); \
	(pData)->point.y = *((INT32 *)(pBuf)+1); \
	}

#define CORDATA_UNPACK_FPOINT(pBuf, pData) \
	{\
	(pData)->fpoint.x = *((FLOAT *)(pBuf)  ); \
	(pData)->fpoint.y = *((FLOAT *)(pBuf)+1); \
	}

#define CORDATA_UNPACK_HSV(pBuf, pData) \
	{\
	(pData)->hsv.h= (INT32) *((UINT8 *)(pBuf)+2); \
	(pData)->hsv.s= (INT32) *((UINT8 *)(pBuf)+1); \
	(pData)->hsv.v= (INT32) *((UINT8 *)(pBuf)  ); \
	}

#define CORDATA_UNPACK_HSI(pBuf, pData) \
	{\
	(pData)->hsi.h= (INT32) *((UINT8 *)(pBuf)+2); \
	(pData)->hsi.s= (INT32) *((UINT8 *)(pBuf)+1); \
	(pData)->hsi.i= (INT32) *((UINT8 *)(pBuf)  ); \
	}

#define CORDATA_UNPACK_LAB(pBuf, pData) \
	{\
	(pData)->lab.l= (INT32) *((UINT8 *)(pBuf)+2); \
	(pData)->lab.a= (INT32) *((UINT8 *)(pBuf)+1); \
	(pData)->lab.b= (INT32) *((UINT8 *)(pBuf)  ); \
	}

#define CORDATA_UNPACK_YUV(pBuf, pData) \
	{\
	(pData)->yuv.y= (INT32) *((UINT8 *)(pBuf)+2); \
	(pData)->yuv.u= (INT32) *((UINT8 *)(pBuf)+1); \
	(pData)->yuv.v= (INT32) *((UINT8 *)(pBuf)  ); \
	}

#define CORDATA_UNPACK_UYVY(pBuf, pData, xPos) \
	{\
	(pData)->yuv.u = (INT32) *((UINT8 *)(pBuf)  ); \
	(pData)->yuv.v = (INT32) *((UINT8 *)(pBuf)+2); \
	(pData)->yuv.y = (INT32) *((UINT8 *)(pBuf)+1 + (((xPos) & 1) ? 2 : 0)); \
	}

#define CORDATA_UNPACK_YUY2(pBuf, pData, xPos) \
	{\
	(pData)->yuv.u = (INT32) *((UINT8 *)(pBuf)+1); \
	(pData)->yuv.v = (INT32) *((UINT8 *)(pBuf)+3); \
	(pData)->yuv.y = (INT32) *((UINT8 *)(pBuf) + (((xPos) & 1) ? 2 : 0)); \
	}

#define CORDATA_UNPACK_Y411(pBuf, pData, xPos)\
	{\
	(pData)->yuv.u = (INT32) *((UINT8 *)(pBuf)  ); \
	(pData)->yuv.v = (INT32) *((UINT8 *)(pBuf)+3); \
	(pData)->yuv.y = (INT32) *((UINT8 *)(pBuf)+1+(xPos)+(((xPos) & 2) ? 1 : 0)); \
	}

#define CORDATA_UNPACK_IYU1(pBuf, pData, xPos)	CORDATA_UNPACK_Y411(pBuf, pData, xPos)

#define CORDATA_UNPACK_IYU2(pBuf, pData) \
	{\
	(pData)->yuv.u = (INT32) *((UINT8 *)(pBuf)  ); \
	(pData)->yuv.y = (INT32) *((UINT8 *)(pBuf)+1); \
	(pData)->yuv.v = (INT32) *((UINT8 *)(pBuf)+2); \
	}

#define CORDATA_UNPACK_BICOLOR88_RG(pBuf, pData) \
   {\
	(pData)->rgb.red  = (INT32) *((UINT8 *)(pBuf)  );\
	(pData)->rgb.green= (INT32) *((UINT8 *)(pBuf)+1);\
	(pData)->rgb.blue = 0;\
   }

#define CORDATA_UNPACK_BICOLOR88_BG(pBuf, pData) \
   {\
	(pData)->rgb.red  = 0;\
	(pData)->rgb.green= (INT32) *((UINT8 *)(pBuf)+1);\
	(pData)->rgb.blue = (INT32) *((UINT8 *)(pBuf)  );\
   }

#define CORDATA_UNPACK_BICOLOR1616_RG(pBuf, pData) \
   {\
	(pData)->rgb.red  = (INT32) *((UINT16 *)(pBuf)  );\
	(pData)->rgb.green= (INT32) *((UINT16 *)(pBuf)+1);\
	(pData)->rgb.blue = 0;\
   }

#define CORDATA_UNPACK_BICOLOR1616_BG(pBuf, pData) \
   {\
	(pData)->rgb.red  = 0;\
	(pData)->rgb.green= (INT32) *((UINT16 *)(pBuf)+1);\
	(pData)->rgb.blue = (INT32) *((UINT16 *)(pBuf)  );\
   }

#endif   // _CORPACK_H_
