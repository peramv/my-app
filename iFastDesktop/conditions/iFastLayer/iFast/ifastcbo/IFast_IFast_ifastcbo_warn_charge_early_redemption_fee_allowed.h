#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_charge_early_redemption_fee_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_charge_early_redemption_fee_allowed() { }
		~CIFast_IFast_ifastcbo_warn_charge_early_redemption_fee_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CHARGE_EARLY_REDEMPTION_FEE_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("It is allowed to charge early redemption fee on the transaction.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("It is allowed to charge early redemption fee on the transaction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il est autorisé de facturer des frais de rachat anticipé sur la transaction.")); }

        // Actions
	};
}



