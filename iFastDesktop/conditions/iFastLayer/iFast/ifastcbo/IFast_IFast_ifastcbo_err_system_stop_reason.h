#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_system_stop_reason : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_system_stop_reason() { }
		~CIFast_IFast_ifastcbo_err_system_stop_reason() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SYSTEM_STOP_REASON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop reason Missing KYC (System) or Deceased (System) can be set only by the system.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La raison d'arrêt Profil d'investisseur manquant (système) ou Décédé (système) ne peut être réglée que par le système.")); }

        // Actions
	};
}



