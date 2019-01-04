#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_eap_redempt_exceeded_earning : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_eap_redempt_exceeded_earning() { }
		~CIFast_IFast_ifastcbo_err_eap_redempt_exceeded_earning() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EAP_REDEMPT_EXCEEDED_EARNING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption Charges %PARAM_1% exceed Earnings %PARAM_2%. Waive the charges or system will deduct them  from the account holdings/contribution.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais de rachat %PARAM_1% excèdent les bénéfices %PARAM_2%. Il faut supprimer ces frais ou le système les déduira des avoirs ou des cotisations du compte.")); }

        // Actions
	};
}



