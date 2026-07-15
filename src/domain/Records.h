#pragma once
#include <cstdint>
#include <string>

// CONTRACT.md §5 — 필드명/타입은 계약 그대로. 이 저장소에서 수정 금지.
struct SampleRecord {
    std::string sampleId; std::string name;
    double avgProductionTime; int yieldNumerator; int64_t stockQuantity;
};
struct OrderRecord {
    int64_t orderId; std::string sampleId; std::string customerName;
    int64_t orderQuantity; std::string status; std::string createdAt;
};
constexpr int YIELD_DENOMINATOR = 10000;
