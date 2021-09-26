#include "./stdint.h"

static inline void outb(uint16_t port, uint8_t data);
static inline uint8_t inb(uint16_t port);
static inline void outw(uint16_t port, uint32_t data);
static inline uint32_t inw(uint16_t port);