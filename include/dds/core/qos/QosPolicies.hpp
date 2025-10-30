#pragma once

#include <dds/core/Types.hpp> // For Duration_t
#include <vector>
// #include <cstdint> // For INT32_MAX

namespace dds {
namespace core {

// --- Basic QoS Kinds ---

enum class DurabilityKind : uint8_t {
    VOLATILE,
    
    // TRANSIENT, // Optional per spec
    // PERSISTENT // Optional per spec
};

enum class ReliabilityKind : uint8_t {
    BEST_EFFORT,
    RELIABLE
};

enum class HistoryKind : uint8_t {
    KEEP_LAST,
    KEEP_ALL
};

// --- QoS Policy Structs ---
// Based on DDS Spec Section 2.2.3

struct DurabilityQosPolicy {
    DurabilityKind kind = DurabilityKind::VOLATILE;
};

struct ReliabilityQosPolicy {
    ReliabilityKind kind = ReliabilityKind::BEST_EFFORT;
    //Duration_t max_blocking_time = {0, 100000000}; // Default 100ms
};

struct HistoryQosPolicy {
    HistoryKind kind = HistoryKind::KEEP_LAST;
    int32_t depth = 1;
};

// Represents LENGTH_UNLIMITED from the spec
const int32_t LENGTH_UNLIMITED = -1;

struct ResourceLimitsQosPolicy {
    int32_t max_samples = LENGTH_UNLIMITED;
    int32_t max_instances = LENGTH_UNLIMITED;
    int32_t max_samples_per_instance = LENGTH_UNLIMITED;
};

// Add other policies as needed in future phases...
// struct UserDataQosPolicy { std::vector<uint8_t> value; };
// struct DeadlineQosPolicy { Duration_t period; };
// struct LatencyBudgetQosPolicy { Duration_t duration; };
// etc.


} // namespace core
} // namespace dds