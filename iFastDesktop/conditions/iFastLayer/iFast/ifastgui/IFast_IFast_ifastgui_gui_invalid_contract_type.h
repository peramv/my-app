#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_invalid_contract_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_invalid_contract_type() { }
		~CIFast_IFast_ifastgui_gui_invalid_contract_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_INVALID_CONTRACT_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A valid contract type is needed to access the contract maturity instruction screen.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un type de contrat valide est requis pour accéder à l'écran des instructions à l'échéance du contrat.")); }

        // Actions
	};
}



