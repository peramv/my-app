#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ad_too_many_failed_logons : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ad_too_many_failed_logons() { }
		~CIFast_IFast_ifastdbrkr_err_ad_too_many_failed_logons() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_TOO_MANY_FAILED_LOGONS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - Too many failed logons.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Nombre trop eleve d'echecs de connexions")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Zu viele fehlgeschlagene Anmeldungen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - Demasiados intentos de conexión fallidos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – le maximum de tentatives d'ouverture de session a été atteint.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Te veel mislukte aanmeldingen")); }

        // Actions
	};
}



