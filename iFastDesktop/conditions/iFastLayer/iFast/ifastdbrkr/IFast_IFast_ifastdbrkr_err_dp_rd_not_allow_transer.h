#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_dp_rd_not_allow_transer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_dp_rd_not_allow_transer() { }
		~CIFast_IFast_ifastdbrkr_err_dp_rd_not_allow_transer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DP_RD_NOT_ALLOW_TRANSER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("DP 20 or RD 61, 83, 84 not allowed in Transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("DP 20 oder RD 61, 83, 84 nicht in Transfer erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten DP 20 ni RD 61, 83, 84 para transferencias")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("DP 20 ou RD 61, 83 et 84 ne sont pas autorisés pour les transferts.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("DP 20 of RD 61, 83, 84 zijn niet toegestaan voor overdracht")); }

        // Actions
	};
}



