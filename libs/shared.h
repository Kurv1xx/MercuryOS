#pragma once
#include <stdint.h>

typedef struct {
    void* framebuffer;
    uint32_t width;
    uint32_t height;
    uint32_t pitch;

    void* memory_map;
    uint64_t memory_map_size;
    uint64_t memory_map_desc_size;
} BootInfo;
