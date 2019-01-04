#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deptype_redcode_can_only_be_used_for_resp_to_resp_tx : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deptype_redcode_can_only_be_used_for_resp_to_resp_tx() { }
		~CIFast_IFast_ifastcbo_err_deptype_redcode_can_only_be_used_for_resp_to_resp_tx() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPTYPE_REDCODE_CAN_ONLY_BE_USED_FOR_RESP_TO_RESP_TX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("DP17, RD 64/65 can only be used for RESP to RESP transfer.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("DP 17, RD 64/65 ne peuvent être utilisés que pour les transferts de REEE à REEE.")); }

        // Actions
	};
}



