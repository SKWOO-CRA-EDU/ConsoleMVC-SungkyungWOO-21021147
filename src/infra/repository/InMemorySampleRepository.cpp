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

WriteOutcome InMemorySampleRepository::Add(const SampleRecord& sample) {
    if (records_.find(sample.sampleId) != records_.end()) return WriteOutcome::DuplicateKey;
    records_[sample.sampleId] = sample;
    return WriteOutcome::Ok;
}

WriteOutcome InMemorySampleRepository::Update(const SampleRecord& sample) {
    auto it = records_.find(sample.sampleId);
    if (it == records_.end()) return WriteOutcome::NotFound;
    it->second = sample;
    return WriteOutcome::Ok;
}

WriteOutcome InMemorySampleRepository::Delete(const std::string& sampleId) {
    auto it = records_.find(sampleId);
    if (it == records_.end()) return WriteOutcome::NotFound;
    records_.erase(it);
    return WriteOutcome::Ok;
}
