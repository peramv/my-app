#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_inelig_resp_transfer_trigger_grant_repayment : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_inelig_resp_transfer_trigger_grant_repayment() { }
		~CIFast_IFast_ifastcbo_warn_inelig_resp_transfer_trigger_grant_repayment() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INELIG_RESP_TRANSFER_TRIGGER_GRANT_REPAYMENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Ineligible RESP Transfer may trigger grant repayment which should be done before the transfer.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un transfert REEE non admissible pourrait déclencher un remboursement de subvention qui devrait être fait avant le transfert.")); }

        // Actions
	};
}



