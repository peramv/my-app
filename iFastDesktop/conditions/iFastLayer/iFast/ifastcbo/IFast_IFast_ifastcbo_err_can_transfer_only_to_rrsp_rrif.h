﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_can_transfer_only_to_rrsp_rrif : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_can_transfer_only_to_rrsp_rrif() { }
		~CIFast_IFast_ifastcbo_err_can_transfer_only_to_rrsp_rrif() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CAN_TRANSFER_ONLY_TO_RRSP_RRIF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("From this account you can transfer only to RRSP or RRIF account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Von diesem Konto können Sie nur auf ein RRSP oder RRIF-Konto transferieren.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Desde esta cuenta sólo se puede transferir a una cuenta RRSP o RRIF.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("À partir de ce compte, vous ne pouvez transférer que vers un compte REER ou FERR.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vanuit dit account kunt u alleen overdragen naar een RRSP- of RRIF-account")); }

        // Actions
	};
}



