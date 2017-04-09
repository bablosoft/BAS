#ifndef UTIL_SNAPPY_OPENSOURCE_SNAPPY_STUBS_PUBLIC_H_
#define UTIL_SNAPPY_OPENSOURCE_SNAPPY_STUBS_PUBLIC_H_

#include <stdint.h>
#include <stddef.h>

#define SNAPPY_MAJOR 1
#define SNAPPY_MINOR 1
#define SNAPPY_PATCHLEVEL 1
#define SNAPPY_BUILD 7
#define SNAPPY_VERSION \
	((SNAPPY_MAJOR << 16) | (SNAPPY_MINOR << 8) | SNAPPY_PATCHLEVEL)
#define SNAPPY_VERSION_STRING "1.1.1.7"

#include <string>

namespace snappy {

	typedef int ssize_t;

	typedef int8_t int8;
	typedef uint8_t uint8;
	typedef int16_t int16;
	typedef uint16_t uint16;
	typedef int32_t int32;
	typedef uint32_t uint32;
	typedef int64_t int64;
	typedef uint64_t uint64;

	typedef std::string string;

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&);               \
	void operator=(const TypeName&)

}  // namespace snappy

#endif  // UTIL_SNAPPY_OPENSOURCE_SNAPPY_STUBS_PUBLIC_H_
