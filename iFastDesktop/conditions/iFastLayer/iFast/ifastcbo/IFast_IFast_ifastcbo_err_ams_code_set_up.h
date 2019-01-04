#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_code_set_up : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_code_set_up() { }
		~CIFast_IFast_ifastcbo_err_ams_code_set_up() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_CODE_SET_UP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS Code already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS-Code existiert bereits.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código AMS ya existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de service de gestion de portefeuille existe déjà.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("BBD-code bestaat al")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please input other value.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please input other value.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please input other value.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez saisir une autre valeur.")); }
	};
}



