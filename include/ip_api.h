#ifndef __IP_API_H__
#define __IP_API_H__

#include <stddef.h>
#define SIZEOF(X) (sizeof(X)/sizeof(char*))

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @para: argc - number of command
 * @para: argv - array of command
 * @para: buffer - buffer provided by the user
 * @para: buffer_size - size of the buffer 
 */

int main_entry_point3(int argc, const char* argv[], char* buffer, size_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif
