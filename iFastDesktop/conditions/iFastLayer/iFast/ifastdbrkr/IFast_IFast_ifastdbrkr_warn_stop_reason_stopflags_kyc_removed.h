#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_warn_stop_reason_stopflags_kyc_removed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_warn_stop_reason_stopflags_kyc_removed() { }
		~CIFast_IFast_ifastdbrkr_warn_stop_reason_stopflags_kyc_removed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_STOP_REASON_STOPFLAGS_KYC_REMOVED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account stop flags and stop reason Missing KYC (System) are removed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les signaux d'arrêt du compte et la raison d'arrêt Profil d'investisseur manquant (système) ont été retirés.")); }

        // Actions
	};
}



