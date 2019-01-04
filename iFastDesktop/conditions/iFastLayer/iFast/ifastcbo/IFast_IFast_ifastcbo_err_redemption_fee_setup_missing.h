#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redemption_fee_setup_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redemption_fee_setup_missing() { }
		~CIFast_IFast_ifastcbo_err_redemption_fee_setup_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDEMPTION_FEE_SETUP_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee applicable to this Redemption Code has not been setup.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fee applicable to this Redemption Code has not been setup.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("System Error, Fee applicable to this Redemption Code has not been setup.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais applicables à ce code de rachat n'ont pas été réglés.")); }

        // Actions
	};
}



