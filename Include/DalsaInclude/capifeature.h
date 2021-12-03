//
// Coreco API - Camera feature functions.
//

#ifndef _CAPIFEATURE_H_
#define _CAPIFEATURE_H_

#include "capidef.h"


/****************************************************************************
*	Feature Parameters
****************************************************************************/

#define CORFEATURE_PRM_FIRST			0
#define CORFEATURE_PRM( n, size)		((((n) + CORFEATURE_PRM_FIRST) << 16) | (size))


#define CORFEATURE_PRM_NAME            CORFEATURE_PRM( 0, 64)  // String
#define CORFEATURE_PRM_TYPE            CORFEATURE_PRM( 1, 4)   // Enum
#define CORFEATURE_PRM_STANDARD        CORFEATURE_PRM( 2, 4)   // Bool
#define CORFEATURE_PRM_ACCESS_MODE     CORFEATURE_PRM( 3, 4)   // Enum
#define CORFEATURE_PRM_POLLING_TIME    CORFEATURE_PRM( 4, 4)   // Integer
#define CORFEATURE_PRM_TOOL_TIP        CORFEATURE_PRM( 5, 256) // String
#define CORFEATURE_PRM_DISPLAY_NAME    CORFEATURE_PRM( 6, 64)  // String
#define CORFEATURE_PRM_REPRESENTATION  CORFEATURE_PRM( 7, 4)   // Enum
#define CORFEATURE_PRM_SIGN            CORFEATURE_PRM( 8, 4)   // Enum
#define CORFEATURE_PRM_SI_UNIT         CORFEATURE_PRM( 9, 32)  // String
#define CORFEATURE_PRM_CATEGORY        CORFEATURE_PRM( 10, 64) // String
#define CORFEATURE_PRM_WRITE_MODE      CORFEATURE_PRM( 11, 4)  // Enum
#define CORFEATURE_PRM_SAVED_TO_CONFIG_FILE     CORFEATURE_PRM( 12, 4)  // Bool
#define CORFEATURE_PRM_SI_TO_NATIVE_EXP10       CORFEATURE_PRM( 13, 4)  // Integer
#define CORFEATURE_PRM_VISIBILITY      CORFEATURE_PRM( 14, 4)  // Enum
#define CORFEATURE_PRM_SELECTOR        CORFEATURE_PRM( 15, 4)  // Bool
#define CORFEATURE_PRM_ARRAY_LENGTH    CORFEATURE_PRM( 16, 4)  // Integer
#define CORFEATURE_PRM_DESCRIPTION     CORFEATURE_PRM( 17, 1024)// String
#define CORFEATURE_PRM_IS_DEPRECATED   CORFEATURE_PRM( 18, 4) // Bool
#define CORFEATURE_PRM_DOC_URL         CORFEATURE_PRM( 19, 1024) // String
#define CORFEATURE_PRM_INCREMENT_TYPE  CORFEATURE_PRM( 20, 4)  // Enum
#define CORFEATURE_PRM_VALID_VALUE_COUNT        CORFEATURE_PRM( 21, 4) // Integer
#define CORFEATURE_PRM_CATEGORY_COUNT   CORFEATURE_PRM( 22, 4) // Integer
#define CORFEATURE_PRM_CATEGORY_LIST    CORFEATURE_PRM( 23, 128) // List of Integer
#define CORFEATURE_PRM_FLOAT_PRECISION  CORFEATURE_PRM( 24, 8) // Integer
#define CORFEATURE_PRM_FLOAT_NOTATION   CORFEATURE_PRM( 25, 4) // Enum

#define CORFEATURE_PRM_LAST            (CORFEATURE_PRM_FIRST + 25)

/****************************************************************************
*	Enumeration Parameters
****************************************************************************/

#define CORFEATURE_ENUM_PRM_FIRST	1000
#define CORFEATURE_ENUM_PRM( n, size)		((((n) + CORFEATURE_ENUM_PRM_FIRST) << 16) | (size))

#define CORFEATURE_ENUM_PRM_NAME            CORFEATURE_ENUM_PRM( 0, 64)  // String
#define CORFEATURE_ENUM_PRM_STANDARD        CORFEATURE_ENUM_PRM( 1, 4)   // Bool
#define CORFEATURE_ENUM_PRM_TOOL_TIP        CORFEATURE_ENUM_PRM( 2, 256) // String
#define CORFEATURE_ENUM_PRM_DISPLAY_NAME    CORFEATURE_ENUM_PRM( 3, 64)  // String
#define CORFEATURE_ENUM_PRM_VISIBILITY      CORFEATURE_ENUM_PRM( 4, 4)   // Enum
#define CORFEATURE_ENUM_PRM_DESCRIPTION     CORFEATURE_ENUM_PRM( 5, 1024)// String
#define CORFEATURE_ENUM_PRM_IS_DEPRECATED   CORFEATURE_ENUM_PRM( 6, 4) // Bool

#define CORFEATURE_ENUM_PRM_LAST            (CORFEATURE_ENUM_PRM_FIRST + 7)

/****************************************************************************
*	Feature Values
****************************************************************************/

// Data Types
#define CORFEATURE_VAL_TYPE_UNDEFINED  0
#define CORFEATURE_VAL_TYPE_INT32      1
#define CORFEATURE_VAL_TYPE_INT64      2
#define CORFEATURE_VAL_TYPE_FLOAT      3
#define CORFEATURE_VAL_TYPE_DOUBLE     4
#define CORFEATURE_VAL_TYPE_BOOL       5
#define CORFEATURE_VAL_TYPE_ENUM       6
#define CORFEATURE_VAL_TYPE_STRING     7
#define CORFEATURE_VAL_TYPE_BUFFER     8
#define CORFEATURE_VAL_TYPE_LUT        9
#define CORFEATURE_VAL_TYPE_ARRAY      10
#define CORFEATURE_VAL_TYPE_ACTION     11

// Access Modes
#define CORFEATURE_VAL_ACCESS_MODE_UNDEFINED  0    // Undefined
#define CORFEATURE_VAL_ACCESS_MODE_RW         1		// Read and Write
#define CORFEATURE_VAL_ACCESS_MODE_RO         2		// Read Only
#define CORFEATURE_VAL_ACCESS_MODE_WO         3		// Write Only
#define CORFEATURE_VAL_ACCESS_MODE_NP         4	   // Not present
#define CORFEATURE_VAL_ACCESS_MODE_NE         5		// Not enabled

// Data Representations (for float and integer)
#define CORFEATURE_VAL_REPRESENTATION_UNDEFINED   0
#define CORFEATURE_VAL_REPRESENTATION_LINEAR      1
#define CORFEATURE_VAL_REPRESENTATION_LOGARITHMIC 2
#define CORFEATURE_VAL_REPRESENTATION_PURENUMBER  4
//            integer only
#define CORFEATURE_VAL_REPRESENTATION_BOOLEAN     3
#define CORFEATURE_VAL_REPRESENTATION_HEXNUMBER   5
#define CORFEATURE_VAL_REPRESENTATION_IPV4ADDRESS 6
#define CORFEATURE_VAL_REPRESENTATION_MACADDR     7

// Data Sign
#define CORFEATURE_VAL_SIGN_UNDEFINED  0
#define CORFEATURE_VAL_SIGN_SIGNED     1
#define CORFEATURE_VAL_SIGN_UNSIGNED   2

// Restriction on writing when access mode is read-write or write only
#define CORFEATURE_VAL_WRITE_MODE_UNDEFINED     0     // Undefined
#define CORFEATURE_VAL_WRITE_MODE_ALWAYS        1     // Always writable
#define CORFEATURE_VAL_WRITE_MODE_NOT_ACQUIRING 2     // Writable when not acquiring
#define CORFEATURE_VAL_WRITE_MODE_NOT_CONNECTED 3     // Writable when not connected

// Visibility Types
#define CORFEATURE_VAL_VISIBILITY_UNDEFINED 0   // Undefined
#define CORFEATURE_VAL_VISIBILITY_BEGINNER  1	// Always visible
#define CORFEATURE_VAL_VISIBILITY_EXPERT    2   // Visible for experts or Gurus
#define CORFEATURE_VAL_VISIBILITY_GURU      3	// Visible for Gurus
#define CORFEATURE_VAL_VISIBILITY_INVISIBLE 4	// Not Visible

// Increment Type
#define CORFEATURE_VAL_INCREMENT_TYPE_UNDEFINED 0   // Undefined
#define CORFEATURE_VAL_INCREMENT_TYPE_NONE   1      // Feature has no increment
#define CORFEATURE_VAL_INCREMENT_TYPE_LINEAR 2      // Increment by a fix number
#define CORFEATURE_VAL_INCREMENT_TYPE_LIST   3      // Valid value are provided in a list

// Float Notation
#define CORFEATURE_VAL_FLOAT_NOTATION_UNDEFINED    0   // Undefined
#define CORFEATURE_VAL_FLOAT_NOTATION_FIXED        1   // GUI should use fixed notation, i.e. 123.4
#define CORFEATURE_VAL_FLOAT_NOTATION_SCIENTIFIC   2   // GUI should use scientific notation, i.e. 1.234e-5



/****************************************************************************
*	Application programming interface
****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

// Creation/destruction
CORSTATUS CORAPIFUNC CorFeatureNew(CORSERVER server, PCORFEATURE feature);
CORSTATUS CORAPIFUNC CorFeatureFree(CORFEATURE feature);

// General Parameters
CORSTATUS CORAPIFUNC CorFeatureGetPrm  (CORFEATURE feature, UINT32 prm, void *value);
CORSTATUS CORAPIFUNC CorFeatureSetPrm  (CORFEATURE feature, UINT32 prm, UINT32 value);
CORSTATUS CORAPIFUNC CorFeatureSetPrmEx(CORFEATURE feature, UINT32 prm, const void *value);

// Integer/float-specific Parameters
CORSTATUS CORAPIFUNC CorFeatureGetMin(CORFEATURE feature, void *minVal, UINT32 valSize);
CORSTATUS CORAPIFUNC CorFeatureGetMax(CORFEATURE feature, void *maxVal, UINT32 valSize);
CORSTATUS CORAPIFUNC CorFeatureGetInc(CORFEATURE feature, void *incVal, UINT32 valSize);
CORSTATUS CORAPIFUNC CorFeatureGetValidValue(CORFEATURE feature, UINT32 valueIndex, void *val, UINT32 valSize);

// Enumeration-specific Parameters
CORSTATUS CORAPIFUNC CorFeatureGetEnumCount(CORFEATURE feature, PUINT32 count);
CORSTATUS CORAPIFUNC CorFeatureGetEnumString(CORFEATURE feature, UINT32 index, PSTR enumString, UINT32 stringSize);
CORSTATUS CORAPIFUNC CorFeatureGetEnumValue(CORFEATURE feature, UINT32 index, PUINT32 value);
CORSTATUS CORAPIFUNC CorFeatureIsEnumEnabled(CORFEATURE feature, UINT32 index, PUINT32 enabled);
CORSTATUS CORAPIFUNC CorFeatureGetEnumStringFromValue(CORFEATURE feature, UINT32 value, PSTR enumString, UINT32 stringSize);
CORSTATUS CORAPIFUNC CorFeatureGetEnumValueFromString(CORFEATURE feature, PCSTR enumString, PUINT32 value);

// Selector-specific Parameters
CORSTATUS CORAPIFUNC CorFeatureGetSelectedCount(CORFEATURE feature, PUINT32 count);
CORSTATUS CORAPIFUNC CorFeatureGetSelectedIndex(CORFEATURE feature, UINT32 selectedIndex, PUINT32 featureIndex);
CORSTATUS CORAPIFUNC CorFeatureGetSelectedName(CORFEATURE feature, UINT32 selectedIndex, PSTR featureName, UINT32 nameSize);
CORSTATUS CORAPIFUNC CorFeatureGetSelectingCount(CORFEATURE feature, PUINT32 count);
CORSTATUS CORAPIFUNC CorFeatureGetSelectingIndex(CORFEATURE feature, UINT32 selectingIndex, PUINT32 featureIndex);
CORSTATUS CORAPIFUNC CorFeatureGetSelectingName(CORFEATURE feature, UINT32 selectingIndex, PSTR featureName, UINT32 nameSize);

#ifdef __cplusplus
}
#endif

#endif   // _CAPIFEATURE_H_
