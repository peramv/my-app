#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_less_or_equal_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_less_or_equal_100() { }
		~CIFast_IFast_ifastcbo_err_fee_less_or_equal_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_LESS_OR_EQUAL_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee has to be less or equal to 100.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Fee has to be less or equal to 100.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provision muss kleiner oder gleich 100 sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La comisión debe ser inferior o igual a 100")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais doivent être inférieurs ou égaux à 100.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kosten moeten minder zijn dan of gelijk aan 100")); }

        // Actions
	};
}



