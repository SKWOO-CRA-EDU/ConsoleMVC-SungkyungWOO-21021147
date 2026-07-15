#pragma once
#include <cstdint>
#include <stdexcept>
#include <string>

// CONTRACT.md §2/§5/§7 — 필드명/타입/어휘는 계약 그대로. 이 저장소에서 수정 금지.
enum class OrderStatus { Reserved, Rejected, Producing, Confirmed, Release };

enum class [[nodiscard]] WriteOutcome { Ok, NotFound, DuplicateKey };

class StorageUnavailable : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};
class StorageCorrupted : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};
class SchemaVersionMismatch : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

struct SampleRecord {
    std::string sampleId; std::string name;
    double avgProductionTime; int yieldNumerator; int64_t stockQuantity;
};
struct OrderRecord {
    int64_t orderId; std::string sampleId; std::string customerName;
    int64_t orderQuantity; OrderStatus status; std::string createdAt;
};
constexpr int YIELD_DENOMINATOR = 10000;
