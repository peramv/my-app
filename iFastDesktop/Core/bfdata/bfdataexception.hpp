#pragma once

#include <commonport.h>
#include <conditionexception.hpp>
#include <conditionmanager.hpp>
#include <deque>
#include <string>
#include <iosfwd>

// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif


#define BF_DECL_EXCEPTION( e, b ) class BFDATA_LINKAGE e : public b { public: e() : b() {} }
#define BF_DECL_BASE_EXCEPTION( e ) BF_DECL_EXCEPTION( e, BFDataException )
#define BF_THROW(e) throw e()
#define BF_RETHROW(e) throw

#define BF_DECL_CE_EXCEPTION( e, b ) \
   namespace CND { extern BFDATA_LINKAGE const long CND_##e; } \
   class BFDATA_LINKAGE e : public b { public: e( const I_CHAR* pszM, long code, const I_CHAR* codeStr, const DString& idiStr, const char* f, unsigned long l ) : b( pszM, code, codeStr, idiStr, f, l ) {} virtual const char* name() { return #e; } }
#define BF_DECL_BASE_CE_EXCEPTION( e ) BF_DECL_CE_EXCEPTION( e, BFDataCEException )
#define BF_CE_THROW( e, m ) throw e( (m), CND::CND_##e, CM_STRINGIFY(e) ,NULL_STRING, __FILE__, __LINE__ )
#define BF_CE_THROW_IDI( e, m, i ) throw e( (m), CND::CND_##e, CM_STRINGIFY(e), i, __FILE__, __LINE__ )
#define BF_CE_RETHROW( e ) throw

#pragma warning( disable: 4251 )

class BFDATA_LINKAGE BFDataException
{
};

class BFDATA_LINKAGE BFDataTracedException
{
public:
   BFDataTracedException( int code, const I_CHAR* codeStr, const char* pszFile = "", unsigned long line = 0 )
   : code_( code )
   , codeStr_( codeStr )
   {
      stack_.push_back( ThrowPoint( pszFile, line ) );
   }
   virtual ~BFDataTracedException(){}

   int getCode() const { return( code_ );}
   const DString& getCodeString() const { return(codeStr_); }

   class ThrowPoint
   {
   public:
      ThrowPoint( const char* fileName, unsigned long line )
      : fileName_( fileName )
      , line_( line )
      {}

      const std::string& getFile() const { return(fileName_);}
      unsigned long getLine() const { return(line_);}

   private:
      std::string    fileName_;
      unsigned long  line_;
   };

   void push( const char* pszFile, unsigned long line )
   {
      stack_.push_back( ThrowPoint( pszFile, line ) );
   }

   typedef std::deque< ThrowPoint > ThrowPointStack;

   void dump( std::ostream& os ) const
   {
      ThrowPointStack::const_iterator it;
      for( it = stack_.begin(); it != stack_.end(); ++it )
      {
         os << (*it).getFile().c_str() << "( " << (*it).getLine() << ")" << std::endl;
      }
   }

private:
   int               code_;
   DString           codeStr_;
   ThrowPointStack   stack_;
};


class BFDATA_LINKAGE BFDataCEException : public ConditionException
{
public:
   BFDataCEException( const I_CHAR* pszMethod, 
                      long code, 
                      const I_CHAR* codeStr,
                      const DString& idiStr,
                      const char* pszFile = "", 
                      unsigned long line = 0 )
   : ConditionException( s_componentName_, 
                         pszMethod, 
                         code, 
                         codeStr,
                         pszFile,
                         line,
                         0,
                         FALSE,
                         g_conditionManager.getPath(),
                         NO_SEVERITY,
                         idiStr )
   {
   }
   virtual ~BFDataCEException(){}
private:
   static const DString s_componentName_;
};
