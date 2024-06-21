#pragma once
#include <cstdint>
#include <span>

namespace Payload {

std::span<uint8_t> GetPayloadX86();
std::span<uint8_t> GetPayloadX64();

};  // namespace Payload
