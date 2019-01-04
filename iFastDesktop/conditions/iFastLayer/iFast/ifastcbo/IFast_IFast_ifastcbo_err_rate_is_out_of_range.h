#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rate_is_out_of_range : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rate_is_out_of_range() { }
		~CIFast_IFast_ifastcbo_err_rate_is_out_of_range() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RATE_IS_OUT_OF_RANGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Rate has to be between %MINRATE% and %MAXRATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Satz muss zwischen %MINRATE% und %MAXRATE% liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tasa debe ser entre %MINRATE% y %MAXRATE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux doit être situé entre %MINRATE% et %MAXRATE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Tarief moet tussen %MINRATE% en %MAXRATE% liggen")); }

        // Actions
	};
}



