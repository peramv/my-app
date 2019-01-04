#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_settleindate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_settleindate() { }
		~CIFast_IFast_ifastcbo_err_invalid_settleindate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_SETTLEINDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settle In Date is before Settle Out Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de règlement entrant est antérieure à la date de règlement sortant.")); }

        // Actions
	};
}



