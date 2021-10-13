#include <stdint.h>

#ifndef PORTS_H__
#define PORTS_H__

void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);
void outw(uint16_t port, uint32_t data);
uint32_t inw(uint16_t port);

#endif