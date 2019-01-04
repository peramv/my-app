#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_dayofweek_required : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_dayofweek_required() { }
		~CIFast_Infrastructure_ifastcbo_err_dayofweek_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DAYOFWEEK_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Communication with host returned an unknown error code from WS00221C, Error = %error%, Location = %loc%, CICS return code is %CICSError%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Communication with host returned an unknown error code from WS00221C, Error = %error%, Location = %loc%, CICS return code is %CICSError%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kommunikation mit Host ergab einen unbekannten Fehlercode von WS00221C, Fehler = %error%, Ort = %loc%, CICS-Rückgabecode ist %CICSError%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La comunicación con el host devolvió un código de error desconocido de WS00221C, Error =  %error%, Lugar= %loc%, el código de retorno CICS es %CICSError%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La communication avec l'hôte a renvoyé un code d'erreur inconnu de WS00221C. Erreur : %error%, localisation : %loc%, code de renvoi CICS : %CICSError%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Communicatie met host heeft een onbekende fout gegenereerd van WS00221C, fout = %error%, locatie = %loc%, CICS retourcode is %CICSError%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify data entered. If entry is correct, contact a supervision and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify data entered. If entry is correct, contact a supervision and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die eingegebenen Daten. Wenn der Eintrag richtig ist, wenden Sie sich an einen Supervisor und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify data entered. If entry is correct, contact a supervision and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez les données saisies. Si elles sont exactes, communiquez avec un superviseur et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de ingevoerde gegevens. Als de invoer juist is, neemt u contact op met een supervisor en meldt u dit bericht")); }
	};
}



