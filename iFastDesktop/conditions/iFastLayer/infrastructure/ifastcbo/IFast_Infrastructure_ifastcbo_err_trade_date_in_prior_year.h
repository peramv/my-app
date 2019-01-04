#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_trade_date_in_prior_year : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_trade_date_in_prior_year() { }
		~CIFast_Infrastructure_ifastcbo_err_trade_date_in_prior_year() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_DATE_IN_PRIOR_YEAR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELD% must be populated.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%FIELD% must be populated.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELD% muss ausgefüllt sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El campo %FIELD% debe completarse.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %FIELD% doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELD% moet zijn ingevuld")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Supply a value.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Supply a value.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie einen Wert ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Supply a value.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Fournissez une valeur.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Geef een waarde op")); }
	};
}



