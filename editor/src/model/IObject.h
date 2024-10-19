#pragma once
#include "ObjectType.h"
#include "UUID.h"

#ifndef DIAGRAMS_IObject_H
#define DIAGRAMS_IObject_H
#endif

namespace model
{
class IObject
{
public:
	virtual ObjectType GetObjectType() const noexcept = 0;
	virtual UUID GetUUID() const noexcept = 0;

	~IObject() = default;
};
} // namespace model