#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_has_no_inq_permission_for_settlement : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_has_no_inq_permission_for_settlement() { }
		~CIFast_IFast_ifastcbo_err_has_no_inq_permission_for_settlement() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_HAS_NO_INQ_PERMISSION_FOR_SETTLEMENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You don't have permission to inquire settlement for %SEARCH_TYPE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sie sind nicht berechtigt, die Abrechnung für %SEARCH_TYPE% zu untersuchen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Usted no tiene autorización para consultar la liquidación para %SEARCH_TYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous n'avez pas l'autorisation de demander un règlement pour %SEARCH_TYPE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("U hebt geen toestemming om betaling aan te vragen voor %SEARCH_TYPE%")); }

        // Actions
	};
}



