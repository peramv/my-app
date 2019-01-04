#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_percent_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_percent_invalid() { }
		~CIFast_IFast_ifastcbo_err_fee_percent_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_PERCENT_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee percentage must be between 0 and 100 inclusively.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Prozentsatz muss zwischen 0 und 100 (inklusive) liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El porcentaje de comisión debe ser entre 0 y 100, inclusive.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage de frais doit être situé entre 0 et 100 inclusivement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kostenpercentage moet tussen 0 tot en met 100 liggen")); }

        // Actions
	};
}



