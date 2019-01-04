﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_comm_rate_less_then_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_comm_rate_less_then_zero() { }
		~CIFast_IFast_ifastcbo_err_comm_rate_less_then_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COMM_RATE_LESS_THEN_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Commission rate should not be less than or equal to zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Commission rate should not be less than or equal to zero.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Commission rate should not be less than or equal to zero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux de commission ne devrait  pas être inférieur ou égal à zéro.")); }

        // Actions
	};
}



