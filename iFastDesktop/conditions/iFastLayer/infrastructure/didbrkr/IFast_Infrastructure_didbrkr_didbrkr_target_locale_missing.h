#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_target_locale_missing : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_target_locale_missing() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_target_locale_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_TARGET_LOCALE_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to find ClientLocale object with locale (%locale%), market (%market%), and client (%client%) as redirection target.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to find ClientLocale object with locale (%locale%), market (%market%), and client (%client%) as redirection target.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das ClientLocale-Objekt mit Locale (%locale%), Markt (%market%) und Client (%client%) als Umleitungsziel kann nicht gefunden werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible encontrar el objeto ClientLocale con local (%locale%), mercado (%market%) y cliente (%client%) como meta de redireccionamiento.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de trouver l'objet de localisation du client avec la localisation (%locale%), le marché (%market%) et le client (%client%) comme cible de réacheminement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Taal/landcode klant-object met taal- en landcode (%locale%), markt (%market%) en klant (%client%) als doel voor doorsturen kon niet worden gevonden")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and relay this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a support representative and relay this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und geben Sie die Meldung an ihn weiter.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and relay this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et transmettez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



