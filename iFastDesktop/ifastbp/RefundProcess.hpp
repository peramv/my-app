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
//
//
//    Copyright 2005 by IFDS.
//
//******************************************************************************


#include <bfproc\abstractprocess.hpp>
#include <map>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE RefundProcess : public AbstractProcess
{
// Construction
public:

   RefundProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~RefundProcess();

protected:

   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doRefresh( GenericInterface *rpGICaller, 
                           const I_CHAR *szOriginalCommand )
   {
      return(false);
   };
   virtual bool setCommitDataGroupAsHost()
   {
      return(true);
   };

private:
   bool isflowEnd ( int index);
   void setParamsForChild (const I_CHAR* params[]);
   void getParamFromParent (const I_CHAR* params[]);

private:
   class RefundParam
   {
   public:
      RefundParam();
      ~RefundParam();
      void AddParam( const DString &name, const DString &value);
      DString getParam (const DString &name);
      void removeParam (const DString &name);
   private:
        typedef std::map< DString, DString > REFUND_PARAM;
        REFUND_PARAM refund_param_;   
   };
   RefundParam  refundParam_;
};

