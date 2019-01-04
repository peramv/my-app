#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ro_eff_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ro_eff_date() { }
		~CIFast_IFast_ifastcbo_err_ro_eff_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RO_EFF_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot modify effective date on RO allocation")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de modifier la date d'entrée en vigueur de la répartition de l'actif du compte.")); }

        // Actions
	};
}



