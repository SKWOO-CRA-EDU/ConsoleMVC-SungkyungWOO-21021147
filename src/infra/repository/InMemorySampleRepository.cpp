#include "InMemorySampleRepository.h"

std::optional<SampleRecord> InMemorySampleRepository::FindById(const std::string& sampleId) const {
    auto it = records_.find(sampleId);
    if (it == records_.end()) return std::nullopt;
    return it->second;
}

std::vector<SampleRecord> InMemorySampleRepository::FindAll() const {
    std::vector<SampleRecord> result;
    result.reserve(records_.size());
    for (const auto& [id, record] : records_) {
        result.push_back(record);
    }
    return result;
}

bool InMemorySampleRepository::Exists(const std::string& sampleId) const {
    return records_.find(sampleId) != records_.end();
}

void InMemorySampleRepository::Add(const SampleRecord& sample) {
    records_[sample.sampleId] = sample;
}

void InMemorySampleRepository::Update(const SampleRecord& sample) {
    records_[sample.sampleId] = sample;
}
