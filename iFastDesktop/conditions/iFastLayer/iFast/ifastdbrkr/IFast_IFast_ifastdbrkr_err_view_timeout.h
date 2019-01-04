#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_view_timeout : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_view_timeout() { }
		~CIFast_IFast_ifastdbrkr_err_view_timeout() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VIEW_TIMEOUT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("View %VIEWNAME% did not respond within %TIMEOUT% seconds.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("View %VIEWNAME% did not respond within %TIMEOUT% seconds.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("View %VIEWNAME% did not respond within %TIMEOUT% seconds.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La réponse de l'affichage %VIEWNAME% n'a pas été reçue avant %TIMEOUT% secondes.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique.")); }
	};
}



