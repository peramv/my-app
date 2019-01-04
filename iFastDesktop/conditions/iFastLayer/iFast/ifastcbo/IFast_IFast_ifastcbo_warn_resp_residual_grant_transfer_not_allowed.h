#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_resp_residual_grant_transfer_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_resp_residual_grant_transfer_not_allowed() { }
		~CIFast_IFast_ifastcbo_warn_resp_residual_grant_transfer_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESP_RESIDUAL_GRANT_TRANSFER_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Allocation RESP fund transfer is not allowed to transfer the Residual Grant.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'affectation du transfert des fonds du REEE n'autorise pas le transfert du solde de subvention.")); }

        // Actions
	};
}



