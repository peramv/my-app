#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicbocore_err_cbe_label_invalid_for_update : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicbocore_err_cbe_label_invalid_for_update() { }
		~CIFast_Infrastructure_dicbocore_err_cbe_label_invalid_for_update() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CBE_LABEL_INVALID_FOR_UPDATE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Update invalid for %LABEL%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Update invalid for '^'")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aktualisierung ungültig für %LABEL%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Actualización no válida para %LABEL%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mise à jour invalide pour %LABEL%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bijwerken ongeldig voor %LABEL%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify that event is valid.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify that event is valid.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie, ob das Ereignis gültig ist.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify that event is valid.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez que l'événement est valide.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer of de gebeurtenis geldig is")); }
	};
}



