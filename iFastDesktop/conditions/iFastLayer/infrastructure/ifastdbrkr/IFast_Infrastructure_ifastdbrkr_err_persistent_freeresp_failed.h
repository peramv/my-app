#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_persistent_freeresp_failed : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_persistent_freeresp_failed() { }
		~CIFast_Infrastructure_ifastdbrkr_err_persistent_freeresp_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PERSISTENT_FREERESP_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Communication with host returned an error, DEADLOCK_ROLLED_BCK. CICS return code is %CICSError%, WS00221 return code is %error%, WS00221 return location is %loc%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Communication with host returned an error, DEADLOCK_ROLLED_BCK. CICS return code is %CICSError%, WS00221 return code is %error%, WS00221 return location is %loc%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kommunikation mit Host ergab einen Fehler, DEADLOCK_ROLLED_BCK. CICS-Rückgabecode ist %CICSError%, WS00221-Rückgabecode ist %error%, WS00221-Rückgabeort ist %loc%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La comunicación con el host devolvió un error, DEADLOCK_ROLLED_BCK. El código de retorno CICS es %CICSError%, el código de retorno WS00221 es %error%, la ubicación de retorno WS00221 es %loc%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La communication avec l'hôte a renvoyé une erreur, DEADLOCK_ROLLED_BCK. Le code de renvoi CICS est %CICSError%, le code de renvoi WS00221 est %error%, la localisation de renvoi WS00221 est %loc%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Communicatie met host heeft fout gegenereerd, DEADLOCK_ROLLED_BCK. CICS retourcode is %CICSError%, WS00221 retourcode is %error%, WS00221 retourlocatie is %loc%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify data entered. If entry is correct, contact a supervision and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify data entered. If entry is correct, contact a supervision and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die eingegebenen Daten. Wenn der Eintrag richtig ist, wenden Sie sich an einen Supervisor und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify data entered. If entry is correct, contact a supervision and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez les données saisies. Si elles sont exactes, communiquez avec un superviseur et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de ingevoerde gegevens. Als de invoer juist is, neemt u contact op met een supervisor en meldt u dit bericht")); }
	};
}



