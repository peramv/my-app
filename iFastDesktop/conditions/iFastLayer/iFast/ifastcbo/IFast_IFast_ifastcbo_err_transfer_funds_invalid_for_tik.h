#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transfer_funds_invalid_for_tik : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transfer_funds_invalid_for_tik() { }
		~CIFast_IFast_ifastcbo_err_transfer_funds_invalid_for_tik() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_FUNDS_INVALID_FOR_TIK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Funds invalid for Transfer In Kind.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Funds invalid for Transfer In Kind.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Funds invalid for Transfer In Kind.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fonds invalides pour un transfert en biens")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please change Redemption Code.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please change Redemption Code.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please change Redemption Code.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez changer le code de rachat.")); }
	};
}



