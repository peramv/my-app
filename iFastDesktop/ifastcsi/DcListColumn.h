// DcListColumn.h: interface for the DcListColumn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DCLISTCOLUMN_H__INCLUDED_)
   #define _DCLISTCOLUMN_H__INCLUDED_

   #include <ifastcsi\xplatform.h>
   #include <ifastcsi\CsiComponent.h>

class DcListColumn : public CsiComponent  
{
public:
   DcListColumn(const std::string &componentName, int column=0);
   virtual ~DcListColumn();

   int getColumn() const {return(_column);}
private:
   int _column;
};

#endif // !defined(_DCLISTCOLUMN_H__INCLUDED_)
