#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_diawdi_diawdi_invalid_date_time_passed : public CConditionObject
	{
	public:
		CIFast_IFast_diawdi_diawdi_invalid_date_time_passed() { }
		~CIFast_IFast_diawdi_diawdi_invalid_date_time_passed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWDI_INVALID_DATE_TIME_PASSED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("diawdi")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Server didn't build the response correctly")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Server didn't build the response correctly")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Server hat die Antwort nicht richtig erstellt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El servidor no construyó la respuesta correctamente")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le serveur n'a pas correctement construit la réponse.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Server heeft de respons niet goed opgebouwd")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assistance technique.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker")); }
	};
}



