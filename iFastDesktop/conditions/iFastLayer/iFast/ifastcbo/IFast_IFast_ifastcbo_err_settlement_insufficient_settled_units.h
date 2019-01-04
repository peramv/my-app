#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_settlement_insufficient_settled_units : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_settlement_insufficient_settled_units() { }
		~CIFast_IFast_ifastcbo_err_settlement_insufficient_settled_units() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLEMENT_INSUFFICIENT_SETTLED_UNITS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Insufficient account holdings due to unsettled units.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Insufficient account holdings due to unsettled units.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le portefeuille du compte est insuffisant en raison d'unités non réglées.")); }

        // Actions
	};
}



