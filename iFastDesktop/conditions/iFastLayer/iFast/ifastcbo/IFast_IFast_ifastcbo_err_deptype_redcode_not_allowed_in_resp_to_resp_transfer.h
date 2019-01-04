#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deptype_redcode_not_allowed_in_resp_to_resp_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deptype_redcode_not_allowed_in_resp_to_resp_transfer() { }
		~CIFast_IFast_ifastcbo_err_deptype_redcode_not_allowed_in_resp_to_resp_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPTYPE_REDCODE_NOT_ALLOWED_IN_RESP_TO_RESP_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("For RESP to RESP transfer only RD 64 and DP 17 are allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seuls RD 64 et DP 17 sont autorisés pour les transferts de REEE à REEE.")); }

        // Actions
	};
}



