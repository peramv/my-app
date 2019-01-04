// DcMenu.h: interface for the DcMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DCMENU_H__INCLUDED_)
   #define _DCMENU_H__INCLUDED_

   #include <ifastcsi\xplatform.h>
   #include <ifastcsi\CsiScreen.h>

class DcMenu: public CsiScreen  
{
public:
   DcMenu(const std::string &componentName, int itemColumn,int c2 = 0);
   virtual ~DcMenu();

   virtual void select(const std::string &componentName) const;
   virtual bool trySelect(const std::string &componentName) const;
   virtual bool trySelect1(const std::string &componentName) const;

private:
   bool   isRect() const;
   bool   isInRect(TEPosition pos,TEPosition leftTop,TEPosition rightBtm ) const;
   int _itemColumn;
   int _itemColumn2;
};

class DcMenuItemNotIdentified : public CsiException
{
public:
   DcMenuItemNotIdentified(const std::string &menuItem)
   : _menuItem(menuItem){}

   virtual const std::string getMessage() {return("Menu Item \"" + _menuItem + "\" not identified in menu");}
private:
   std::string _menuItem;
};

#endif // !defined(_DCMENU_H__INCLUDED_)
