#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_trustee_invalid_for_acct_type : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_trustee_invalid_for_acct_type() { }
		~CIFast_Infrastructure_ifastcbo_err_trustee_invalid_for_acct_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRUSTEE_INVALID_FOR_ACCT_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not authorized to modify %FIELD% field.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Not authorized to modify '^' field.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sie sind nicht autorisiert, das Feld  %FIELD% zu ändern.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No está autorizado a modificar el campo %FIELD%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Non autorisé à modifier le champ %FIELD%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Niet gemachtigd om veld %FIELD% te wijzigen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Read-only fields cannot be updated.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Read-only fields cannot be updated.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Schreibgeschützte Felder können nicht aktualisiert werden.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Read-only fields cannot be updated.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Les champs à lecture seule ne peuvent être mis à jour.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("De velden die alleen kunnen worden gelezen, kunnen niet worden bijgewerkt")); }
	};
}



