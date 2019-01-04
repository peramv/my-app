#pragma once

#include <ifastgui/SiteConfig.h>
#include "afxwin.h"

class BaseConfigPage {
public:
   BaseConfigPage( CPropertyPage* pPage ) 
   : pPage_( pPage ) 
   {}
   virtual ~BaseConfigPage()
   {}

private:
   CPropertyPage* pPage_;
};