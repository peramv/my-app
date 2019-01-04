#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_invalid_class_code : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_invalid_class_code() { }
		~CIFast_Infrastructure_ifastdbrkr_err_invalid_class_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CLASS_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Change record not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Change record not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Änderungseintrag nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el registro de cambio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Enregistrement de changement introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wijzigingsrecord is niet gevonden")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Supervisor und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un superviseur et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supervisor en meld dit bericht")); }
	};
}



