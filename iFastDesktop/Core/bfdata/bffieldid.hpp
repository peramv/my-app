#pragma once

#include <bfdata\bfdataexception.hpp>

#include <DString.hpp>
#include <map>

// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif

class BFFieldId;
class BFData;

BF_DECL_BASE_CE_EXCEPTION( BFFieldIdUnknownException );

BF_DECL_BASE_EXCEPTION( BFFieldIdException );
BF_DECL_EXCEPTION( BFFieldIdOpException, BFFieldIdException );

class BFDATA_LINKAGE BFFieldId 
{
public:
   BFFieldId()
   : id_( 0 )
#ifdef _DEBUG
   , name_( I_( "" ) )
#endif
   {}
   BFFieldId( long idField,
              const I_CHAR * name );

   explicit BFFieldId( long idField )
   : id_( idField )
#ifdef _DEBUG
   , name_( I_( "" ) )
#endif
   {}

   ~BFFieldId();

   BFFieldId( const BFFieldId& rhs ) { *this = rhs;}
   BFFieldId& operator=( const BFFieldId& rhs );

   bool operator>( const BFFieldId& rhs ) const { return( id_ > rhs.id_ );}
   bool operator>=( const BFFieldId& rhs ) const { return( id_ >= rhs.id_ );}
   bool operator<( const BFFieldId& rhs ) const { return( id_ < rhs.id_ );}
   bool operator<=( const BFFieldId& rhs ) const { return( id_ <= rhs.id_ );}
   bool operator!=( const BFFieldId& rhs ) const { return( id_ != rhs.id_ );}
   bool operator==( const BFFieldId& rhs ) const { return( id_ == rhs.id_ );}

   const DString& getName() const;
   static const DString& getName( long id );

   long getId() const { return(id_);}
   static const BFFieldId& getId( const DString& name );

   bool isDynamic() const;

   static void setOptions( unsigned long fOpt );
   static unsigned long getOptions();

   static const unsigned long allowDynamic;

protected:
   friend class BFData;

   static const BFFieldId* _getId( const DString& name );
   static const BFFieldId* _getStaticId( const DString& name );
   static const BFFieldId* _getDynamicId( const DString& name );

private:
   long  id_;
#ifdef _DEBUG
   I_CHAR* name_;
#endif
};

class BFDateFieldId : public BFFieldId
{
public:
   BFDateFieldId( long idField, const I_CHAR* name )
   : BFFieldId( idField, name )
   {}
};

class BFTimeFieldId : public BFFieldId
{
public:
   BFTimeFieldId( long idField, const I_CHAR* name )
   : BFFieldId( idField, name )
   {}
};

class BFVarTextFieldId : public BFFieldId
{
public:
   BFVarTextFieldId( long idField, const I_CHAR* name )
   : BFFieldId( idField, name )
   {}
};

class BFTextFieldId : public BFFieldId
{
public:
   BFTextFieldId( long idField, const I_CHAR* name )
   : BFFieldId( idField, name )
   {}
};

class BFIntegerFieldId : public BFFieldId
{
public:
   BFIntegerFieldId( long idField, const I_CHAR* name )
   : BFFieldId( idField, name )
   {}
};

class BFNumericFieldId : public BFFieldId
{
public:
   BFNumericFieldId( long idField, const I_CHAR* name )
   : BFFieldId( idField, name )
   {}
};

class BFDecimalFieldId : public BFFieldId
{
public:
   BFDecimalFieldId( long idField, const I_CHAR* name )
   : BFFieldId( idField, name )
   {}
};

class BFBigDecimalFieldId : public BFFieldId
{
public:
   BFBigDecimalFieldId( long idField, const I_CHAR* name )
   : BFFieldId( idField, name )
   {}
};

class BFDATA_LINKAGE BFNullFieldId : public BFFieldId
{
public:
   BFNullFieldId( long idField, const I_CHAR* name );
};

class BFDATA_LINKAGE BFDummyFieldId : public BFFieldId
{
public:
   explicit BFDummyFieldId( long idField );
};

namespace ifds
{
   extern BFDATA_LINKAGE const BFNullFieldId NullFieldId;
   extern BFDATA_LINKAGE const BFFieldId MaxFieldId;
}

// arithmetic operations on BFFieldId are not allowed...
const BFFieldId operator+( const BFFieldId& lhs, const BFFieldId& rhs );
const BFFieldId operator+( int lhs, const BFFieldId& rhs );
const BFFieldId operator+( const BFFieldId& lhs, int rhs );


extern const BFVarTextFieldId idVarTextField;


