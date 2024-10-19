#pragma once
#include "../model/IDocument_fwd.h"
#include <filesystem>

namespace controller
{
class IEditorController
{
public:
	virtual void SaveDocument(const std::filesystem::path& path) const = 0;
	virtual model::IDocumentUniquePtr LoadDocument(const std::filesystem::path& path) = 0;

	~IEditorController() = default;
};
} // namespace controller