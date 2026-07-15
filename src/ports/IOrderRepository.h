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
    virtual std::vector<OrderRecord> FindByStatus(const std::string& status) const = 0;
    virtual int64_t NextOrderId() const = 0;
    virtual void Add(const OrderRecord& order) = 0;
    virtual void Update(const OrderRecord& order) = 0;
};
