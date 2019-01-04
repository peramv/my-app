#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_cert_unit_not_enough : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_cert_unit_not_enough() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_cert_unit_not_enough() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_ACCT_CERT_UNIT_NOT_ENOUGH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("NOT enough Cert Units for account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("NOT enough Cert Units for account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Unités de certificat insuffisantes pour le compte.")); }

        // Actions
	};
}



