#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_switch_eft_pur_to_alternative_eft_pur : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_switch_eft_pur_to_alternative_eft_pur() { }
		~CIFast_IFast_ifastcbo_warn_switch_eft_pur_to_alternative_eft_pur() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SWITCH_EFT_PUR_TO_ALTERNATIVE_EFT_PUR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Existing EFT Purchase has been changed to Alternative EFT Purchase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'achat TEF existant a été changé pour l'autre achat TEF.")); }

        // Actions
	};
}



