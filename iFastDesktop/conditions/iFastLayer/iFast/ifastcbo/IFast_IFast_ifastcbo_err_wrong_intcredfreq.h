#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_wrong_intcredfreq : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_wrong_intcredfreq() { }
		~CIFast_IFast_ifastcbo_err_wrong_intcredfreq() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WRONG_INTCREDFREQ")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Monthly is applicable only for Cash Rollover Type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La fréquence mensuelle ne s'applique qu'au roulement de type comptant.")); }

        // Actions
	};
}



