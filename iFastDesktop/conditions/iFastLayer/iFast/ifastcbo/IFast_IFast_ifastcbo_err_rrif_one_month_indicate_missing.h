#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rrif_one_month_indicate_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rrif_one_month_indicate_missing() { }
		~CIFast_IFast_ifastcbo_err_rrif_one_month_indicate_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RRIF_ONE_MONTH_INDICATE_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The %MONTH% in \"Monthly Indicator\" has to be set to \"Y\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The %MONTH% in \"Monthly Indicator\" has to be set to \"Y\".")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The %MONTH% in \"Monthly Indicator\" has to be set to \"Y\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le mois de %MONTH% de l'indicateur mensuel doit être réglé à Y.")); }

        // Actions
	};
}



