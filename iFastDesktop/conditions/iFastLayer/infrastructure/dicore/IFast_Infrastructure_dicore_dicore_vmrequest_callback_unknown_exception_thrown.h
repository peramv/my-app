#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicore_dicore_vmrequest_callback_unknown_exception_thrown : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicore_dicore_vmrequest_callback_unknown_exception_thrown() { }
		~CIFast_Infrastructure_dicore_dicore_vmrequest_callback_unknown_exception_thrown() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_VMREQUEST_CALLBACK_UNKNOWN_EXCEPTION_THROWN")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("VmRequest caught an unknown exception while calling a user-defined preprocessing callback function.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("VmRequest caught an unknown exception while calling a user-defined preprocessing callback function.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("VmRequest traf auf eine unbekannte Ausnahme beim Aufruf einer benutzerdefinierten vorbearbeitenden Rückruffunktion.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("VmRequest encontró una excepción desconocida al llamar una función de rellamada de retorno de preprocesamiento definida por el usuario.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La demande de gestionnaire de l'affichage a détecté une exception inconnue en appelant une fonction de rappel automatique de prétraitement définie par l'utilisateur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("VmRequest heeft een onbekende exceptie aangetroffen bij het oproepen van een door de gebruiker gedefinieerde voorverwerkings-terugroepfunctie")); }

        // Actions
	};
}



