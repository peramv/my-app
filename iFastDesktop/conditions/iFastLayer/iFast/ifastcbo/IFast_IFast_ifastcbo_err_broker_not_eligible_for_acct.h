#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_broker_not_eligible_for_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_broker_not_eligible_for_acct() { }
		~CIFast_IFast_ifastcbo_err_broker_not_eligible_for_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_NOT_ELIGIBLE_FOR_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker not eligible for this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Broker not eligible for this account.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Broker not eligible for this account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Courtier non admissible à ce compte")); }

        // Actions
	};
}



