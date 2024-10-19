#pragma once
#include "IObject.h"

namespace model
{
class BaseObject : public IObject
{
public:
	explicit BaseObject(ObjectType type)
		: m_type{ type }
		, m_uuid{ "fake_uuid" }
	{
	}

	ObjectType GetObjectType() const noexcept override
	{
		return m_type;
	}

	UUID GetUUID() const noexcept override
	{
		return m_uuid;
	}

private:
	ObjectType m_type;
	UUID m_uuid;
};
} // namespace model