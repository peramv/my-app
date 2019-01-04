﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_change_all_market_mailing : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_change_all_market_mailing() { }
		~CIFast_Infrastructure_ifastcbo_err_change_all_market_mailing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CHANGE_ALL_MARKET_MAILING")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 4; }

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



