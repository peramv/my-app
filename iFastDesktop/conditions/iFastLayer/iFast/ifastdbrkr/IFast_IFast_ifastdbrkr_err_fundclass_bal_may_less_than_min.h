#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fundclass_bal_may_less_than_min : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fundclass_bal_may_less_than_min() { }
		~CIFast_IFast_ifastdbrkr_err_fundclass_bal_may_less_than_min() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUNDCLASS_BAL_MAY_LESS_THAN_MIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund/Class balance may be less than minimum.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds / Klasse -Saldo kann unter dem Minimum liegen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El saldo del fondo/clase puede ser inferior al mínimo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le solde du fonds/de la classe peut être inférieur au minimum.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Saldo fonds/categorie kan lager zijn dan minimum")); }

        // Actions
	};
}



