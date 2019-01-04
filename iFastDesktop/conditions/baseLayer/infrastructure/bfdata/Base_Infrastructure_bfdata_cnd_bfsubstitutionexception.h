#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfdata_cnd_bfsubstitutionexception : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfdata_cnd_bfsubstitutionexception() { }
		~CBase_Infrastructure_bfdata_cnd_bfsubstitutionexception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("CND_BFSubstitutionException")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfdata")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Current Daily Dividend Rates File (A79) is not del.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Current Daily Dividend Rates File (A79) is not del.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tages-Dividendensatz-Datei (A79) ist nicht gelöscht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Current Daily Dividend Rates File (A79) is not del.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fichier des taux de dividende quotidiens actuels (A79) n'est pas supprimé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Current Daily Dividend Rates File (A79) is not del")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de servicio al cliente.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een medewerker van de klantendienst en meld dit bericht")); }
	};
}



