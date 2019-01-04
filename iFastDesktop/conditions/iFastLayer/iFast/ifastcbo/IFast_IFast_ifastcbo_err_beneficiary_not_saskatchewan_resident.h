#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_beneficiary_not_saskatchewan_resident : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_beneficiary_not_saskatchewan_resident() { }
		~CIFast_IFast_ifastcbo_err_beneficiary_not_saskatchewan_resident() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BENEFICIARY_NOT_SASKATCHEWAN_RESIDENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bene tax jurisdiction must be 'SK' as of the Trade date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La juridiction fiscale doit être « SK » à la date de la transaction.")); }

        // Actions
	};
}



