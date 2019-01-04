#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_vision_err_no_initialized_service : public CConditionObject
	{
	public:
		CIFast_Infrastructure_vision_err_no_initialized_service() { }
		~CIFast_Infrastructure_vision_err_no_initialized_service() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_INITIALIZED_SERVICE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A required IDI string terminator is missing after %TAG_NAME%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("A required IDI string terminator is missing after %TAG_NAME%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein erforderliches IDI-String-Abschlusszeichen fehlt nach %TAG_NAME%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falta un terminador de cadena IDI obligatorio después de %TAG_NAME%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un terminateur de chaîne IDI requis est manquant après %TAG_NAME%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Een vereist beëindigingsteken voor de IDI-string ontbreekt na %TAG_NAME%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Add the terminator before the next IDI tag.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Add the terminator before the next IDI tag.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Fügen Sie das Abschlusszeichen vor dem nächsten IDI-Tag ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Add the terminator before the next IDI tag.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Ajoutez le terminateur avant le prochain marqueur IDI.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Voeg het beëindigingsteken toe voor de volgende IDI-tag")); }
	};
}



