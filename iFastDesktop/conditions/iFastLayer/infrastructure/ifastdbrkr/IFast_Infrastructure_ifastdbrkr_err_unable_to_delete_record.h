#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_unable_to_delete_record : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_unable_to_delete_record() { }
		~CIFast_Infrastructure_ifastdbrkr_err_unable_to_delete_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_DELETE_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Return information is unavailable.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. Return information is unavailable.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Ausgabe-Information ist nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. La información de retorno no está disponible.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. L'information sur le remboursement n'est pas disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Retourgegevens zijn niet beschikbaar")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



