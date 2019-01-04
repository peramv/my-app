#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_escrow_amt_equals_holding : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_escrow_amt_equals_holding() { }
		~CIFast_IFast_ifastcbo_err_warn_escrow_amt_equals_holding() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_ESCROW_AMT_EQUALS_HOLDING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There are only %SETTLEUNIT% units available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur %SETTLEUNIT%–Anteile sind verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo hay %SETTLEUNIT% unidades disponibles.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il n'y a que %SETTLEUNIT% unités disponibles.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn alleen %SETTLEUNIT% eenheden beschikbaar")); }

        // Actions
	};
}



