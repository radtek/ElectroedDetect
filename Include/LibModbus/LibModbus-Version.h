#ifndef LIBMODBUS_VERSION_H
#define LIBMODBUS_VERSION_H

/* The major version, (1, if %LIBMODBUS_VERSION is 1.2.3) */
#define LIBMODBUS_VERSION_MAJOR (@LIBMODBUS_VERSION_MAJOR@)

/* The minor version (2, if %LIBMODBUS_VERSION is 1.2.3) */
#define LIBMODBUS_VERSION_MINOR (@LIBMODBUS_VERSION_MINOR@)

/* The micro version (3, if %LIBMODBUS_VERSION is 1.2.3) */
#define LIBMODBUS_VERSION_MICRO (@LIBMODBUS_VERSION_MICRO@)

/* The full version, like 1.2.3 */
#define LIBMODBUS_VERSION        @LIBMODBUS_VERSION@

/* The full version, in string form (suited for string concatenation)
 */
#define LIBMODBUS_VERSION_STRING "@LIBMODBUS_VERSION@"

/* Numerically encoded version, eg. v1.2.3 is 0x010203 */
#define LIBMODBUS_VERSION_HEX ((LIBMODBUS_VERSION_MAJOR << 16) |  \
                               (LIBMODBUS_VERSION_MINOR <<  8) |  \
                               (LIBMODBUS_VERSION_MICRO <<  0))

/* Evaluates to True if the version is greater than @major, @minor and @micro
 */
#define LIBMODBUS_VERSION_CHECK(major,minor,micro)      \
    (LIBMODBUS_VERSION_MAJOR > (major) ||               \
     (LIBMODBUS_VERSION_MAJOR == (major) &&             \
      LIBMODBUS_VERSION_MINOR > (minor)) ||             \
     (LIBMODBUS_VERSION_MAJOR == (major) &&             \
      LIBMODBUS_VERSION_MINOR == (minor) &&             \
      LIBMODBUS_VERSION_MICRO >= (micro)))

#define     IPTOS_LOWDELAY        0x10
#define     IPTOS_THROUGHPUT      0x08
#define     IPTOS_RELIABILITY     0x04

#endif /* LIBMODBUS_VERSION_H */
