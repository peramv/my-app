// DcInputField.h: interface for the DcInputField class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DCINPUTFIELD_H__NCLUDED_)
   #define _DCINPUTFIELD_H__NCLUDED_

   #if _MSC_VER > 1000
      #pragma once
   #endif // _MSC_VER > 1000

   #include <ifastcsi\CsiComponent.h>

class DcInputField : public CsiComponent  
{
public:
   DcInputField(const std::string &componentName, int row, int column, int tabOrder);
   virtual ~DcInputField();

   int getTabOrder() const { return(_tabOrder);}
   int getRow() const { return(_row);}
   int getColumn() const { return(_column);}

private:

   int _row;
   int _column;
   int _tabOrder;

};

#endif // !defined(_DCINPUTFIELD_H__NCLUDED_)
