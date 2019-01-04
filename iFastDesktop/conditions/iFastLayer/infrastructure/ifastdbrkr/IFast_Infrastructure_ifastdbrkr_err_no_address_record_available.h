#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_no_address_record_available : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_no_address_record_available() { }
		~CIFast_Infrastructure_ifastdbrkr_err_no_address_record_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ADDRESS_RECORD_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid net change.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid net change.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Netto-Änderung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cambio neto no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Changement net invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige netto verandering")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Supervisor und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un superviseur et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supervisor en meld dit bericht")); }
	};
}



