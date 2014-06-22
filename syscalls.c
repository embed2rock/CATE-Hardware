/*
 * syscalls.c
 *
 *  Created on: 13/feb/2014
 *      Author: Postazione Embedded
 */

#include <sys/stat.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "usb/usbd_cdc_vcp.h"

int __errno;

int _close(int file) {
	return 0;
}

int _fstat(int file, struct stat *st) {
	return 0;
}

int _isatty(int file) {
	return 1;
}

int _lseek(int file, int ptr, int dir) {
	return 0;
}

int _open(const char *name, int flags, int mode) {
	return -1;
}

int _read(int file, char *ptr, int len) {
	if (file != 0) {
		return 0;
	}

	// Use USB CDC Port for stdin
	while(!VCP_get_char((uint8_t*)ptr)){};

	// Echo typed characters
	VCP_put_char((uint8_t)*ptr);

	return 1;
}

/*The _sbrk_r is provided by the toolchain compiler*/

int _write(int file, char *ptr, int len) {
	VCP_send_buffer((uint8_t*)ptr, len);
	return len;
}
