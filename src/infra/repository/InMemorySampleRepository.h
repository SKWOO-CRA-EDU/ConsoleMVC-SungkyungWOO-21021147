#pragma once
#include <unordered_map>
#include "../../ports/ISampleRepository.h"

// ISampleRepository의 최소 스텁 구현. 실제 영속화(파일 저장 등)는 범위 밖(PRD O3) —
// 이 저장소는 자동 실행을 배선(wiring)하는 데 필요한 만큼의 인메모리 저장만 제공한다.
class InMemorySampleRepository : public ISampleRepository {
public:
    std::optional<SampleRecord> FindById(const std::string& sampleId) const override;
    std::vector<SampleRecord> FindAll() const override;
    WriteOutcome Add(const SampleRecord& sample) override;
    WriteOutcome Update(const SampleRecord& sample) override;
    WriteOutcome Delete(const std::string& sampleId) override;

private:
    std::unordered_map<std::string, SampleRecord> records_;
};
