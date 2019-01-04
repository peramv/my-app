#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_exch_in_fee_over_maximum : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_exch_in_fee_over_maximum() { }
		~CIFast_IFast_ifastcbo_err_exch_in_fee_over_maximum() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXCH_IN_FEE_OVER_MAXIMUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exchange In fee over maximum allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Devisen-Kauf-Provision über Maximum erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El cargo por traspaso de entrada se encuentra por encima del máximo permitido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le frais d'échange entrant sont supérieurs au maximum autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kosten ruil-in boven toegestane maximum")); }

        // Actions
	};
}



