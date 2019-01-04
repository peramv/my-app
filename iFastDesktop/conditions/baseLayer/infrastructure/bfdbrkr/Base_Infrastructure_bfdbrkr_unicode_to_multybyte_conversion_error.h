#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfdbrkr_unicode_to_multybyte_conversion_error : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfdbrkr_unicode_to_multybyte_conversion_error() { }
		~CBase_Infrastructure_bfdbrkr_unicode_to_multybyte_conversion_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("UNICODE_TO_MULTYBYTE_CONVERSION_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD logon was not successful. Operator already logged on.\n\nAWD Message: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD logon was not successful. Operator already logged on.\n\nAWD Message: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Anmeldung war nicht erfolgreich. Der Operator ist bereits angemeldet.\n\nAWD-Meldung: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La conexión con AWD no fue exitosa. El operador ya está conectado.\n\nMensaje de AWD: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec d'ouverture de session AWD. L'opérateur a déjà une session ouverte. \n\n Message AWD : %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aanmelden bij AWD is niet gelukt. Operator is al aangemeld.\n\nAWD-bericht: %AWD_ERROR_MESSAGE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify operator ID and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify operator ID and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Operator-ID und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique la identificación del operador y vuelva a introducirla.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code d'opérateur et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het operator-ID en voer opnieuw in")); }
	};
}



