// DcMenuItem.h: interface for the DcMenuItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DCMENUITEM_H__INCLUDED_)
   #define _DCMENUITEM_H__INCLUDED_

   #include <ifastcsi\xplatform.h>
   #include <ifastcsi\CsiComponent.h>

class DcMenuItem : public CsiComponent  
{
public:
   DcMenuItem(const std::string &componentName);
   virtual ~DcMenuItem();

};

#endif // !defined(_DCMENUITEM_H__INCLUDED_)
