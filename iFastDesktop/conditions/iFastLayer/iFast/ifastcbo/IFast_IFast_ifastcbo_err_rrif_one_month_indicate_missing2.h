#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rrif_one_month_indicate_missing2 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rrif_one_month_indicate_missing2() { }
		~CIFast_IFast_ifastcbo_err_rrif_one_month_indicate_missing2() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RRIF_ONE_MONTH_INDICATE_MISSING2")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one month between %MONTH1% and  %MONTH2% in \"Monthly Indicator\" has to be set to \"Y\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("At least one month between %MONTH1% and  %MONTH2% in \"Monthly Indicator\" has to be set to \"Y\".")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("At least one month between %MONTH1% and  %MONTH2% in \"Monthly Indicator\" has to be set to \"Y\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins l'un des mois entre %MONTH1% et  %MONTH2% dans l'indicateur mensuel doit être réglé à Y.")); }

        // Actions
	};
}



