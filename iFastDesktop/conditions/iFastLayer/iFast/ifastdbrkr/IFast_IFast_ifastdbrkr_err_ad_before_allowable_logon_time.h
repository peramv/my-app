#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ad_before_allowable_logon_time : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ad_before_allowable_logon_time() { }
		~CIFast_IFast_ifastdbrkr_err_ad_before_allowable_logon_time() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_BEFORE_ALLOWABLE_LOGON_TIME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - Before allowable logon time.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Precede le temps de connexion autorisé")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Vor der zulässigen Anmeldezeit.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - Antes del tiempo de conexión permitido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – antérieur au délai d'ouverture de session disponible")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Vóór toegestane aanmeldtijd")); }

        // Actions
	};
}



