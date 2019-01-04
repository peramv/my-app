#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_invalid_exch_red_canc : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_invalid_exch_red_canc() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_invalid_exch_red_canc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_EXCH_RED_CANC")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid exchange redemption cancel.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid exchange redemption cancel.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Devisentilgungswandlung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cancelación de rescate de traspaso no válida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Annulation de rachat d'échange invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige annulering ruilaflossing")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify entry. If entry is correct, contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify entry. If entry is correct, contact a supervisor and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Eintrag. Wenn der Eintrag richtig ist, wenden Sie sich an einen Supervisor und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify entry. If entry is correct, contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez la saisie. Si elle est correcte, communiquez avec un superviseur et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de invoer. Als de invoer juist is, neemt u contact op met een supervisor en meldt u dit bericht")); }
	};
}



