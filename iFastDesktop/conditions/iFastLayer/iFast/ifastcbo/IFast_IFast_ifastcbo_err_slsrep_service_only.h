#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_slsrep_service_only : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_slsrep_service_only() { }
		~CIFast_IFast_ifastcbo_err_slsrep_service_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SERVICE_ONLY_SALES_REP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Service Only SlsRep is not permitted for new accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Service uniquement représentant des ventes ne sont pas autorisées pour les nouveaux comptes.")); }

        // Actions
	};
}



