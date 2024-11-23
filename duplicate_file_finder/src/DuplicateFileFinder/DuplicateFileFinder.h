#pragma once
#include "../InputData/InputData.h"

class DuplicateFileFinder
{
public:
	explicit DuplicateFileFinder(InputData data);

    void Find();

private:
    class Impl;

    std::shared_ptr<Impl> m_impl;
};