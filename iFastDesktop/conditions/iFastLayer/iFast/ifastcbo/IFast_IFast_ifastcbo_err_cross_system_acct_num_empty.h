#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cross_system_acct_num_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cross_system_acct_num_empty() { }
		~CIFast_IFast_ifastcbo_err_cross_system_acct_num_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CROSS_SYSTEM_ACCT_NUM_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cross System Account Number is blank.")); }
        virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro de compte Système Croix est vide.")); }
        virtual DString GetMessage_FR_FR() const { return DString(I_("Numéro de compte Système Croix est vide.")); }
        // Actions
	};
}