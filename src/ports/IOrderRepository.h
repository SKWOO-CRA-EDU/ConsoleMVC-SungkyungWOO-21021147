#pragma once
#include <cstdint>
#include <optional>
#include <string>
#include <vector>
#include "../domain/Records.h"

// CONTRACT.md §5 — 시그니처 그대로. 구현 금지(선언만); 실제 구현은 타 저장소 책임.
class IOrderRepository {
public:
    virtual ~IOrderRepository() = default;
    virtual std::optional<OrderRecord> FindById(int64_t orderId) const = 0;
    virtual std::vector<OrderRecord> FindAll() const = 0;
    virtual std::vector<OrderRecord> FindByStatus(OrderStatus status) const = 0;
    virtual std::vector<OrderRecord> FindBySampleId(const std::string& sampleId) const = 0;
    virtual WriteOutcome Add(const OrderRecord& order) = 0;
    virtual WriteOutcome Update(const OrderRecord& order) = 0;
};
