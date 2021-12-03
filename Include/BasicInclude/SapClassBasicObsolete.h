#ifndef _SAPCLASSBASICOBSOLETE_H_
#define _SAPCLASSBASICOBSOLETE_H_

// SapClassBasicObsolete.h : header file
//

// Classes kept for compatibility with existing applications
#include "SapBufferWithTrashAndRoi.h"
#include "SapRTProDesignOnBrdBuffers.h"

// Manager resource types
#define SAPMAN_RESOURCE_ACQ      SapManager::ResourceAcq
#define SAPMAN_RESOURCE_DISPLAY  SapManager::ResourceDisplay
#define SAPMAN_RESOURCE_CAB      SapManager::ResourceCab
#define SAPMAN_RESOURCE_PIXPRO   SapManager::ResourcePixPro
#define SAPMAN_RESOURCE_LAST     SapManager::ResourceLast

// Manager status reporting modes
#define SAPMAN_STATUS_NOTIFY  SapManager::StatusNotify
#define SAPMAN_STATUS_LOG     SapManager::StatusLog
#define SAPMAN_STATUS_DEBUG   SapManager::StatusDebug
#define SAPMAN_STATUS_LAST    SapManager::StatusLast

// Manager resource database dimensions
#define SAPMAN_MAX_SERVERS          SapManager::MaxServers
#define SAPMAN_MAX_RESOURCE_TYPES   SapManager::MaxResourceTypes
#define SAPMAN_MAX_RESOURCES        SapManager::MaxResources
#define SAPMAN_MAX_LABEL_SIZE       SapManager::MaxLabelSize

// Default values for buffer parameters
#undef SAPBUFFER_DEFAULT_COUNT
#undef SAPBUFFER_DEFAULT_WIDTH
#undef SAPBUFFER_DEFAULT_HEIGHT
#undef SAPBUFFER_DEFAULT_FORMAT
#undef SAPBUFFER_DEFAULT_TYPE

#define SAPBUFFER_DEFAULT_COUNT  SapDefBufferCount
#define SAPBUFFER_DEFAULT_WIDTH  SapDefWidth
#define SAPBUFFER_DEFAULT_HEIGHT SapDefHeight
#define SAPBUFFER_DEFAULT_FORMAT SapDefFormat
#define SAPBUFFER_DEFAULT_TYPE   SapDefBufferType

// Default values for transfer parameters
#undef SAPXFER_DEFAULT_FRAME
#undef SAPXFER_DEFAULT_FIELD_ORDER
#undef SAPXFER_DEFAULT_WIDTH
#undef SAPXFER_DEFAULT_HEIGHT
#undef SAPXFER_DEFAULT_FORMAT
#undef SAPXFER_DEFAULT_PIXEL_DEPTH
#undef SAPXFER_DEFAULT_PIXEL_SHIFT

#define SAPXFER_DEFAULT_FRAME       SapDefFrame
#define SAPXFER_DEFAULT_FIELD_ORDER SapDefFieldOrder
#define SAPXFER_DEFAULT_WIDTH       SapDefWidth
#define SAPXFER_DEFAULT_HEIGHT      SapDefHeight
#define SAPXFER_DEFAULT_FORMAT      SapDefFormat
#define SAPXFER_DEFAULT_PIXEL_DEPTH SapDefPixelDepth
#define SAPXFER_DEFAULT_PIXEL_SHIFT SapDefPixelShift

#endif   // _SAPCLASSBASICOBSOLETE_H_
