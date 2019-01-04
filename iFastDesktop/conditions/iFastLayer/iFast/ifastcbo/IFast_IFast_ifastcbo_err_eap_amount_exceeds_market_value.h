#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_eap_amount_exceeds_market_value : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_eap_amount_exceeds_market_value() { }
		~CIFast_IFast_ifastcbo_err_eap_amount_exceeds_market_value() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EAP_AMOUNT_EXCEEDS_MARKET_VALUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("EAP Amount exceeds Market Value.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant PAE excède la valeur de marché.")); }

        // Actions
	};
}



