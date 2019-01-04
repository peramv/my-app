#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tup_estimated_units : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tup_estimated_units() { }
		~CIFast_IFast_ifastcbo_err_tup_estimated_units() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TUP_ESTIMATED_UNITS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The estimated unit amount of the inputted trade is %ESTUNITS% units.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant d'unité estimé de la transaction saisie est de %ESTUNITS% unités.")); }

        // Actions
	};
}



