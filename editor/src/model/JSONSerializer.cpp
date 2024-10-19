#include "JSONSerializer.h"
#include "Document.h"

namespace model
{
void JSONSerializer::SaveDocument(const std::filesystem::path&, const IDocument&) const
{
	// use IDocument::GetAllObjects();
	// serialize to json
}

IDocumentUniquePtr JSONSerializer::LoadDocument(const std::filesystem::path&) const
{
	// load from path IDocument;
	return std::unique_ptr<model::Document>();
}
} // namespace model