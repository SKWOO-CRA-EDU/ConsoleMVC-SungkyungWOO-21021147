#pragma once
#include <unordered_map>
#include "../../ports/IOrderRepository.h"

// IOrderRepository의 최소 스텁 구현. 실제 영속화는 범위 밖(PRD O3) —
// 이 저장소는 자동 실행을 배선(wiring)하는 데 필요한 만큼의 인메모리 저장만 제공한다.
class InMemoryOrderRepository : public IOrderRepository {
public:
    std::optional<OrderRecord> FindById(int64_t orderId) const override;
    std::vector<OrderRecord> FindAll() const override;
    std::vector<OrderRecord> FindByStatus(OrderStatus status) const override;
    std::vector<OrderRecord> FindBySampleId(const std::string& sampleId) const override;
    WriteOutcome Add(const OrderRecord& order) override;
    WriteOutcome Update(const OrderRecord& order) override;

private:
    std::unordered_map<int64_t, OrderRecord> records_;
};
