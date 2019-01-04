#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_broker_different_than_account_broker : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_broker_different_than_account_broker() { }
		~CIFast_IFast_ifastcbo_err_broker_different_than_account_broker() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_DIFFERENT_THAN_ACCOUNT_BROKER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Dealer of account and transaction are different.")); }
        virtual DString GetMessage_FR_CA() const { return DString(I_("The Dealer of account and transaction are different.")); }

        // Actions
	};
}



