#include "DocumentController.h"
#include "../model/IDocument.h"

namespace controller
{
DocumentController::DocumentController(model::IDocument& document)
	: m_document(document)
{
}

void DocumentController::AddObject(model::ObjectType type)
{
	m_document.AddObject(type);
}

void DocumentController::DeleteObject(model::UUID uuid)
{
	m_document.DeleteObject(uuid);
}

} // namespace controller