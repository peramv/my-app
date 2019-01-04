#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_address_used_for_mailing : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_address_used_for_mailing() { }
		~CIFast_Infrastructure_ifastdbrkr_err_address_used_for_mailing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDRESS_USED_FOR_MAILING")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

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



