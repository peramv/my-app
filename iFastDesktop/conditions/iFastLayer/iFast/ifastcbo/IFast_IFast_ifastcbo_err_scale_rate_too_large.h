#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_scale_rate_too_large : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_scale_rate_too_large() { }
		~CIFast_IFast_ifastcbo_err_scale_rate_too_large() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SCALE_RATE_TOO_LARGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Rate for scale %GRADE% can not be larger than %RATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Satz für Gebühren %GRADE% darf nicht größer als %RATE% sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo para la escala %GRADE% no puede ser mayor que %RATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux pour l'échelle %GRADE% ne peut être supérieur à %RATE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Tarief voor schaal %GRADE% kan niet groter zijn dan %RATE%")); }

        // Actions
	};
}



