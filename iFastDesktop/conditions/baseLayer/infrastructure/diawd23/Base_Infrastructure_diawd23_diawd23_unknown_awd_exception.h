#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_diawd23_diawd23_unknown_awd_exception : public CConditionObject
	{
	public:
		CBase_Infrastructure_diawd23_diawd23_unknown_awd_exception() { }
		~CBase_Infrastructure_diawd23_diawd23_unknown_awd_exception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWD23_UNKNOWN_AWD_EXCEPTION")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("diawd23")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.\n\nAn unkown AWD exception was caught.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.\n\nAn unkown AWD exception was caught.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.\n\nEine unbekannte AWD-Ausnahme ist aufgetreten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.\n Se detectó una excepción de AWD desconocida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. \n\n Une exception AWD inconnue a été détectée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.\n\nEr is een onbekende AWD-exceptie aangetroffen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



