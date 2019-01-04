// DcListScreen.h: interface for the DcListScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DCLISTSCREEN_H__INCLUDED_)
   #define _DCLISTSCREEN_H__INCLUDED_

   #include <ifastcsi\xplatform.h>
   #include <ifastcsi\CsiScreen.h>

class DcListScreen : public CsiScreen  
{
public:
   DcListScreen(const std::string &componentName, int topRow, int bottomRow);
   virtual ~DcListScreen();

   virtual void init() const;

private:
   int _topRow;
   int _bottomRow;

};

class DcListItemNotFound : public CsiException
{
public:
   DcListItemNotFound(const std::string &listItem)
   : _listItem(listItem){}

   virtual const std::string getMessage() {return("Required item not found in list \"" + _listItem);}
private:
   std::string _listItem;
};

#endif // !defined(_DCLISTSCREEN_H__INCLUDED_)
