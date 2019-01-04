// DcInputScreen.h: interface for the DcInputScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DCINPUTSCREEN_H__INCLUDED_)
   #define _DCINPUTSCREEN_H__INCLUDED_

   #include <ifastcsi\xplatform.h>
   #include <ifastcsi\CsiScreen.h>

class DcInputScreen: public CsiScreen  
{
public:
   DcInputScreen(const std::string &componentName);
   virtual ~DcInputScreen();

   virtual void init() const;

private:
};

class DcInputFieldNotFound : public CsiException
{
public:
   DcInputFieldNotFound(const std::string &inputField, int row, int column)
   : _inputField(inputField), _row(row), _column(column) {}

   virtual const std::string getMessage() {return("Input field \"" + _inputField + "\" not reached");}
private:
   std::string _inputField;
   int _row;
   int _column;
};

#endif // !defined(_DCINPUTSCREEN_H__INCLUDED_)
