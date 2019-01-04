#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicore_dicore_vmrequest_callback_conditionexception_thrown : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicore_dicore_vmrequest_callback_conditionexception_thrown() { }
		~CIFast_Infrastructure_dicore_dicore_vmrequest_callback_conditionexception_thrown() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_VMREQUEST_CALLBACK_CONDITIONEXCEPTION_THROWN")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("VmRequest caught a ConditionException while calling a user-defined preprocessing callback function. Original error: %ERROR%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("VmRequest caught a ConditionException while calling a user-defined preprocessing callback function. Original error: %ERROR%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("VmRequest traf auf eine Bedingungsausnahme beim Aufruf einer benutzerdefinierten vorbearbeitenden Rückruffunktion. Originalfehler: %ERROR%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("VmRequest encontró una excepción de condición al llamar una función de rellamada de retorno de preprocesamiento definida por el usuario. Error original: %ERROR%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La demande de gestionnaire de l'affichage a détecté une exception de condition en appelant une fonction de rappel automatique de prétraitement définie par l'utilisateur. Erreur d'origine : %ERROR%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("VmRequest heeft een voorwaardenexceptie aangetroffen bij het oproepen van een door de gebruiker gedefinieerde voorverwerkings-terugroepfunctie.  Oorspronkelijke fout: %ERROR%")); }

        // Actions
	};
}



