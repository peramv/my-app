#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfdbrkr_multybyte_to_unicode_conversion_error : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfdbrkr_multybyte_to_unicode_conversion_error() { }
		~CBase_Infrastructure_bfdbrkr_multybyte_to_unicode_conversion_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("MULTYBYTE_TO_UNICODE_CONVERSION_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD logon was not successful. Password is invalid.\n\nAWD Message: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD logon was not successful. Password is invalid.\n\nAWD Message: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Anmeldung war nicht erfolgreich. Das Kennwort ist ungültig.\n\nAWD-Meldung: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La conexión con AWD no fue exitosa. La contraseña no es válida.\n\nMensaje de AWD: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec d'ouverture de session AWD. Mot de passe invalide. \n\n Message AWD : %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aanmelden bij AWD is niet gelukt. Wachtwoord is ongeldig.\n\n AWD-bericht: %AWD_ERROR_MESSAGE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify password and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify password and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das Kennwort und geben Sie es erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique la contraseña y vuelva a introducirla.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le mot de passe et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het wachtwoord en voer dit opnieuw in")); }
	};
}



