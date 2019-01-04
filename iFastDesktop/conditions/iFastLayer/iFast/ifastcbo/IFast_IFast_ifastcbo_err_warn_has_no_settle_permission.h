#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_has_no_settle_permission : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_has_no_settle_permission() { }
		~CIFast_IFast_ifastcbo_err_warn_has_no_settle_permission() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_HAS_NO_SETTLE_PERMISSION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You don't have permission to settle trade for %SEARCH_TYPE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sie haben keine Erlaubnis, den Handel für %SEARCH_TYPE% abzurechnen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Usted no tiene autorización para liquidar la operación para %SEARCH_TYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous n'avez pas l'autorisation de régler la transaction pour %SEARCH_TYPE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("U hebt geen toestemming om handel te betalen voor %SEARCH_TYPE%")); }

        // Actions
	};
}



