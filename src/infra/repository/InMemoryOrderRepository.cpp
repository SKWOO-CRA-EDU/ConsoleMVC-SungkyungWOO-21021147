#include "InMemoryOrderRepository.h"

std::optional<OrderRecord> InMemoryOrderRepository::FindById(int64_t orderId) const {
    auto it = records_.find(orderId);
    if (it == records_.end()) return std::nullopt;
    return it->second;
}

std::vector<OrderRecord> InMemoryOrderRepository::FindAll() const {
    std::vector<OrderRecord> result;
    result.reserve(records_.size());
    for (const auto& [id, record] : records_) {
        result.push_back(record);
    }
    return result;
}

std::vector<OrderRecord> InMemoryOrderRepository::FindByStatus(const std::string& status) const {
    std::vector<OrderRecord> result;
    for (const auto& [id, record] : records_) {
        if (record.status == status) result.push_back(record);
    }
    return result;
}

int64_t InMemoryOrderRepository::NextOrderId() const {
    return nextId_;
}

void InMemoryOrderRepository::Add(const OrderRecord& order) {
    records_[order.orderId] = order;
    if (order.orderId >= nextId_) {
        nextId_ = order.orderId + 1;
    }
}

void InMemoryOrderRepository::Update(const OrderRecord& order) {
    records_[order.orderId] = order;
}
