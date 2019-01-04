#pragma once
#include <ifastgui\BaseMainDlg.h>
#include <resource.h>

class ValueVariationDlg
   : public BaseMainDlg
{
public:
   ValueVariationDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual ~ValueVariationDlg(void);

   enum
   {
      IDD = IDD_VALUE_VARIATION
   };

   DECLARE_MESSAGE_MAP();
protected:
   SEVERITY doInit();
   virtual void OnPostInitDialog();  
   void OnBtnReset();
   virtual bool doRefresh( GenericInterface * rpGICaller,  const I_CHAR * szOriginalCommand);

private:
   DString dstrCaption;
};
