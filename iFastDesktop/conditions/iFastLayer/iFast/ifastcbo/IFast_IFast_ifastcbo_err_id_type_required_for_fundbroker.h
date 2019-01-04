#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_id_type_required_for_fundbroker : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_id_type_required_for_fundbroker() { }
		~CIFast_IFast_ifastcbo_err_id_type_required_for_fundbroker() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ID_TYPE_REQUIRED_FOR_FUNDBROKER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The identification information %IDS% is required for the fund broker.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The identification information %IDS% is required for the fund broker.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information d'identification %IDS% du courtier en fonds est requise.")); }

        // Actions
	};
}



