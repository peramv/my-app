#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ad_after_mandatory_logoff_time : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ad_after_mandatory_logoff_time() { }
		~CIFast_IFast_ifastdbrkr_err_ad_after_mandatory_logoff_time() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_AFTER_MANDATORY_LOGOFF_TIME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - After mandatory logoff time.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Le temps de deconnexion obligatoire est depasse.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Nach der vorgeschriebenen Abmeldezeit.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - Después del tiempo de desconexión obligatorio")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – délai obligatoire de fermeture de session dépassé")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Na verplichte afmeldtijd")); }

        // Actions
	};
}



