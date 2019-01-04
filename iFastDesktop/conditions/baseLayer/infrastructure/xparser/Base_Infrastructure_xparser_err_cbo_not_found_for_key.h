#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_xparser_err_cbo_not_found_for_key : public CConditionObject
	{
	public:
		CBase_Infrastructure_xparser_err_cbo_not_found_for_key() { }
		~CBase_Infrastructure_xparser_err_cbo_not_found_for_key() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CBO_NOT_FOUND_FOR_KEY")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not authorized to modify %FIELD% field.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Not authorized to modify '^' field.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sie sind nicht autorisiert, das Feld  %FIELD% zu ändern.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No está autorizado a modificar el campo %FIELD%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Non autorisé à modifier le champ %FIELD%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Niet gemachtigd om veld %FIELD% te wijzigen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Read-only fields cannot be updated.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Read-only fields cannot be updated.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Schreibgeschützte Felder können nicht aktualisiert werden.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Los campos de sólo lectura no se pueden actualizar.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Les champs à lecture seule ne peuvent être mis à jour.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("De velden die alleen kunnen worden gelezen, kunnen niet worden bijgewerkt")); }
	};
}



