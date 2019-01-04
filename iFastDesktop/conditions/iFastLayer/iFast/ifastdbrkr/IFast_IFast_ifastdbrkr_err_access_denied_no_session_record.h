#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_access_denied_no_session_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_access_denied_no_session_record() { }
		~CIFast_IFast_ifastdbrkr_err_access_denied_no_session_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCESS_DENIED_NO_SESSION_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied. No session record.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Access denied. No session record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert. Kein Sitzungseintrag.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado. No hay registro de sesión.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé. Aucun enregistrement de session.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd. Geen sessierecord")); }

        // Actions
	};
}



