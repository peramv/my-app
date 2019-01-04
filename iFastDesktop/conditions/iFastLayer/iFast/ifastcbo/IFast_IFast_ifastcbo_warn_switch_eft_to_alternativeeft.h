#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_switch_eft_to_alternativeeft : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_switch_eft_to_alternativeeft() { }
		~CIFast_IFast_ifastcbo_warn_switch_eft_to_alternativeeft() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SWITCH_EFT_TO_ALTERNATIVEEFT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Existing EFT Redemption has been changed to Alternative EFT Redemption.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le rachat TEF existant a été changé pour l'autre rachat TEF.")); }

        // Actions
	};
}



