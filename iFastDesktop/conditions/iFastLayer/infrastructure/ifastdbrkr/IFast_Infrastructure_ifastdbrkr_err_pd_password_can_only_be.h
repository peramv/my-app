#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_pd_password_can_only_be : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_pd_password_can_only_be() { }
		~CIFast_Infrastructure_ifastdbrkr_err_pd_password_can_only_be() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PD_PASSWORD_CAN_ONLY_BE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid exchange purchase cancel.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid exchange purchase cancel.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Devisenkaufwandlung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cancelación de traspaso de compra no válida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Annulation d'achat d'échange invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige annulering ruilaankoop")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify entry. If entry is correct, contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify entry. If entry is correct, contact a supervisor and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Eintrag. Wenn der Eintrag richtig ist, wenden Sie sich an einen Supervisor und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify entry. If entry is correct, contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez la saisie. Si elle est correcte, communiquez avec un superviseur et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de invoer. Als de invoer juist is, neemt u contact op met een supervisor en meldt u dit bericht")); }
	};
}



