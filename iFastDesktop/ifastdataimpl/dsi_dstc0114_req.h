// BFDataImpl header file for DataSet DSTC0114.REQ
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 15:59:59 2015


#pragma once
#include <commonport.h>
#include <clientlocale.hpp>

#undef IFAST_DATAIMPL_LINKAGE
#ifdef IFAST_DATAIMPL_DLL
   #define IFAST_DATAIMPL_LINKAGE CLASS_EXPORT
#else
   #define IFAST_DATAIMPL_LINKAGE CLASS_IMPORT
#endif

namespace ifds
{
   //Field Externs
   extern const BFTextFieldId SessionId;
   extern const BFTextFieldId User_Id;
   extern const BFTextFieldId LanguageCode;
   extern const BFTextFieldId CompanyId;
   extern const BFTextFieldId RunMode;
   extern const BFTextFieldId RegAddr;
   extern const BFTextFieldId DivConfAddr;
   extern const BFTextFieldId DivChqAddr;
   extern const BFTextFieldId TxnConfAddr;
   extern const BFTextFieldId DupConfAddr;
   extern const BFTextFieldId StmtAddr;
   extern const BFTextFieldId DupStmtAddr;
   extern const BFTextFieldId CertAddr;
   extern const BFTextFieldId TaxAddr;
   extern const BFTextFieldId LetAddr;
   extern const BFTextFieldId BenAddr;
   extern const BFNumericFieldId DupConfCopies;
   extern const BFNumericFieldId DupStmtCopies;
   extern const BFTextFieldId RegOnHold;
   extern const BFTextFieldId DivConfOnHold;
   extern const BFTextFieldId DivChqOnHold;
   extern const BFTextFieldId TxnConfOnHold;
   extern const BFTextFieldId DupConfOnHold;
   extern const BFTextFieldId StmtOnHold;
   extern const BFTextFieldId DupStmtOnHold;
   extern const BFTextFieldId CertOnHold;
   extern const BFTextFieldId TaxOnHold;
   extern const BFTextFieldId LetOnHold;
   extern const BFTextFieldId BenOnHold;
   extern const BFTextFieldId SATxnConfCode;
   extern const BFTextFieldId SADivConfCode;
   extern const BFTextFieldId SALettersCode;
   extern const BFNumericFieldId AcctMstrVer;
   extern const BFTextFieldId NFCAddr;
   extern const BFTextFieldId NFConHold;
   extern const BFNumericFieldId AccountNum;
   extern const BFDecimalFieldId AcctMstrRid;
   extern const BFTextFieldId Track;
   extern const BFTextFieldId Activity;
   extern const BFTextFieldId ContrAddr;
   extern const BFTextFieldId ContrHold;
   extern const BFTextFieldId AnnlRptsAddr;
   extern const BFTextFieldId AnnlRptsHold;
   extern const BFTextFieldId ProspAddr;
   extern const BFTextFieldId ProspHold;
   extern const BFTextFieldId TaxSuppress;
   extern const BFTextFieldId TaxWaive;
   extern const BFTextFieldId TaxMail;
   extern const BFTextFieldId TaxFax;
   extern const BFTextFieldId TaxCD;
   extern const BFTextFieldId TaxEmail;
   extern const BFTextFieldId LetSuppress;
   extern const BFTextFieldId LetWaive;
   extern const BFTextFieldId LetMail;
   extern const BFTextFieldId LetFax;
   extern const BFTextFieldId LetCD;
   extern const BFTextFieldId LetEmail;
   extern const BFTextFieldId CertSuppress;
   extern const BFTextFieldId CertWaive;
   extern const BFTextFieldId CertMail;
   extern const BFTextFieldId CertCD;
   extern const BFTextFieldId CertEmail;
   extern const BFTextFieldId CertFax;
   extern const BFTextFieldId DivConfSuppress;
   extern const BFTextFieldId DivConfWaive;
   extern const BFTextFieldId DivConfMail;
   extern const BFTextFieldId DivConfFax;
   extern const BFTextFieldId DivConfCD;
   extern const BFTextFieldId DivConfEmail;
   extern const BFTextFieldId DivChqSuppress;
   extern const BFTextFieldId DivChqWaive;
   extern const BFTextFieldId DivChqMail;
   extern const BFTextFieldId DivChqFax;
   extern const BFTextFieldId DivChqCD;
   extern const BFTextFieldId DivChqEmail;
   extern const BFTextFieldId RegSuppress;
   extern const BFTextFieldId RegWaive;
   extern const BFTextFieldId RegMail;
   extern const BFTextFieldId RegFax;
   extern const BFTextFieldId RegCD;
   extern const BFTextFieldId RegEmail;
   extern const BFTextFieldId AnnlRptsSuppress;
   extern const BFTextFieldId AnnlRptsWaive;
   extern const BFTextFieldId AnnlRptsMail;
   extern const BFTextFieldId AnnlRptsFax;
   extern const BFTextFieldId AnnlRptsCD;
   extern const BFTextFieldId AnnlRptsEmail;
   extern const BFTextFieldId ProspSuppress;
   extern const BFTextFieldId ProspWaive;
   extern const BFTextFieldId ProspMail;
   extern const BFTextFieldId ProspFax;
   extern const BFTextFieldId ProspCD;
   extern const BFTextFieldId ProspEmail;
   extern const BFTextFieldId BenSuppress;
   extern const BFTextFieldId BenWaive;
   extern const BFTextFieldId BenMail;
   extern const BFTextFieldId BenFax;
   extern const BFTextFieldId BenCD;
   extern const BFTextFieldId BenEmail;
   extern const BFTextFieldId StmtSuppress;
   extern const BFTextFieldId StmtWaive;
   extern const BFTextFieldId StmtMail;
   extern const BFTextFieldId StmtFax;
   extern const BFTextFieldId StmtCD;
   extern const BFTextFieldId StmtEmail;
   extern const BFTextFieldId DupStmtSuppress;
   extern const BFTextFieldId DupStmtWaive;
   extern const BFTextFieldId DupStmtMail;
   extern const BFTextFieldId DupStmtFax;
   extern const BFTextFieldId DupStmtCD;
   extern const BFTextFieldId DupStmtEmail;
   extern const BFTextFieldId NFConfSuppress;
   extern const BFTextFieldId NFConfWaive;
   extern const BFTextFieldId NFConfMail;
   extern const BFTextFieldId NFConfFax;
   extern const BFTextFieldId NFConfCD;
   extern const BFTextFieldId NFConfEmail;
   extern const BFTextFieldId TxnConfSuppress;
   extern const BFTextFieldId TxnConfWaive;
   extern const BFTextFieldId TxnConfMail;
   extern const BFTextFieldId TxnConfFax;
   extern const BFTextFieldId TxnConfCD;
   extern const BFTextFieldId TxnConfEmail;
   extern const BFTextFieldId DupConfSuppress;
   extern const BFTextFieldId DupConfWaive;
   extern const BFTextFieldId DupConfMail;
   extern const BFTextFieldId DupConfFax;
   extern const BFTextFieldId DupConfCD;
   extern const BFTextFieldId DupConfEmail;
   extern const BFTextFieldId ContrSuppress;
   extern const BFTextFieldId ContrWaive;
   extern const BFTextFieldId ContrMail;
   extern const BFTextFieldId ContrFax;
   extern const BFTextFieldId ContrCD;
   extern const BFTextFieldId ContrEmail;
   extern const BFTextFieldId SemiAnnualSuppress;
   extern const BFTextFieldId SemiAnnualWaive;
   extern const BFTextFieldId SemiAnnualMail;
   extern const BFTextFieldId SemiAnnualFax;
   extern const BFTextFieldId SemiAnnualCD;
   extern const BFTextFieldId SemiAnnualEmail;
   extern const BFTextFieldId SemiAnnualAddr;
   extern const BFTextFieldId SemiAnnualOnHold;
   extern const BFTextFieldId TaxEpost;
   extern const BFTextFieldId LetEpost;
   extern const BFTextFieldId CertEpost;
   extern const BFTextFieldId DivConfEpost;
   extern const BFTextFieldId DivChqEpost;
   extern const BFTextFieldId ContrEPost;
   extern const BFTextFieldId RegEpost;
   extern const BFTextFieldId AnnlRptsEpost;
   extern const BFTextFieldId ProspEpost;
   extern const BFTextFieldId BenEpost;
   extern const BFTextFieldId StmtEpost;
   extern const BFTextFieldId DupStmtEpost;
   extern const BFTextFieldId NFConfEpost;
   extern const BFTextFieldId TxnConfEpost;
   extern const BFTextFieldId DupConfEpost;
   extern const BFTextFieldId SemiAnnualEpost;
   extern const BFTextFieldId ContributionSuppress;
   extern const BFTextFieldId ContributionWaive;
   extern const BFTextFieldId ContributionMail;
   extern const BFTextFieldId ContributionFax;
   extern const BFTextFieldId ContributionCD;
   extern const BFTextFieldId ContributionEmail;
   extern const BFTextFieldId ContributionEpost;
   extern const BFTextFieldId ContributionAddr;
   extern const BFTextFieldId ContributionOnHold;
   extern const BFTextFieldId SmAnnlMRFPAddr;
   extern const BFTextFieldId SmAnnlMRFPSuppress;
   extern const BFTextFieldId SmAnnlMRFPWaive;
   extern const BFTextFieldId SmAnnlMRFPHold;
   extern const BFTextFieldId SmAnnlMRFPMail;
   extern const BFTextFieldId SmAnnlMRFPFax;
   extern const BFTextFieldId SmAnnlMRFPCD;
   extern const BFTextFieldId SmAnnlMRFPEmail;
   extern const BFTextFieldId SmAnnlMRFPEpost;
   extern const BFTextFieldId SmAnnlMRFPAuth;
   extern const BFTextFieldId AnnlMRFPAddr;
   extern const BFTextFieldId AnnlMRFPSuppress;
   extern const BFTextFieldId AnnlMRFPWaive;
   extern const BFTextFieldId AnnlMRFPHold;
   extern const BFTextFieldId AnnlMRFPMail;
   extern const BFTextFieldId AnnlMRFPFax;
   extern const BFTextFieldId AnnlMRFPCD;
   extern const BFTextFieldId AnnlMRFPEmail;
   extern const BFTextFieldId AnnlMRFPEpost;
   extern const BFTextFieldId AnnlMRFPAuth;
   extern const BFTextFieldId TaxAuth;
   extern const BFTextFieldId LetAuth;
   extern const BFTextFieldId CertAuth;
   extern const BFTextFieldId DivConfAuth;
   extern const BFTextFieldId DivChqAuth;
   extern const BFTextFieldId ContrAuth;
   extern const BFTextFieldId RegAuth;
   extern const BFTextFieldId AnnlRptsAuth;
   extern const BFTextFieldId ProspAuth;
   extern const BFTextFieldId BenAuth;
   extern const BFTextFieldId StmtAuth;
   extern const BFTextFieldId DupStmtAuth;
   extern const BFTextFieldId NFConAuth;
   extern const BFTextFieldId TxnConfAuth;
   extern const BFTextFieldId DupConfAuth;
   extern const BFTextFieldId SmAnnlRptsAuth;
   extern const BFTextFieldId ContributionAuth;
   extern const BFTextFieldId StmtFrequency;

   //Property Externs
   extern const BFDataFieldProperties s_FldProp_SessionId;
   extern const BFDataFieldProperties s_FldProp_User_Id;
   extern const BFDataFieldProperties s_FldProp_LanguageCode;
   extern const BFDataFieldProperties s_FldProp_CompanyId;
   extern const BFDataFieldProperties s_FldProp_RunMode;
   extern const BFDataFieldProperties s_FldProp_RegAddr;
   extern const BFDataFieldProperties s_FldProp_DivConfAddr;
   extern const BFDataFieldProperties s_FldProp_DivChqAddr;
   extern const BFDataFieldProperties s_FldProp_TxnConfAddr;
   extern const BFDataFieldProperties s_FldProp_DupConfAddr;
   extern const BFDataFieldProperties s_FldProp_StmtAddr;
   extern const BFDataFieldProperties s_FldProp_DupStmtAddr;
   extern const BFDataFieldProperties s_FldProp_CertAddr;
   extern const BFDataFieldProperties s_FldProp_TaxAddr;
   extern const BFDataFieldProperties s_FldProp_LetAddr;
   extern const BFDataFieldProperties s_FldProp_BenAddr;
   extern const BFDataFieldProperties s_FldProp_DupConfCopies;
   extern const BFDataFieldProperties s_FldProp_DupStmtCopies;
   extern const BFDataFieldProperties s_FldProp_RegOnHold;
   extern const BFDataFieldProperties s_FldProp_DivConfOnHold;
   extern const BFDataFieldProperties s_FldProp_DivChqOnHold;
   extern const BFDataFieldProperties s_FldProp_TxnConfOnHold;
   extern const BFDataFieldProperties s_FldProp_DupConfOnHold;
   extern const BFDataFieldProperties s_FldProp_StmtOnHold;
   extern const BFDataFieldProperties s_FldProp_DupStmtOnHold;
   extern const BFDataFieldProperties s_FldProp_CertOnHold;
   extern const BFDataFieldProperties s_FldProp_TaxOnHold;
   extern const BFDataFieldProperties s_FldProp_LetOnHold;
   extern const BFDataFieldProperties s_FldProp_BenOnHold;
   extern const BFDataFieldProperties s_FldProp_SATxnConfCode;
   extern const BFDataFieldProperties s_FldProp_SADivConfCode;
   extern const BFDataFieldProperties s_FldProp_SALettersCode;
   extern const BFDataFieldProperties s_FldProp_AcctMstrVer;
   extern const BFDataFieldProperties s_FldProp_NFCAddr;
   extern const BFDataFieldProperties s_FldProp_NFConHold;
   extern const BFDataFieldProperties s_FldProp_AccountNum;
   extern const BFDataFieldProperties s_FldProp_AcctMstrRid;
   extern const BFDataFieldProperties s_FldProp_Track;
   extern const BFDataFieldProperties s_FldProp_Activity;
   extern const BFDataFieldProperties s_FldProp_ContrAddr;
   extern const BFDataFieldProperties s_FldProp_ContrHold;
   extern const BFDataFieldProperties s_FldProp_AnnlRptsAddr;
   extern const BFDataFieldProperties s_FldProp_AnnlRptsHold;
   extern const BFDataFieldProperties s_FldProp_ProspAddr;
   extern const BFDataFieldProperties s_FldProp_ProspHold;
   extern const BFDataFieldProperties s_FldProp_TaxSuppress;
   extern const BFDataFieldProperties s_FldProp_TaxWaive;
   extern const BFDataFieldProperties s_FldProp_TaxMail;
   extern const BFDataFieldProperties s_FldProp_TaxFax;
   extern const BFDataFieldProperties s_FldProp_TaxCD;
   extern const BFDataFieldProperties s_FldProp_TaxEmail;
   extern const BFDataFieldProperties s_FldProp_LetSuppress;
   extern const BFDataFieldProperties s_FldProp_LetWaive;
   extern const BFDataFieldProperties s_FldProp_LetMail;
   extern const BFDataFieldProperties s_FldProp_LetFax;
   extern const BFDataFieldProperties s_FldProp_LetCD;
   extern const BFDataFieldProperties s_FldProp_LetEmail;
   extern const BFDataFieldProperties s_FldProp_CertSuppress;
   extern const BFDataFieldProperties s_FldProp_CertWaive;
   extern const BFDataFieldProperties s_FldProp_CertMail;
   extern const BFDataFieldProperties s_FldProp_CertCD;
   extern const BFDataFieldProperties s_FldProp_CertEmail;
   extern const BFDataFieldProperties s_FldProp_CertFax;
   extern const BFDataFieldProperties s_FldProp_DivConfSuppress;
   extern const BFDataFieldProperties s_FldProp_DivConfWaive;
   extern const BFDataFieldProperties s_FldProp_DivConfMail;
   extern const BFDataFieldProperties s_FldProp_DivConfFax;
   extern const BFDataFieldProperties s_FldProp_DivConfCD;
   extern const BFDataFieldProperties s_FldProp_DivConfEmail;
   extern const BFDataFieldProperties s_FldProp_DivChqSuppress;
   extern const BFDataFieldProperties s_FldProp_DivChqWaive;
   extern const BFDataFieldProperties s_FldProp_DivChqMail;
   extern const BFDataFieldProperties s_FldProp_DivChqFax;
   extern const BFDataFieldProperties s_FldProp_DivChqCD;
   extern const BFDataFieldProperties s_FldProp_DivChqEmail;
   extern const BFDataFieldProperties s_FldProp_RegSuppress;
   extern const BFDataFieldProperties s_FldProp_RegWaive;
   extern const BFDataFieldProperties s_FldProp_RegMail;
   extern const BFDataFieldProperties s_FldProp_RegFax;
   extern const BFDataFieldProperties s_FldProp_RegCD;
   extern const BFDataFieldProperties s_FldProp_RegEmail;
   extern const BFDataFieldProperties s_FldProp_AnnlRptsSuppress;
   extern const BFDataFieldProperties s_FldProp_AnnlRptsWaive;
   extern const BFDataFieldProperties s_FldProp_AnnlRptsMail;
   extern const BFDataFieldProperties s_FldProp_AnnlRptsFax;
   extern const BFDataFieldProperties s_FldProp_AnnlRptsCD;
   extern const BFDataFieldProperties s_FldProp_AnnlRptsEmail;
   extern const BFDataFieldProperties s_FldProp_ProspSuppress;
   extern const BFDataFieldProperties s_FldProp_ProspWaive;
   extern const BFDataFieldProperties s_FldProp_ProspMail;
   extern const BFDataFieldProperties s_FldProp_ProspFax;
   extern const BFDataFieldProperties s_FldProp_ProspCD;
   extern const BFDataFieldProperties s_FldProp_ProspEmail;
   extern const BFDataFieldProperties s_FldProp_BenSuppress;
   extern const BFDataFieldProperties s_FldProp_BenWaive;
   extern const BFDataFieldProperties s_FldProp_BenMail;
   extern const BFDataFieldProperties s_FldProp_BenFax;
   extern const BFDataFieldProperties s_FldProp_BenCD;
   extern const BFDataFieldProperties s_FldProp_BenEmail;
   extern const BFDataFieldProperties s_FldProp_StmtSuppress;
   extern const BFDataFieldProperties s_FldProp_StmtWaive;
   extern const BFDataFieldProperties s_FldProp_StmtMail;
   extern const BFDataFieldProperties s_FldProp_StmtFax;
   extern const BFDataFieldProperties s_FldProp_StmtCD;
   extern const BFDataFieldProperties s_FldProp_StmtEmail;
   extern const BFDataFieldProperties s_FldProp_DupStmtSuppress;
   extern const BFDataFieldProperties s_FldProp_DupStmtWaive;
   extern const BFDataFieldProperties s_FldProp_DupStmtMail;
   extern const BFDataFieldProperties s_FldProp_DupStmtFax;
   extern const BFDataFieldProperties s_FldProp_DupStmtCD;
   extern const BFDataFieldProperties s_FldProp_DupStmtEmail;
   extern const BFDataFieldProperties s_FldProp_NFConfSuppress;
   extern const BFDataFieldProperties s_FldProp_NFConfWaive;
   extern const BFDataFieldProperties s_FldProp_NFConfMail;
   extern const BFDataFieldProperties s_FldProp_NFConfFax;
   extern const BFDataFieldProperties s_FldProp_NFConfCD;
   extern const BFDataFieldProperties s_FldProp_NFConfEmail;
   extern const BFDataFieldProperties s_FldProp_TxnConfSuppress;
   extern const BFDataFieldProperties s_FldProp_TxnConfWaive;
   extern const BFDataFieldProperties s_FldProp_TxnConfMail;
   extern const BFDataFieldProperties s_FldProp_TxnConfFax;
   extern const BFDataFieldProperties s_FldProp_TxnConfCD;
   extern const BFDataFieldProperties s_FldProp_TxnConfEmail;
   extern const BFDataFieldProperties s_FldProp_DupConfSuppress;
   extern const BFDataFieldProperties s_FldProp_DupConfWaive;
   extern const BFDataFieldProperties s_FldProp_DupConfMail;
   extern const BFDataFieldProperties s_FldProp_DupConfFax;
   extern const BFDataFieldProperties s_FldProp_DupConfCD;
   extern const BFDataFieldProperties s_FldProp_DupConfEmail;
   extern const BFDataFieldProperties s_FldProp_ContrSuppress;
   extern const BFDataFieldProperties s_FldProp_ContrWaive;
   extern const BFDataFieldProperties s_FldProp_ContrMail;
   extern const BFDataFieldProperties s_FldProp_ContrFax;
   extern const BFDataFieldProperties s_FldProp_ContrCD;
   extern const BFDataFieldProperties s_FldProp_ContrEmail;
   extern const BFDataFieldProperties s_FldProp_SemiAnnualSuppress;
   extern const BFDataFieldProperties s_FldProp_SemiAnnualWaive;
   extern const BFDataFieldProperties s_FldProp_SemiAnnualMail;
   extern const BFDataFieldProperties s_FldProp_SemiAnnualFax;
   extern const BFDataFieldProperties s_FldProp_SemiAnnualCD;
   extern const BFDataFieldProperties s_FldProp_SemiAnnualEmail;
   extern const BFDataFieldProperties s_FldProp_SemiAnnualAddr;
   extern const BFDataFieldProperties s_FldProp_SemiAnnualOnHold;
   extern const BFDataFieldProperties s_FldProp_TaxEpost;
   extern const BFDataFieldProperties s_FldProp_LetEpost;
   extern const BFDataFieldProperties s_FldProp_CertEpost;
   extern const BFDataFieldProperties s_FldProp_DivConfEpost;
   extern const BFDataFieldProperties s_FldProp_DivChqEpost;
   extern const BFDataFieldProperties s_FldProp_ContrEPost;
   extern const BFDataFieldProperties s_FldProp_RegEpost;
   extern const BFDataFieldProperties s_FldProp_AnnlRptsEpost;
   extern const BFDataFieldProperties s_FldProp_ProspEpost;
   extern const BFDataFieldProperties s_FldProp_BenEpost;
   extern const BFDataFieldProperties s_FldProp_StmtEpost;
   extern const BFDataFieldProperties s_FldProp_DupStmtEpost;
   extern const BFDataFieldProperties s_FldProp_NFConfEpost;
   extern const BFDataFieldProperties s_FldProp_TxnConfEpost;
   extern const BFDataFieldProperties s_FldProp_DupConfEpost;
   extern const BFDataFieldProperties s_FldProp_SemiAnnualEpost;
   extern const BFDataFieldProperties s_FldProp_ContributionSuppress;
   extern const BFDataFieldProperties s_FldProp_ContributionWaive;
   extern const BFDataFieldProperties s_FldProp_ContributionMail;
   extern const BFDataFieldProperties s_FldProp_ContributionFax;
   extern const BFDataFieldProperties s_FldProp_ContributionCD;
   extern const BFDataFieldProperties s_FldProp_ContributionEmail;
   extern const BFDataFieldProperties s_FldProp_ContributionEpost;
   extern const BFDataFieldProperties s_FldProp_ContributionAddr;
   extern const BFDataFieldProperties s_FldProp_ContributionOnHold;
   extern const BFDataFieldProperties s_FldProp_SmAnnlMRFPAddr;
   extern const BFDataFieldProperties s_FldProp_SmAnnlMRFPSuppress;
   extern const BFDataFieldProperties s_FldProp_SmAnnlMRFPWaive;
   extern const BFDataFieldProperties s_FldProp_SmAnnlMRFPHold;
   extern const BFDataFieldProperties s_FldProp_SmAnnlMRFPMail;
   extern const BFDataFieldProperties s_FldProp_SmAnnlMRFPFax;
   extern const BFDataFieldProperties s_FldProp_SmAnnlMRFPCD;
   extern const BFDataFieldProperties s_FldProp_SmAnnlMRFPEmail;
   extern const BFDataFieldProperties s_FldProp_SmAnnlMRFPEpost;
   extern const BFDataFieldProperties s_FldProp_SmAnnlMRFPAuth;
   extern const BFDataFieldProperties s_FldProp_AnnlMRFPAddr;
   extern const BFDataFieldProperties s_FldProp_AnnlMRFPSuppress;
   extern const BFDataFieldProperties s_FldProp_AnnlMRFPWaive;
   extern const BFDataFieldProperties s_FldProp_AnnlMRFPHold;
   extern const BFDataFieldProperties s_FldProp_AnnlMRFPMail;
   extern const BFDataFieldProperties s_FldProp_AnnlMRFPFax;
   extern const BFDataFieldProperties s_FldProp_AnnlMRFPCD;
   extern const BFDataFieldProperties s_FldProp_AnnlMRFPEmail;
   extern const BFDataFieldProperties s_FldProp_AnnlMRFPEpost;
   extern const BFDataFieldProperties s_FldProp_AnnlMRFPAuth;
   extern const BFDataFieldProperties s_FldProp_TaxAuth;
   extern const BFDataFieldProperties s_FldProp_LetAuth;
   extern const BFDataFieldProperties s_FldProp_CertAuth;
   extern const BFDataFieldProperties s_FldProp_DivConfAuth;
   extern const BFDataFieldProperties s_FldProp_DivChqAuth;
   extern const BFDataFieldProperties s_FldProp_ContrAuth;
   extern const BFDataFieldProperties s_FldProp_RegAuth;
   extern const BFDataFieldProperties s_FldProp_AnnlRptsAuth;
   extern const BFDataFieldProperties s_FldProp_ProspAuth;
   extern const BFDataFieldProperties s_FldProp_BenAuth;
   extern const BFDataFieldProperties s_FldProp_StmtAuth;
   extern const BFDataFieldProperties s_FldProp_DupStmtAuth;
   extern const BFDataFieldProperties s_FldProp_NFConAuth;
   extern const BFDataFieldProperties s_FldProp_TxnConfAuth;
   extern const BFDataFieldProperties s_FldProp_DupConfAuth;
   extern const BFDataFieldProperties s_FldProp_SmAnnlRptsAuth;
   extern const BFDataFieldProperties s_FldProp_ContributionAuth;
   extern const BFDataFieldProperties s_FldProp_StmtFrequency;
}


class dsi_DSTC0114_REQ : public BFDataImpl 
{
public:
   // Constructors
   dsi_DSTC0114_REQ();
   virtual ~dsi_DSTC0114_REQ();

   virtual BFDataImpl* clone();

   virtual BFDataField* getElement( const BFFieldId& id );
   virtual const BFDataField* getElement( const BFFieldId& id ) const;
   virtual BFDataField* getElementByIndex( unsigned int iField );
   virtual const BFDataField* getElementByIndex( unsigned int iField ) const;


   virtual unsigned long getLargestDefinedField( void ) const;
   virtual unsigned long getDefinedByteLength( void ) const;
   virtual bool exists( const BFFieldId& id ) const;
   static bool fieldExists( const BFFieldId& id );

private:
   BFDataField* aFlds_[206];
   // Field Declarations
   BFTextField_60 SessionId_;
   BFTextField_60 User_Id_;
   BFTextField_60 LanguageCode_;
   BFTextField_60 CompanyId_;
   BFTextField_60 RunMode_;
   BFTextField_60 RegAddr_;
   BFTextField_60 DivConfAddr_;
   BFTextField_60 DivChqAddr_;
   BFTextField_60 TxnConfAddr_;
   BFTextField_60 DupConfAddr_;
   BFTextField_60 StmtAddr_;
   BFTextField_60 DupStmtAddr_;
   BFTextField_60 CertAddr_;
   BFTextField_60 TaxAddr_;
   BFTextField_60 LetAddr_;
   BFTextField_60 BenAddr_;
   BFNumericField DupConfCopies_;
   BFNumericField DupStmtCopies_;
   BFTextField_1 RegOnHold_;
   BFTextField_1 DivConfOnHold_;
   BFTextField_1 DivChqOnHold_;
   BFTextField_1 TxnConfOnHold_;
   BFTextField_1 DupConfOnHold_;
   BFTextField_1 StmtOnHold_;
   BFTextField_1 DupStmtOnHold_;
   BFTextField_1 CertOnHold_;
   BFTextField_1 TaxOnHold_;
   BFTextField_1 LetOnHold_;
   BFTextField_1 BenOnHold_;
   BFTextField_60 SATxnConfCode_;
   BFTextField_60 SADivConfCode_;
   BFTextField_60 SALettersCode_;
   BFNumericField AcctMstrVer_;
   BFTextField_60 NFCAddr_;
   BFTextField_1 NFConHold_;
   BFNumericField AccountNum_;
   BFDecimalField AcctMstrRid_;
   BFTextField_1 Track_;
   BFTextField_60 Activity_;
   BFTextField_10 ContrAddr_;
   BFTextField_10 ContrHold_;
   BFTextField_10 AnnlRptsAddr_;
   BFTextField_1 AnnlRptsHold_;
   BFTextField_10 ProspAddr_;
   BFTextField_10 ProspHold_;
   BFTextField_2 TaxSuppress_;
   BFTextField_2 TaxWaive_;
   BFTextField_10 TaxMail_;
   BFTextField_2 TaxFax_;
   BFTextField_2 TaxCD_;
   BFTextField_2 TaxEmail_;
   BFTextField_2 LetSuppress_;
   BFTextField_2 LetWaive_;
   BFTextField_10 LetMail_;
   BFTextField_2 LetFax_;
   BFTextField_2 LetCD_;
   BFTextField_2 LetEmail_;
   BFTextField_2 CertSuppress_;
   BFTextField_2 CertWaive_;
   BFTextField_10 CertMail_;
   BFTextField_2 CertCD_;
   BFTextField_2 CertEmail_;
   BFTextField_2 CertFax_;
   BFTextField_2 DivConfSuppress_;
   BFTextField_2 DivConfWaive_;
   BFTextField_10 DivConfMail_;
   BFTextField_2 DivConfFax_;
   BFTextField_2 DivConfCD_;
   BFTextField_2 DivConfEmail_;
   BFTextField_2 DivChqSuppress_;
   BFTextField_2 DivChqWaive_;
   BFTextField_10 DivChqMail_;
   BFTextField_2 DivChqFax_;
   BFTextField_2 DivChqCD_;
   BFTextField_2 DivChqEmail_;
   BFTextField_2 RegSuppress_;
   BFTextField_2 RegWaive_;
   BFTextField_10 RegMail_;
   BFTextField_2 RegFax_;
   BFTextField_2 RegCD_;
   BFTextField_2 RegEmail_;
   BFTextField_2 AnnlRptsSuppress_;
   BFTextField_2 AnnlRptsWaive_;
   BFTextField_10 AnnlRptsMail_;
   BFTextField_2 AnnlRptsFax_;
   BFTextField_2 AnnlRptsCD_;
   BFTextField_2 AnnlRptsEmail_;
   BFTextField_2 ProspSuppress_;
   BFTextField_2 ProspWaive_;
   BFTextField_10 ProspMail_;
   BFTextField_2 ProspFax_;
   BFTextField_2 ProspCD_;
   BFTextField_2 ProspEmail_;
   BFTextField_2 BenSuppress_;
   BFTextField_2 BenWaive_;
   BFTextField_10 BenMail_;
   BFTextField_2 BenFax_;
   BFTextField_2 BenCD_;
   BFTextField_2 BenEmail_;
   BFTextField_2 StmtSuppress_;
   BFTextField_2 StmtWaive_;
   BFTextField_10 StmtMail_;
   BFTextField_2 StmtFax_;
   BFTextField_2 StmtCD_;
   BFTextField_2 StmtEmail_;
   BFTextField_2 DupStmtSuppress_;
   BFTextField_2 DupStmtWaive_;
   BFTextField_10 DupStmtMail_;
   BFTextField_2 DupStmtFax_;
   BFTextField_2 DupStmtCD_;
   BFTextField_2 DupStmtEmail_;
   BFTextField_2 NFConfSuppress_;
   BFTextField_2 NFConfWaive_;
   BFTextField_10 NFConfMail_;
   BFTextField_2 NFConfFax_;
   BFTextField_2 NFConfCD_;
   BFTextField_2 NFConfEmail_;
   BFTextField_2 TxnConfSuppress_;
   BFTextField_2 TxnConfWaive_;
   BFTextField_10 TxnConfMail_;
   BFTextField_2 TxnConfFax_;
   BFTextField_2 TxnConfCD_;
   BFTextField_2 TxnConfEmail_;
   BFTextField_2 DupConfSuppress_;
   BFTextField_2 DupConfWaive_;
   BFTextField_10 DupConfMail_;
   BFTextField_2 DupConfFax_;
   BFTextField_2 DupConfCD_;
   BFTextField_2 DupConfEmail_;
   BFTextField_2 ContrSuppress_;
   BFTextField_2 ContrWaive_;
   BFTextField_10 ContrMail_;
   BFTextField_2 ContrFax_;
   BFTextField_2 ContrCD_;
   BFTextField_2 ContrEmail_;
   BFTextField_2 SemiAnnualSuppress_;
   BFTextField_2 SemiAnnualWaive_;
   BFTextField_10 SemiAnnualMail_;
   BFTextField_2 SemiAnnualFax_;
   BFTextField_2 SemiAnnualCD_;
   BFTextField_2 SemiAnnualEmail_;
   BFTextField<20> SemiAnnualAddr_;
   BFTextField_2 SemiAnnualOnHold_;
   BFTextField_2 TaxEpost_;
   BFTextField_2 LetEpost_;
   BFTextField_2 CertEpost_;
   BFTextField_2 DivConfEpost_;
   BFTextField_2 DivChqEpost_;
   BFTextField_2 ContrEPost_;
   BFTextField_2 RegEpost_;
   BFTextField_2 AnnlRptsEpost_;
   BFTextField_2 ProspEpost_;
   BFTextField_2 BenEpost_;
   BFTextField_2 StmtEpost_;
   BFTextField_2 DupStmtEpost_;
   BFTextField_2 NFConfEpost_;
   BFTextField_2 TxnConfEpost_;
   BFTextField_2 DupConfEpost_;
   BFTextField_2 SemiAnnualEpost_;
   BFTextField_2 ContributionSuppress_;
   BFTextField_2 ContributionWaive_;
   BFTextField_10 ContributionMail_;
   BFTextField_2 ContributionFax_;
   BFTextField_2 ContributionCD_;
   BFTextField_2 ContributionEmail_;
   BFTextField_2 ContributionEpost_;
   BFTextField<20> ContributionAddr_;
   BFTextField_2 ContributionOnHold_;
   BFTextField<4> SmAnnlMRFPAddr_;
   BFTextField_2 SmAnnlMRFPSuppress_;
   BFTextField_2 SmAnnlMRFPWaive_;
   BFTextField<4> SmAnnlMRFPHold_;
   BFTextField_10 SmAnnlMRFPMail_;
   BFTextField_2 SmAnnlMRFPFax_;
   BFTextField_2 SmAnnlMRFPCD_;
   BFTextField_2 SmAnnlMRFPEmail_;
   BFTextField_2 SmAnnlMRFPEpost_;
   BFTextField<4> SmAnnlMRFPAuth_;
   BFTextField<4> AnnlMRFPAddr_;
   BFTextField_2 AnnlMRFPSuppress_;
   BFTextField_2 AnnlMRFPWaive_;
   BFTextField_2 AnnlMRFPHold_;
   BFTextField_10 AnnlMRFPMail_;
   BFTextField_2 AnnlMRFPFax_;
   BFTextField_2 AnnlMRFPCD_;
   BFTextField_2 AnnlMRFPEmail_;
   BFTextField_2 AnnlMRFPEpost_;
   BFTextField<4> AnnlMRFPAuth_;
   BFTextField<4> TaxAuth_;
   BFTextField<4> LetAuth_;
   BFTextField<4> CertAuth_;
   BFTextField<4> DivConfAuth_;
   BFTextField<4> DivChqAuth_;
   BFTextField<4> ContrAuth_;
   BFTextField<4> RegAuth_;
   BFTextField<4> AnnlRptsAuth_;
   BFTextField<4> ProspAuth_;
   BFTextField<4> BenAuth_;
   BFTextField<4> StmtAuth_;
   BFTextField<4> DupStmtAuth_;
   BFTextField<4> NFConAuth_;
   BFTextField<4> TxnConfAuth_;
   BFTextField<4> DupConfAuth_;
   BFTextField<4> SmAnnlRptsAuth_;
   BFTextField_2 ContributionAuth_;
   BFTextField_60 StmtFrequency_;

};
