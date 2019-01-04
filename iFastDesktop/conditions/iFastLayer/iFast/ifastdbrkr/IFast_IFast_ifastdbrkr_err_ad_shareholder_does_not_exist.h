#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ad_shareholder_does_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ad_shareholder_does_not_exist() { }
		~CIFast_IFast_ifastdbrkr_err_ad_shareholder_does_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_SHAREHOLDER_DOES_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - Shareholder does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Actionnaire n'existe pas")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Aktionär existiert nicht")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - El accionista no existe")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – actionnaire inexistant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Aandeelhouder bestaat niet")); }

        // Actions
	};
}



