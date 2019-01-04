#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastbp_bp_no_access_to_acctdetails : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastbp_bp_no_access_to_acctdetails() { }
		~CIFast_Infrastructure_ifastbp_bp_no_access_to_acctdetails() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_NO_ACCESS_TO_ACCTDETAILS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("VmRequest encountered an error calling a user-defined preprocessing callback function. Original component: %COMPONENT% Original code: %RC%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("VmRequest encountered an error calling a user-defined preprocessing callback function. Original component: %COMPONENT% Original code: %RC%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("VmRequest traf auf einen Fehler beim Aufruf einer benutzerdefinierten vorbearbeitenden Rückruffunktion. Originalkomponente : %COMPONENT% Originalcode: %RC%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("VmRequest encontró un error al llamar una función de rellamada de retorno de preprocesamiento definida por el usuario. Componente original: %COMPONENT%  Código original: %RC%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La demande de gestionnaire de l'affichage a détecté une erreur en appelant une fonction de rappel automatique de prétraitement définie par l'utilisateur. Élément d'origine : %COMPONENT%, code d'origine : %RC%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("VmRequest heeft een fout aangetroffen bij het oproepen van een door de gebruiker gedefinieerde voorverwerkings-terugroepfunctie. Oorspronkelijke component: %COMPONENT% Oorspronkelijke code: %RC%")); }

        // Actions
	};
}



