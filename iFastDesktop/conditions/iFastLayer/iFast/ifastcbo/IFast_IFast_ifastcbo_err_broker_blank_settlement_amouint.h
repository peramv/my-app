#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_broker_blank_settlement_amouint : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_broker_blank_settlement_amouint() { }
		~CIFast_IFast_ifastcbo_err_broker_blank_settlement_amouint() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_BLANK_SETTLEMENT_AMOUINT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker settlement amount cannot be blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Broker settlement amount cannot be blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de règlement du courtier est requis.")); }

        // Actions
	};
}



