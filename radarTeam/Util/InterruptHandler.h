#ifndef AVR_INTERRUPTHANDLER_H
#define AVR_INTERRUPTHANDLER_H

#define CPP_ISR(vector) static void vector() __asm__("vector_num") __attribute__((__signal__, __used__, __externally_visible__))

#endif //AVR_INTERRUPTHANDLER_H
