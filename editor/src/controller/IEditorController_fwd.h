#pragma once
#include <memory>

namespace controller
{
class IEditorController;
using IEditorControllerUniquePtr = std::unique_ptr<IEditorController>;
} // namespace controller