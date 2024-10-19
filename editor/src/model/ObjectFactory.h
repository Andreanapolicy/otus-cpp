#pragma once
#include "IObject.h"
#include <memory>

namespace model
{
class ObjectFactory
{
public:
	[[nodiscard]] static std::unique_ptr<IObject> CreateObject(ObjectType type);
};
} // namespace model