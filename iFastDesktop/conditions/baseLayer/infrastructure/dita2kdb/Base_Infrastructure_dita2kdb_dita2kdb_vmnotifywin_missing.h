#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_vmnotifywin_missing : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_vmnotifywin_missing() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_vmnotifywin_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_VMNOTIFYWIN_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error calling TA2000DataBroker: using unregistered hwnd and msg to receive a response from AWD/View. HWND MSG for views. HWND: %hwnd%, MSG %msg%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Error calling TA2000DataBroker: using unregistered hwnd and msg to receive a response from AWD/View. HWND MSG for views. HWND: %hwnd%, MSG %msg%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fehler beim Aufruf von TA2000DataBroker: nicht registrierte hwnd und msg werden verwendet, um eine Antwort von AWD/View zu erhalten. HWND MSG für Ansichten. HWND: %hwnd%, MSG %msg%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error al llamar TA2000DataBroker: se está usando un hwnd y msg no registrados para recibir una respuesta de AWD/View. HWND MSG para views. HWND: %hwnd%, MSG %msg%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur lors de l'appel du courtier des données TA2000 : utilisation du AWD et du message non enregistrés pour la réception d'une réponse d'AWD/de l'affichage. HWNDmessage pour les affichages, HWND : %hwnd%, message : %msg%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fout bij oproepen van TA2000DataBroker: ongeregistreerde hwnd en msg gebruikt om een respons van AWD-view te krijgen: HWND MSG voor views. HWND: %hwnd%, MSG %msg%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



