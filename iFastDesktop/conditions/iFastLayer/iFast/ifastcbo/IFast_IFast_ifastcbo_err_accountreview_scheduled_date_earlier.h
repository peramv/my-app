#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_accountreview_scheduled_date_earlier : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_accountreview_scheduled_date_earlier() { }
		~CIFast_IFast_ifastcbo_err_accountreview_scheduled_date_earlier() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNTREVIEW_SCHEDULED_DATE_EARLIER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Scheduled date must be after previous scheduled date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Terminvorgabe muss nach der vorigen Terminvorgabe liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha programada debe ser posterior a la fecha programada anterior.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date fixe doit être postérieure à la date fixe précédente.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geplande datum moet later zijn dan vorige geplande datum")); }

        // Actions
	};
}



