#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_tfsa_acct_status_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_tfsa_acct_status_changed() { }
		~CIFast_IFast_ifastcbo_warn_tfsa_acct_status_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TFSA_ACCT_STATUS_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please create amendment record upon change of account status.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez créer un enregistrement de modification lors du changement du statut du compte.")); }

        // Actions
	};
}



