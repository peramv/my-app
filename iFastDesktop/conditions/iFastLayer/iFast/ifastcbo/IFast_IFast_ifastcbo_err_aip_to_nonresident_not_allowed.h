#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_aip_to_nonresident_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_aip_to_nonresident_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_aip_to_nonresident_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AIP_TO_NONRESIDENT_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AIP withdrawal exists, payment to non-resident Owner is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Retrait PRA existant, le paiement à un titulaire non résident n'est pas autorisé.")); }

        // Actions
	};
}



