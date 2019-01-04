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
//    AUTHOR : 
//    DATE   : 03 Feb 2000
//
//
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class WorksessionTradesList;

class IFASTBP_LINKAGE TradesTaxRateProcess : public AbstractProcess
{
// Construction
public:
//CP20030319   TradesTaxRateProcess();
   TradesTaxRateProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~TradesTaxRateProcess();

protected:
   bool doSend( GenericInterface *rpGICaller, const I_CHAR * szMessage );
   SEVERITY doInit();
   E_COMMANDRETURN doProcess();
   void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   bool doOk( GenericInterface *rpGICaller );
   bool doCancel( GenericInterface * rpGICaller );
   virtual SEVERITY ok2( GenericInterface *rpGICaller );

private:

   GenericInterface *_rpChildGI;   
   WorksessionTradesList    * _pTradesList;
   DString          _dstrTransactionType;
   DString			_dstrAccontNum;
   DString			_dstrCurrentKey;
   DString _oldFedRate,_oldProvRate,_oldTransRatePUDFed,_oldTransRatePUDProv, _oldOverrideTax;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradesTaxRateProcess.hpp-arc  $
//
//   Rev 1.0   Aug 15 2003 10:27:24   FENGYONG
//Initial Revision
 * 
*/
