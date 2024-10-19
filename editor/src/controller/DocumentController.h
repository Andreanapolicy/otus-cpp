#pragma once
#include "IDocumentController.h"

namespace model
{
class IDocument;
}

namespace controller
{
class DocumentController : public IDocumentController
{
public:
	DocumentController(model::IDocument& document); // TODO: remove IDocument from private members

	void AddObject(model::ObjectType type) override;
	void DeleteObject(model::UUID uuid) override;

private:
	model::IDocument& m_document;
};

} // namespace controller