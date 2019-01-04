#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : EntitySearchList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 03/11/99
//
// ^CLASS    : EntitySearchList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************





#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

namespace ENTITYSEARCHTYPE
{
   extern IFASTCBO_LINKAGE const int NO_SEARCH;
   extern IFASTCBO_LINKAGE const int USING_ACCOUNT_NUM;
   extern IFASTCBO_LINKAGE const int USING_SIN;
   extern IFASTCBO_LINKAGE const int USING_NAME;
   extern IFASTCBO_LINKAGE const int USING_SHAREHOLDER_NUM;
   extern IFASTCBO_LINKAGE const int USING_DRIVER_LICENSE;
   extern IFASTCBO_LINKAGE const int USING_PASSPORT;
   extern IFASTCBO_LINKAGE const int USING_BIRTH_CERTIFICATE;
   extern IFASTCBO_LINKAGE const int USING_CREDIT_CARD;
   extern IFASTCBO_LINKAGE const int USING_NATIONAL_ID;
   extern IFASTCBO_LINKAGE const int USING_SOCIAL_SEC_INS_CARD;
   extern IFASTCBO_LINKAGE const int USING_OTHER_ID;
   extern IFASTCBO_LINKAGE const int USING_ALT_ACCT_BRK_CODE;
   extern IFASTCBO_LINKAGE const int USING_BRK_CODE;
   extern IFASTCBO_LINKAGE const int USING_TELEPHONE_NUM;
   extern IFASTCBO_LINKAGE const int USING_BIRTH_NAME;
   extern IFASTCBO_LINKAGE const int USING_INTERMEDIARY;
   extern IFASTCBO_LINKAGE const int USING_OTHER_REFERENCE;
   extern IFASTCBO_LINKAGE const int USING_BUSINESSNO;
   extern IFASTCBO_LINKAGE const int USING_CIF;
   extern IFASTCBO_LINKAGE const int USING_ACCESS_ID;
   extern IFASTCBO_LINKAGE const int USING_CLEARING_PLATFORM_ID; //MT535/MT536
   extern IFASTCBO_LINKAGE const int USING_HOUSEHOLD;
   extern IFASTCBO_LINKAGE const int USING_CPFB_ACCNUM;
   extern IFASTCBO_LINKAGE const int USING_REGISTRATION_AGENT;
   extern IFASTCBO_LINKAGE const int USING_CPFB_ACCNUM;
   extern IFASTCBO_LINKAGE const int USING_ACCOUNT_MANAGER_UNIQUE_ID;
};

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE EntitySearchList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   EntitySearchList( BFAbstractCBO &parent );
   virtual ~EntitySearchList( void );
   // Initialize function
   SEVERITY init( int searchNdx, 
                  DString& field1, 
                  DString& field2,
                  bool searchForAllEntities = false, 
                  const DString& getExactSearch = I_( "N" ),
                  const DString& getAllEntity = I_( "N" ),
                  DString& field3 = DString(I_("")), 
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING, 
                  const DString& dstrOverrideRepeats = I_( "0" ), 
                  const DString& dstrNextOrPrevious = I_( "Y" ), 
                  const DString& getALLrecords = I_( "N" ) ); 

   SEVERITY init ( const DString &searchBy, 
                   const DString &firstName,
                   const DString &lastName,
                   const DString &sin, 
                   const DString &idType,
                   const DString &idValue, 
                   const DString &whereUse, 
                   const DString &fundCode = NULL_STRING,
                   const DString &dstrTrack = I_("N"),
                   const DString &dstrPageName = NULL_STRING);

   SEVERITY getMore();
   SEVERITY search();
   void setBrokerInfo ( const DString &BrokerCode, 
                        const DString& BranchCode, 
                        const DString& Slsrep);

protected:
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup);
private:
//methods
   bool containOnlyAllowedChars ( const DString &AllowedChars, 
                                  const DString &str );
   bool isStringEmptyOrJustContainSpace (const DString &str);
   void prepareSearch();
   //private
   DString _field1, 
      _field2,
      _field3,
      _getALLrecords;
   bool _searchForAllEntities,
      _usingBrokerInfo;
   BFData *_requestData;
   int _searchType;
};

///#endif

