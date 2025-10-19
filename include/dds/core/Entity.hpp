#pragma once

namespace dds {
namespace core {

///
/// @class Entity
/// @brief The abstract base class for all DDS objects that support QoS,
/// listeners, and status conditions.
///
class Entity {
public:
    /// @brief Virtual destructor.
    virtual ~Entity() = default;

    /// @brief Enables the entity.
    /// Entity objects can be created disabled and enabled later.
    virtual void enable() = 0;

protected:
    // Protected constructor to make it an abstract class.
    Entity() = default;
};

} // namespace core
} // namespace dds

