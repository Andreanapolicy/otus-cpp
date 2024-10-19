#pragma once
#include <memory>

namespace controller
{
class IDocumentController;
using IDocumentControllerUniquePtr = std::unique_ptr<IDocumentController>;

} // namespace controller