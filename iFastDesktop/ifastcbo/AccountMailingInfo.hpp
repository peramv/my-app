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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AccountMailingInfo.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 11/17/99
//
// ^CLASS    : AccountMailingInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class AccountMailingList;
class Entity;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif



class IFASTCBO_LINKAGE AccountMailingInfo : public MFCanBFCbo, private boost::noncopyable
{
public:
   AccountMailingInfo( BFAbstractCBO &parent );
   virtual ~AccountMailingInfo();

   SEVERITY init( const BFData &InstData, const DString& shrNum );
   SEVERITY init( const BFDataGroupId& idDataGroup, const DString& shrNum ); //for creating new object

   //this is used to set the initial key of the object, 
   //since the key is the account number we could modify this and we have to recreate the keys on commit
   void setInitialStrKey( const DString& strKey );
   void setWorkingFlag( bool Flag );
   bool isWorking();
   void setObjectUpdated(const BFDataGroupId& idDataGroup);
   SEVERITY setDefaultValue( const BFDataGroupId& idDataGroup );
   SEVERITY setDefaultValueforReturnMail( const DString& strAddrCode, const BFDataGroupId& idDataGroup );
   bool isDocumentTypeOnHold(const DString& docType,const BFDataGroupId& idDataGroup);

   bool isEmailExist(const BFDataGroupId& idDataGroup );
   bool isFaxExist(const BFDataGroupId& idDataGroup );
   SEVERITY getMailOptionSubstitutionByDocKey(const DString &strDocKey, 
                                              const BFDataGroupId &idDataGroup, 
                                              BFFieldId &fieldID);

   SEVERITY setHoldFlagForAddrCode(const DString &dstrAddrCode, const DString &dstrHoldFlag, const DString &dstrRetMailFlag, const BFDataGroupId &idDataGroup);
   SEVERITY setAuthorizedFlagForAddrCode(const DString &dstrAddrCode, const DString &dstrAuthorization, const DString &dstrRetMailFlag, const BFDataGroupId &idDataGroup);

protected:
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual const DString *getInitialStrKey();
   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ); 
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY initMailColSubstitutionSet(const BFDataGroupId& idDataGroup);

private:
   bool _bWorkingFlag;
   DString _shrNum;
//CP20020409   DString _AccountMailingInfoCode;
   bool isAllDigit( const DString& strValue );
   void setUpMailingSubstitute(const BFDataGroupId& idDataGroup );
   //void  getValueFromListToField(BFFieldId& lList, BFFieldId bfField[],const BFDataGroupId& idDataGroup);
   void  buildMailingOption(const BFDataGroupId& idDataGroup);
// void setValueForList(BFFieldId& lList, BFFieldId bfFieldId[],const BFDataGroupId& idDataGroup);
// void combineMailingValue(const BFDataGroupId& idDataGroup);
   void setupMailing();
   void clearMailmap();		
   void setMailingFieldsReadonly(const BFDataGroupId& idDataGroup);

   SEVERITY getFirstSequenced01AccountholderObject( const BFDataGroupId& idDataGroup, DString& AcctNum,Entity *&pEntityOut   );
   SEVERITY validateFax(const BFFieldId& idField, DString strValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateEmail(const BFFieldId& idField, DString strValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateSuppress(const BFDataGroupId& idDataGroup);
   SEVERITY WaivePaperRelatedChange(const BFFieldId& idField, const BFDataGroupId& idDataGroup);
   SEVERITY validateWaive( const BFDataGroupId& idDataGroup);
   SEVERITY validateMailingOption( const BFDataGroupId& idDataGroup ); 
   SEVERITY setDefaultStatementfrequency( const BFDataGroupId& idDataGroup);
   SEVERITY setStatementfrequency( const BFDataGroupId& idDataGroup);
   SEVERITY setNonDataBaseFields( const BFDataGroupId& idDataGroup);
   SEVERITY validateMail(const BFFieldId& idField, DString strValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateAccountHold( const BFFieldId& idField,const BFDataGroupId& idDataGroup );
   bool isDeliveryOptionApply( const BFDataGroupId& idDataGroup );
   SEVERITY authorizRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   DString getMailOption(BFFieldId& lFieldId, int iPos,const BFDataGroupId& idDataGroup );
   void setupSubstitutionList( const BFDataGroupId& idDataGroup);
   SEVERITY holdRelatedChanges( const BFFieldId& idField, 
                                const BFDataGroupId& idDataGroup );

   SEVERITY  validateAuthHold( const BFDataGroupId& idDataGroup );
   DString objectKey_;
   class Mailing
   {
   public:
      Mailing(DString dstrCode, 
              BFFieldId& lSuppress,
              BFFieldId& lWaive,
              BFFieldId& lMail,
              BFFieldId& lFax,
              BFFieldId& lCD,
              BFFieldId& lEmail,
              BFFieldId& lHold, 
              BFFieldId& lEpost,
              BFFieldId& lAuthorize, 
              BFFieldId& lAddr,
              BFFieldId& lFreq )
      {
         this->lSuppress = lSuppress;
         this->lWaive = lWaive;
         this->lMail = lMail;
         this->lFax =  lFax;
         this->lCD =  lCD;
         this->lHold = lHold;
         this->lEmail = lEmail;
         this->lEpost = lEpost; 
         this->dstrDocCode = dstrCode;
         this->lAuthorize = lAuthorize;
         this->lAddr = lAddr;
         this->lFreq = lFreq; 
      }
      BFFieldId getSuppress(){return lSuppress;}
      BFFieldId getMail(){return lMail;}
      BFFieldId getWaive(){return lWaive;}
      BFFieldId getFax(){return lFax;}
      BFFieldId getCD(){return lCD;}
      BFFieldId getEmail(){return lEmail;}
      DString   getCode(){return dstrDocCode;}
      BFFieldId getHold(){return lHold;}
      BFFieldId getEpost(){return lEpost;}
      BFFieldId getAuthorize(){return lAuthorize;}
      BFFieldId getAddr(){return lAddr;}
      BFFieldId getInvstFrequency() {return lFreq;} 

   private:
      BFFieldId lSuppress;
      BFFieldId lWaive;
      BFFieldId lMail;
      BFFieldId lFax;
      BFFieldId lCD;
      BFFieldId lEmail;
      BFFieldId lHold;
      BFFieldId lEpost;
      BFFieldId lAuthorize;
      BFFieldId lAddr;
      BFFieldId lFreq;
      DString dstrDocCode;
   };

   typedef std::map< DString, Mailing* > MAIL_MAP;
   typedef MAIL_MAP::iterator           MAIL_MAP_ITER;
   typedef MAIL_MAP::value_type         MAIL_MAP_VALUE_TYPE;
   MAIL_MAP                             _mailmap;



//CP20020409   AccountMailingInfo( const AccountMailingInfo& copy );
//CP20020409   // = Operator
//CP20020409   AccountMailingInfo& operator= ( const AccountMailingInfo& copy );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountMailingInfo.hpp-arc  $
 * 
 *    Rev 1.21   Jan 19 2012 12:10:50   wp040132
 * Minerva ISF Code changes..
 * 
 *    Rev 1.20   Jul 28 2006 10:44:22   fengyong
 * Incident #672869 - Ret mail flag refresh
 * 
 *    Rev 1.19   Sep 21 2005 16:44:58   yingbaol
 * PEt1277,FN09: Investment Fund Continuous Disclosure
 * 
 *    Rev 1.18   Dec 02 2004 11:36:50   yingbaol
 * PET1137,FN01: Add Epost functionality.
 * 
 *    Rev 1.17   Apr 15 2003 10:23:40   YINGBAOL
 * sync. version 1.14.1.0
 * 
 *    Rev 1.16   Apr 04 2003 16:37:00   FENGYONG
 * make isfaxexist and ismailexis public
 * 
 *    Rev 1.15   Mar 21 2003 17:54:56   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.14   Oct 30 2002 10:12:18   YINGBAOL
 * sync. up from old PVCS database
 * 
 *    Rev 1.13   Oct 21 2002 11:21:32   YINGBAOL
 * more business rules added
 * 
 *    Rev 1.12   Oct 09 2002 14:34:56   YINGBAOL
 * add validateMailingOption
 * 
 *    Rev 1.11   Oct 08 2002 11:47:46   YINGBAOL
 * split list to mailing fields-- view change
 * 
 *    Rev 1.10   Sep 23 2002 15:22:32   YINGBAOL
 * more business rules added
 * 
 *    Rev 1.9   Aug 29 2002 12:51:30   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   Aug 02 2002 14:28:34   KOVACSRO
 * moved setDefaultValue to public.
 * 
 *    Rev 1.7   22 May 2002 18:22:06   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   19 Mar 2002 13:14:50   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.5   03 May 2001 14:03:38   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.4   Aug 15 2000 10:26:56   YINGBAOL
 * FIX NASU AND OTHER BUGS FOR c2
 * 
 *    Rev 1.3   Aug 02 2000 11:08:30   KOVACSRO
 * fixes
 * 
 *    Rev 1.1   Feb 15 2000 18:56:10   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:58:54   SMITHDAV
 * Initial revision.
// 
//    Rev 1.7   Jan 23 2000 16:59:28   POPESCUS
// fixes related to accessing the lists and rolling back a cloned account
// 
//    Rev 1.6   Jan 21 2000 11:11:38   POPESCUS
// the user can change the account number and the shareholder number
// 
//    Rev 1.5   Jan 19 2000 10:46:42   POPESCUS
// probably, some fixes
// 
//    Rev 1.4   Jan 14 2000 15:09:28   YINGBAOL
// modify validation
// 
//    Rev 1.3   Jan 06 2000 13:37:36   YINGBAOL
// change
// 
//    Rev 1.2   Dec 21 1999 10:14:36   YINGBAOL
// added validation
// 
//    Rev 1.1   Dec 08 1999 09:50:08   YINGBAOL
// fix Nasu bug
*/

