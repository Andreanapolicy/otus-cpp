#pragma once
#include "../controller/IDocumentController_fwd.h"
#include "../model/IObject_fwd.h"
#include "../model/UUID.h"
#include <functional>
#include <memory>
#include <vector>

namespace view
{
class ObjectView
{
public:
	ObjectView(const model::IObject& object, controller::IDocumentController& documentController);

	void DoOnDelete(std::function<void()> doOnDelete);
	model::UUID GetObjectUUID() const;

private:
	void OnDelete();

	controller::IDocumentController& m_documentController;
	const model::IObject& m_object;
	std::function<void()> m_doOnDelete;
};
} // namespace view