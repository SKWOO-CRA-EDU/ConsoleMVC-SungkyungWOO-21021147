#pragma once
#include <optional>
#include <string>
#include <vector>
#include "../domain/Records.h"

// CONTRACT.md §5 — 시그니처 그대로. 구현 금지(선언만); 실제 구현은 타 저장소 책임.
class ISampleRepository {
public:
    virtual ~ISampleRepository() = default;
    virtual std::optional<SampleRecord> FindById(const std::string& sampleId) const = 0;
    virtual std::vector<SampleRecord> FindAll() const = 0;
    virtual bool Exists(const std::string& sampleId) const = 0;
    virtual void Add(const SampleRecord& sample) = 0;
    virtual void Update(const SampleRecord& sample) = 0;
};
