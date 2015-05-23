#include <stdlib.h>
#include "webp_dll.h"
// This function should be used in place of free() for memory
// returned by the WebP API.
WEBP_EXTERN(void) WebPFree(void* ptr) {
	free(ptr);
}
