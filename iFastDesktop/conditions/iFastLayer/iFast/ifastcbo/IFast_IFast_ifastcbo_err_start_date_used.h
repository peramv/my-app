#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_start_date_used : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_start_date_used() { }
		~CIFast_IFast_ifastcbo_err_start_date_used() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_START_DATE_USED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The results returned used a start date of %DATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für die zurückgegebenen Resultate wurde ein Startdatum vom %DATE% verwendet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los resultados devolvieron una fecha de inicio de %DATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de début des résultats renvoyés était le %DATE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het teruggestuurde resultaat gebruikte de begindatum %DATE%")); }

        // Actions
	};
}



