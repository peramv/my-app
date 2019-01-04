#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transfer_between_rrsp_indiv_and_rrsp_spousal_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transfer_between_rrsp_indiv_and_rrsp_spousal_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_transfer_between_rrsp_indiv_and_rrsp_spousal_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_BETWEEN_RRSP_INDIV_AND_RRSP_SPOUSAL_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer between RRSP individual and RRSP spousal accounts is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transfer between RRSP individual and RRSP spousal accounts is not allowed.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Transfer between RRSP individual and RRSP spousal accounts is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un transfert entre des comptes REER individuel et REER conjoint n'est pas autorisé.")); }

        // Actions
	};
}



