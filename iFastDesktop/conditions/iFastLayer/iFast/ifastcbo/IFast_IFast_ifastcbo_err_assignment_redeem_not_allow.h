#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_assignment_redeem_not_allow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_assignment_redeem_not_allow() { }
		~CIFast_IFast_ifastcbo_err_assignment_redeem_not_allow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ASSIGNMENT_REDEEM_NOT_ALLOW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Assignment reason does not allow redemption.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tilgung wegen Zuweisungs-Begründung nicht möglich")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El motivo de la cesión no permite rescates")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La raison de la mise en garantie n'autorise pas un rachat.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toewijzingsreden staat aflossing niet toe")); }

        // Actions
	};
}



