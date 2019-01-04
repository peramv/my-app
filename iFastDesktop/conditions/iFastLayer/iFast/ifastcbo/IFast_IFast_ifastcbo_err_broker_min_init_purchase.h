#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_broker_min_init_purchase : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_broker_min_init_purchase() { }
		~CIFast_IFast_ifastcbo_err_broker_min_init_purchase() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_MIN_INIT_PURCHASE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker: Less than minimum Initial Purchase amount.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Courtier : inférieur au montant d'achat initial minimal")); }

        // Actions
	};
}



