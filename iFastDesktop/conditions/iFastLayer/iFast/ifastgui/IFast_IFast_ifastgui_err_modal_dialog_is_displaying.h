#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_err_modal_dialog_is_displaying : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_err_modal_dialog_is_displaying() { }
		~CIFast_IFast_ifastgui_err_modal_dialog_is_displaying() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ERR_MODAL_DIALOG_IS_DISPLAYING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Could not proceed with the command. Please close the current dialog and try again.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ne pouvait pas procéder à la commande. Fermez la boîte de dialogue en cours et réessayez")); }

        // Actions
	};
}



