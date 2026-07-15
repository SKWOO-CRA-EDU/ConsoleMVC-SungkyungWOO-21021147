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

std::vector<OrderRecord> InMemoryOrderRepository::FindByStatus(OrderStatus status) const {
    std::vector<OrderRecord> result;
    for (const auto& [id, record] : records_) {
        if (record.status == status) result.push_back(record);
    }
    return result;
}

std::vector<OrderRecord> InMemoryOrderRepository::FindBySampleId(const std::string& sampleId) const {
    std::vector<OrderRecord> result;
    for (const auto& [id, record] : records_) {
        if (record.sampleId == sampleId) result.push_back(record);
    }
    return result;
}

WriteOutcome InMemoryOrderRepository::Add(const OrderRecord& order) {
    if (records_.find(order.orderId) != records_.end()) return WriteOutcome::DuplicateKey;
    records_[order.orderId] = order;
    return WriteOutcome::Ok;
}

WriteOutcome InMemoryOrderRepository::Update(const OrderRecord& order) {
    auto it = records_.find(order.orderId);
    if (it == records_.end()) return WriteOutcome::NotFound;
    it->second = order;
    return WriteOutcome::Ok;
}
