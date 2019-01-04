#pragma once
#include <ifastgui\BaseMainDlg.h>
#include <resource.h>

class FeeModelCopyToGroupDlg
   : public BaseMainDlg
{
public:
   FeeModelCopyToGroupDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual ~FeeModelCopyToGroupDlg(void);

   enum
   {
      IDD = IDD_FEE_MODEL_COPY_TO
   };

protected:

protected:
   virtual BOOL OnInitDialog();
   virtual void OnPostInitDialog();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAddFeeModelCopiedRecord();
   afx_msg void OnBtnDelFeeModelCopiedRecord();

   DECLARE_MESSAGE_MAP();
   
protected:
   virtual bool doRefresh( GenericInterface * rpGICaller,  const I_CHAR * szOriginalCommand);

private:
   DString dstrCaption;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/FeeModelCopyToGroupDlg.h-arc  $
// 
