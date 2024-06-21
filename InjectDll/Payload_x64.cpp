#include "Payload.h"

namespace Payload {
uint8_t gPayloadX64[] = {
    // asm/slide_x64.asm
    0x59,

    // GetLdrLoadDll
    0x48, 0x89, 0x5C, 0x24, 0x10, 0x48, 0x89, 0x74, 0x24, 0x18, 0x55, 0x57, 0x41, 0x56, 0x48, 0x8B, 0xEC, 0x48, 0x83,
    0xEC, 0x60, 0x0F, 0xB7, 0x01, 0x45, 0x33, 0xF6, 0x66, 0x89, 0x45, 0xD0, 0xBF, 0x4E, 0x00, 0x00, 0x00, 0x0F, 0xB7,
    0x41, 0x02, 0x66, 0x89, 0x45, 0xD2, 0x48, 0x8D, 0x41, 0x04, 0x48, 0x89, 0x45, 0xD8, 0x65, 0x48, 0x8B, 0x04, 0x25,
    0x30, 0x00, 0x00, 0x00, 0xC7, 0x45, 0xE0, 0x4E, 0x00, 0x54, 0x00, 0xC7, 0x45, 0xE4, 0x44, 0x00, 0x4C, 0x00, 0xC7,
    0x45, 0xE8, 0x4C, 0x00, 0x2E, 0x00, 0x48, 0x8B, 0x48, 0x60, 0xC7, 0x45, 0xEC, 0x44, 0x00, 0x4C, 0x00, 0xC7, 0x45,
    0xF0, 0x4C, 0x00, 0x00, 0x00, 0xC7, 0x45, 0xC0, 0x4C, 0x64, 0x72, 0x4C, 0x48, 0x8B, 0x59, 0x18, 0x48, 0x83, 0xC3,
    0x20, 0xC7, 0x45, 0xC4, 0x6F, 0x61, 0x64, 0x44, 0x66, 0xC7, 0x45, 0xC8, 0x6C, 0x6C, 0x44, 0x88, 0x75, 0xCA, 0x4C,
    0x8B, 0x1B, 0x4C, 0x3B, 0xDB, 0x0F, 0x84, 0x80, 0x00, 0x00, 0x00, 0x41, 0x0F, 0xB7, 0x4B, 0x38, 0x49, 0x8B, 0x43,
    0x40, 0x48, 0xD1, 0xE9, 0x66, 0x83, 0x7C, 0x48, 0xFE, 0x5C, 0x48, 0x8D, 0x04, 0x48, 0x74, 0x13, 0x0F, 0x1F, 0x84,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x83, 0xE8, 0x02, 0x66, 0x83, 0x78, 0xFE, 0x5C, 0x75, 0xF5, 0x48, 0x8D, 0x4D,
    0xE0, 0x4C, 0x8D, 0x55, 0xE0, 0x48, 0x3B, 0xC1, 0x74, 0x5F, 0x0F, 0xB7, 0xD7, 0x44, 0x0F, 0xB7, 0x08, 0x41, 0x8D,
    0x49, 0x9F, 0x66, 0x83, 0xF9, 0x19, 0x45, 0x8D, 0x41, 0xE0, 0x8D, 0x4A, 0x9F, 0x66, 0x45, 0x0F, 0x47, 0xC1, 0x66,
    0x83, 0xF9, 0x19, 0x77, 0x04, 0x66, 0x83, 0xEA, 0x20, 0x66, 0x44, 0x3B, 0xC2, 0x75, 0x15, 0x66, 0x45, 0x85, 0xC0,
    0x74, 0x2E, 0x41, 0x0F, 0xB7, 0x52, 0x02, 0x48, 0x83, 0xC0, 0x02, 0x49, 0x83, 0xC2, 0x02, 0xEB, 0xC3, 0x4D, 0x8B,
    0x1B, 0x4C, 0x3B, 0xDB, 0x75, 0x80, 0x33, 0xC0, 0x4C, 0x8D, 0x5C, 0x24, 0x60, 0x49, 0x8B, 0x5B, 0x28, 0x49, 0x8B,
    0x73, 0x30, 0x49, 0x8B, 0xE3, 0x41, 0x5E, 0x5F, 0x5D, 0xC3, 0x4D, 0x8B, 0x4B, 0x20, 0x4D, 0x85, 0xC9, 0x74, 0xE0,
    0x49, 0x63, 0x41, 0x3C, 0x42, 0x8B, 0x8C, 0x08, 0x88, 0x00, 0x00, 0x00, 0x49, 0x03, 0xC9, 0x74, 0xCF, 0x48, 0x63,
    0x79, 0x1C, 0x45, 0x8B, 0xC6, 0x48, 0x63, 0x71, 0x24, 0x49, 0x03, 0xF9, 0x48, 0x63, 0x59, 0x20, 0x49, 0x03, 0xF1,
    0x44, 0x8B, 0x59, 0x18, 0x49, 0x03, 0xD9, 0x45, 0x85, 0xDB, 0x74, 0xAE, 0x0F, 0x1F, 0x40, 0x00, 0x66, 0x66, 0x0F,
    0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x8B, 0xD0, 0x48, 0x8D, 0x4D, 0xC0, 0x48, 0x8D, 0x55, 0xC0, 0x4A,
    0x63, 0x04, 0x93, 0x49, 0x03, 0xC1, 0x48, 0x3B, 0xC8, 0x74, 0x2A, 0x48, 0x85, 0xC0, 0x74, 0x18, 0xB1, 0x4C, 0x38,
    0x08, 0x75, 0x12, 0x84, 0xC9, 0x74, 0x1B, 0x0F, 0xB6, 0x4A, 0x01, 0x48, 0xFF, 0xC2, 0x48, 0xFF, 0xC0, 0x3A, 0x08,
    0x74, 0xEE, 0x41, 0xFF, 0xC0, 0x45, 0x3B, 0xC3, 0x72, 0xC4, 0xE9, 0x5F, 0xFF, 0xFF, 0xFF, 0x42, 0x0F, 0xB7, 0x04,
    0x56, 0x4C, 0x63, 0x14, 0x87, 0x4D, 0x03, 0xD1, 0x0F, 0x84, 0x4D, 0xFF, 0xFF, 0xFF, 0x4C, 0x8D, 0x4D, 0x20, 0x4C,
    0x89, 0x75, 0x20, 0x4C, 0x8D, 0x45, 0xD0, 0x33, 0xD2, 0x33, 0xC9, 0x41, 0xFF, 0xD2, 0x48, 0x8B, 0x45, 0x20, 0xE9,
    0x33, 0xFF, 0xFF, 0xFF};

std::span<uint8_t> GetPayloadX64() {
  return std::span(gPayloadX64);
}

};  // namespace Payload
