#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicbocore_err_unable_to_retrieve_label_data : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicbocore_err_unable_to_retrieve_label_data() { }
		~CIFast_Infrastructure_dicbocore_err_unable_to_retrieve_label_data() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_RETRIEVE_LABEL_DATA")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to retrieve data for %LABEL%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to retrieve data for '^'")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Daten für %LABEL% können nicht ausgelesen werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible recuperar los datos para %LABEL%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de récupérer les données pour %LABEL%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens voor %LABEL% konden niet worden opgehaald")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den CBO-Code.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el código CBO.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code d'optimisation de coûts.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de CBO-code")); }
	};
}



