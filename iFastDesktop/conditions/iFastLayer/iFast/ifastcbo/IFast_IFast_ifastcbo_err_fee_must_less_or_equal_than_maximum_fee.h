#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_must_less_or_equal_than_maximum_fee : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_must_less_or_equal_than_maximum_fee() { }
		~CIFast_IFast_ifastcbo_err_fee_must_less_or_equal_than_maximum_fee() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_MUST_LESS_OR_EQUAL_THAN_MAXIMUM_FEE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee must less or equal than maximum fee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provision muss kleiner oder gleich der maximalen Provision sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La comisión debe ser inferior o igual a la comisión máxima.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais doivent être inférieurs ou égaux aux frais maximaux.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kosten moeten minder zijn dan of gelijk aan de maximumkosten")); }

        // Actions
	};
}



