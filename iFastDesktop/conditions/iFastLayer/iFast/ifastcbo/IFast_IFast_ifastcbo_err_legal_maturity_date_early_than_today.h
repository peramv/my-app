#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_legal_maturity_date_early_than_today : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_legal_maturity_date_early_than_today() { }
		~CIFast_IFast_ifastcbo_err_legal_maturity_date_early_than_today() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LEGAL_MATURITY_DATE_EARLY_THAN_TODAY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Legal Maturity Date must be later than today.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The Legal Maturity Date must be later than today.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das gesetzliche Fälligkeitsdatum muss hinter dem heutigen Datum liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de vencimiento legal debe ser posterior a la de hoy")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance légale doit être postérieure à la date actuelle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De wettelijke vervaldatum moet later zijn dan vandaag")); }

        // Actions
	};
}



