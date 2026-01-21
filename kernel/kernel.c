#include "../libs/shared.h"

void kernel_entry(BootInfo* boot) {
    uint32_t* fb = (uint32_t*)boot->framebuffer;

    for (uint32_t y = 0; y < boot->height; y++) {
        for (uint32_t x = 0; x < boot->width; x++) {
            fb[y * (boot->pitch / 4) + x] = 0x002020FF;
        }
    }

    while (1) __asm__("hlt");
}
