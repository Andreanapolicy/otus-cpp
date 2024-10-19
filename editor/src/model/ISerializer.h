#pragma once
#include "IDocument_fwd.h"
#include <filesystem>

#ifndef DIAGRAMS_ISerializer_H
#define DIAGRAMS_ISerializer_H
#endif

namespace model
{

class ISerializer
{
public:
	virtual void SaveDocument(const std::filesystem::path& path, const IDocument& document) const = 0;
	virtual model::IDocumentUniquePtr LoadDocument(const std::filesystem::path& path) const = 0;

	~ISerializer() = default;
};
} // namespace model