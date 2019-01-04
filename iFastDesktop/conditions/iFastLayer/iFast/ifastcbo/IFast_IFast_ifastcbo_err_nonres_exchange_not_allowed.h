#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_nonres_exchange_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_nonres_exchange_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_nonres_exchange_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NONRES_EXCHANGE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("GIA/DIF Exchange transaction is not authorized for non-residents.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les transactions d'échange FIG/FIQ ne sont pas autorisées pour les non-résidents.")); }

        // Actions
	};
}



