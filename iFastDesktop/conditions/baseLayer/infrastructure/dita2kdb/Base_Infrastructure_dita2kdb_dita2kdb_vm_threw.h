#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_vm_threw : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_vm_threw() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_vm_threw() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_VM_THREW")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem because View Manager threw an exception. System: %sys%. Message: %msg%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem because View Manager threw an exception. System: %sys%. Message: %msg%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem, da der View Manager eine Ausnahme ausgegeben hat. System: %sys% Meldung: %msg%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno porque View Manager devolvió una excepción. Sistema: %sys%. Mensaje: %msg%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne parce que le gestionnaire de l'affichage a lancé une exception. Système : %sys%, message : %msg%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem omdat er een exceptie is opgetreden bij View Manager. Systeem: %sys%. Bericht: %msg%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



