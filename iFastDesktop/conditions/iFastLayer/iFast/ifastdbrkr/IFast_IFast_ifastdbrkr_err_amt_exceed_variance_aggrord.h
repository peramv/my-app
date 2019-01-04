#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_amt_exceed_variance_aggrord : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_amt_exceed_variance_aggrord() { }
		~CIFast_IFast_ifastdbrkr_err_amt_exceed_variance_aggrord() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMT_EXCEED_VARIANCE_AGGRORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount exceeded variance limit and Aggregate Order in loss situation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Amount exceeded variance limit and Aggregate Order in loss situation.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant a excédé la limite d'écart et l'ordre global est en situation de perte.")); }

        // Actions
	};
}



