﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_w_invalid_sin : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_w_invalid_sin() { }
		~CIFast_Infrastructure_ifastcbo_err_w_invalid_sin() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_W_INVALID_SIN")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD logon was not successful. Operator ID is invalid.\n\nAWD Message: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD logon was not successful. Operator ID is invalid.\n\nAWD Message: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Anmeldung war nicht erfolgreich. Operator-ID ist ungültig.\n\nAWD-Meldung: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La conexión con AWD no fue exitosa. La identificación de operador no es válida.\n\nMensaje de AWD: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec d'ouverture de session AWD. Code d'opérateur invalide. \n\n Message AWD : %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aanmelden bij AWD is niet gelukt. Operator-ID is ongeldig.\n\n AWD-bericht: %AWD_ERROR_MESSAGE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify operator ID and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify operator ID and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Operator-ID und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify operator ID and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code d'opérateur et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het operator-ID en voer opnieuw in")); }
	};
}



