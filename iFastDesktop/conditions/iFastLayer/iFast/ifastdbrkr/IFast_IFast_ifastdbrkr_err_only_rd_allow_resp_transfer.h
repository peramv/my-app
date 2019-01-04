#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_only_rd_allow_resp_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_only_rd_allow_resp_transfer() { }
		~CIFast_IFast_ifastdbrkr_err_only_rd_allow_resp_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONLY_RD_ALLOW_RESP_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only RD 64 and DP 17 are allowed for RESP - RESP transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur RD 64 und DP 17 sind für RESP-RESP-Transfer erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo se permiten RD 64 y DP 17 para transferencias RESP - RESP")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seuls RD 64 et DP 17 sont autorisés pour les transferts REEE - REEE.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Alleen RD 64 en DP 17 zijn toegestaan voor overdracht van RESP naar RESP")); }

        // Actions
	};
}



