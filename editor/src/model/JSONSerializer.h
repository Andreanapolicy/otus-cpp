#pragma once
#include "ISerializer.h"

namespace model
{
class IDocument;

class JSONSerializer : public ISerializer
{
public:
	JSONSerializer() = default;

	void SaveDocument(const std::filesystem::path& path, const IDocument& document) const override;
	IDocumentUniquePtr LoadDocument(const std::filesystem::path& path) const override;
};
} // namespace model