#include "ObjectView.h"
#include "../controller/IDocumentController.h"
#include "../model/IObject.h"

namespace view
{
ObjectView::ObjectView(const model::IObject& object, controller::IDocumentController& documentController)
	: m_documentController(documentController)
	, m_object(object)
{
	// subscribe on UI for OnDelete
}

void ObjectView::DoOnDelete(std::function<void()> doOnDelete)
{
	m_doOnDelete = doOnDelete;
}

model::UUID ObjectView::GetObjectUUID() const
{
	return m_object.GetUUID();
}

void ObjectView::OnDelete()
{
	m_documentController.DeleteObject(m_object.GetUUID());
	if (m_doOnDelete)
	{
		m_doOnDelete();
	}
}

} // namespace view
