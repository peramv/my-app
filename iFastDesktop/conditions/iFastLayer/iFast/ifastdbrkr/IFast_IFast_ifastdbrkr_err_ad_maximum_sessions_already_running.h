#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ad_maximum_sessions_already_running : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ad_maximum_sessions_already_running() { }
		~CIFast_IFast_ifastdbrkr_err_ad_maximum_sessions_already_running() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_MAXIMUM_SESSIONS_ALREADY_RUNNING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - Maximum sessions already running.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Nombre maximum de sessions deja atteint")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Maximale Anzahl von laufenden Sitzungen wird überschritten")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - Ya se está ejecutando la cantidad máxima de sesiones")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – le nombre maximal de sessions en exécution a été atteint.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Maximumaantal sessies wordt al uitgevoerd")); }

        // Actions
	};
}



