#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tr_invalid_red_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tr_invalid_red_code() { }
		~CIFast_IFast_ifastcbo_err_tr_invalid_red_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TR_INVALID_RED_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This code can be used only for transfer to RSP or RIF account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce code ne peut être utilisé que pour un transfert vers un compte RER ou FRR.")); }

        // Actions
	};
}



