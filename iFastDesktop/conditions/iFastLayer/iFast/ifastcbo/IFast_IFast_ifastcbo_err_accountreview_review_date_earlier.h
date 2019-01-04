#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_accountreview_review_date_earlier : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_accountreview_review_date_earlier() { }
		~CIFast_IFast_ifastcbo_err_accountreview_review_date_earlier() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNTREVIEW_REVIEW_DATE_EARLIER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Review date must be after previous review date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Überprüfungsdatum muss nach dem vorigen Überprüfungsdatum liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de revisión debe ser posterior a la fecha de revisión anterior.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de révision doit être postérieure à la date de révision précédente.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Herzieningsdatum moet later zijn dan vorige herzieningsdatum")); }

        // Actions
	};
}



