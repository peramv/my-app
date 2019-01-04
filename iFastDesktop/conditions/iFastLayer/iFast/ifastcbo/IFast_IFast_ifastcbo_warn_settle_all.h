#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_settle_all : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_settle_all() { }
		~CIFast_IFast_ifastcbo_warn_settle_all() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SETTLE_ALL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("All trades will be settled including Transfers and Exchanges regardeless of settlement date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Toutes les transactions seront réglées, y compris les transferts et échanges, quelle que soit la date de règlement.")); }

        // Actions
	};
}



