#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_invalid_char : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_invalid_char() { }
		~CIFast_Infrastructure_ifastcbo_err_invalid_char() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CHAR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Maximum amount of data requested is reached.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. Maximum amount of data requested is reached.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Die maximale Menge an angeforderten Daten ist erreicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. Se alcanzó la cantidad máxima de datos solicitados.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. La quantité maximale de données demandées est atteinte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. De maximale hoeveelheid aan te vragen gegevens is bereikt")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



