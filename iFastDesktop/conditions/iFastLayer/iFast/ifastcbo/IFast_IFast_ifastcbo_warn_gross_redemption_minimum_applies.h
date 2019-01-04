#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_gross_redemption_minimum_applies : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_gross_redemption_minimum_applies() { }
		~CIFast_IFast_ifastcbo_warn_gross_redemption_minimum_applies() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_GROSS_REDEMPTION_MINIMUM_APPLIES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This transaction may exceed the remaining minimum amount and may be rejected in the cycle.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cette transaction pourrait  excéder les montant minimal restant et pourrait être rejetée par le cycle.")); }

        // Actions
	};
}



