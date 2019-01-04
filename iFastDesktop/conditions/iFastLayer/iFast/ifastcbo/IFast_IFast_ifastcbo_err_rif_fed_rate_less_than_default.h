#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_fed_rate_less_than_default : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_fed_rate_less_than_default() { }
		~CIFast_IFast_ifastcbo_err_rif_fed_rate_less_than_default() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_FED_RATE_LESS_THAN_DEFAULT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fed tax rate is less than the default value.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux d'imposition fédéral est inférieur à la valeur par défaut.")); }

        // Actions
	};
}



