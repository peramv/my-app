#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_pd_only_one_repetition_of_chars_allowed : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_pd_only_one_repetition_of_chars_allowed() { }
		~CIFast_Infrastructure_ifastdbrkr_err_pd_only_one_repetition_of_chars_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PD_ONLY_ONE_REPETITION_OF_CHARS_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid purchase cancel.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid purchase cancel.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Kaufwandlung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cancelación de compra no válida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Annulation d'achat invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige aankoopannulering")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify entry. If entry is correct, contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify entry. If entry is correct, contact a supervisor and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Eintrag. Wenn der Eintrag richtig ist, wenden Sie sich an einen Supervisor und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify entry. If entry is correct, contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez la saisie. Si elle est correcte, communiquez avec un superviseur et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de invoer. Als de invoer juist is, neemt u contact op met een supervisor en meldt u dit bericht")); }
	};
}



