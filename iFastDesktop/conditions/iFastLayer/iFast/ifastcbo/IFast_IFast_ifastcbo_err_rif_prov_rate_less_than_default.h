#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_prov_rate_less_than_default : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_prov_rate_less_than_default() { }
		~CIFast_IFast_ifastcbo_err_rif_prov_rate_less_than_default() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_PROV_RATE_LESS_THAN_DEFAULT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Prov tax rate is less than default value.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux d'imposition provincial est inférieur à la valeur par défaut.")); }

        // Actions
	};
}



