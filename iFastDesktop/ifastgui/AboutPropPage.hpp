#pragma once

#include <sstream>

class AboutPropPage {
public:
   virtual void generateReport( std::wstringstream& ss ) = 0;
};

