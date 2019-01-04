#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_full_redemption_percentage_must_be_zero_for_each_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_full_redemption_percentage_must_be_zero_for_each_fund() { }
		~CIFast_IFast_ifastcbo_err_full_redemption_percentage_must_be_zero_for_each_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FULL_REDEMPTION_PERCENTAGE_MUST_BE_ZERO_FOR_EACH_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Full Redemption is indicated. Please modify Percentage to 0.00 for each fund you wish to redeem.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Full Redemption is indicated. Please modify Percentage to 0.00 for each fund you wish to redeem.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Full Redemption is indicated. Please modify Percentage to 0.00 for each fund you wish to redeem.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le rachat total est indiqué. Veuillez modifier le pourcentage pour 0,00 pour chaque fonds que vous voulez rachater.")); }

        // Actions
	};
}



