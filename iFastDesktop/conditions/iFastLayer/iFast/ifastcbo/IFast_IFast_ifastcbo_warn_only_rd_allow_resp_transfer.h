#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_only_rd_allow_resp_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_only_rd_allow_resp_transfer() { }
		~CIFast_IFast_ifastcbo_warn_only_rd_allow_resp_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ONLY_RD_ALLOW_RESP_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only RD 64 and DP 17 are allowed for RESP - RESP transfer.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seuls RD 64 et DP 17 sont autorisés pour les transferts de REEE à REEE.")); }

        // Actions
	};
}



