#include "ObjectFactory.h"
#include "BaseObject.h"

namespace model
{
std::unique_ptr<IObject> ObjectFactory::CreateObject(ObjectType type)
{
	return std::make_unique<BaseObject>(type);
}
} // namespace model