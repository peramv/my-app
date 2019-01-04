#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_cannot_setup_for_account_holding_multicurrency_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_cannot_setup_for_account_holding_multicurrency_fund() { }
		~CIFast_IFast_ifastcbo_err_ams_cannot_setup_for_account_holding_multicurrency_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_CANNOT_SETUP_FOR_ACCOUNT_HOLDING_MULTICURRENCY_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS portfolio can not be set up for account currently holding multicurrency fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS portfolio can not be set up for account currently holding multicurrency fund.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AMS portfolio can not be set up for account currently holding multicurrency fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le portefeuille de service de gestion de portefeuille ne peut être réglé pour tout compte qui comporte actuellement un fonds multidevise.")); }

        // Actions
	};
}



