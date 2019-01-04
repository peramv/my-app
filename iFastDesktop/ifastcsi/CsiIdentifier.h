// CsiIdentifier.h: interface for the CsiIdentifier class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CSIIDENTIFIER_H__INCLUDED_)
   #define _CSIIDENTIFIER_H__INCLUDED_

   #include <ifastcsi\xplatform.h>

   #include <ifastcsi\CsiComponent.h>

class CsiIdentifier : public CsiComponent  
{
public:
   CsiIdentifier(const std::string &componentName, int r, int c);
//	CsiIdentifier(const std::string &componentName, const std::string &idText, int r, int c);
   CsiIdentifier(const std::string &componentName, const std::string &idText, int r1, int c1,int r2 = 0,int c2 = 0);

   virtual ~CsiIdentifier();

   int getRow() const {return(_row);}
   int getColumn() const {return(_column);}
   void getRect(int& r1, int& c1, int& r2, int& c2) const 
   {
      r1 = _row;   c1 = _column; r2 = _rRightBtm; c2 = _cRightBtm;
   }
   const std::string &getIdText() const {return(_idText);}
   bool isRect() const;

   virtual void wait(long timeout) const;
   virtual bool tryWait(long timeout) const;

private:
   int _row;
   int _column;
   int _rRightBtm,_cRightBtm;
   std::string _idText;
};

#endif // !defined(_CSIIDENTIFIER_H__INCLUDED_)
