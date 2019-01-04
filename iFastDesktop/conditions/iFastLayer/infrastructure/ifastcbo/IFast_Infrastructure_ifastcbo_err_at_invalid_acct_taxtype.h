#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_at_invalid_acct_taxtype : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_at_invalid_acct_taxtype() { }
		~CIFast_Infrastructure_ifastcbo_err_at_invalid_acct_taxtype() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AT_INVALID_ACCT_TAXTYPE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid time format.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid time format.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Zeitformat.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Formato de hora no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Format de temps invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige tijdnotatie")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Enter a time with HH:MM:SS:DD format.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Enter a time with HH:MM:SS:DD format.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie eine Zeit im Format ST:MM:SS:TT ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Enter a time with HH:MM:SS:DD format.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Entrez une heure en format HH:MM:SS.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Geef een tijd op in de notatie UU:MM:SS:DD")); }
	};
}



