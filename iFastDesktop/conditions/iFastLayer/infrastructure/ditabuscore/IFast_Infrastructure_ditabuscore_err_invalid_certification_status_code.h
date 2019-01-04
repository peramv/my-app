#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ditabuscore_err_invalid_certification_status_code : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ditabuscore_err_invalid_certification_status_code() { }
		~CIFast_Infrastructure_ditabuscore_err_invalid_certification_status_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CERTIFICATION_STATUS_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The postal address certification status code is invalid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The postal address certification status code is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Postadressen-Bestätigungsstatus-Code ist ungültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de estado de certificación de dirección postal no es válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code du statut de certification de l'adresse postale est invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De code van de certificeringsstatus voor het postadres is ongeldig")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Valid values are Y and N.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Valid values are Y and N.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Gültige Werte sind J und N.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Los valores válidos son Y y N.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Les valeurs valides sont O et N.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Geldige waarden zijn J en N")); }
	};
}



