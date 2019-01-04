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
//    AUTHOR : Yingbao Li
//    DATE   : June 23, 2005
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


class IFASTBP_LINKAGE RebookProcess : public AbstractProcess
{
// Construction
public:

   RebookProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~RebookProcess();

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
   class RebookParam
   {
   public:
      RebookParam();
      ~RebookParam();
      void AddParam( const DString &name, const DString &value);
      DString getParam (const DString &name);
      void removeParam (const DString &name);
   private:
        typedef std::map< DString, DString > REBOOK_PARAM;
        REBOOK_PARAM rebook_param_;   
   };
   RebookParam  reboolParam_;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RebookProcess.hpp-arc  $
//
//   Rev 1.0   Jul 06 2005 16:35:56   Yingbaol
//Initial revision.
 * 
 *
 */

