#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_transitno_not_exist : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_transitno_not_exist() { }
		~CIFast_Infrastructure_ifastcbo_err_transitno_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSITNO_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error calling TA2000DataBroker: using duplicate HWND MSG for views. HWND: %hwnd%, MSG %msg%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Error calling TA2000DataBroker: using duplicate HWND MSG for views. HWND: %hwnd%, MSG %msg%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fehler beim Aufruf von TA2000DataBroker: doppelte HWND MSG werden zur Ansicht verwendet. HWND: %hwnd%, MSG %msg%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error al llamar TA2000DataBroker: se está usando un HWND MSG repetido para views. HWND: %hwnd%, MSG %msg%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur lors de l'appel du courtier des données TA2000 : utilisation du message et du HWND pour les affichages. HWND : %hwnd%, message : %msg%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fout bij oproepen van TA2000DataBroker: dubbele HWND MSG gebruikt voor views. HWND: %hwnd%, MSG %msg%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



