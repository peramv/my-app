#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transfer_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transfer_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_transfer_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer from fund %FromFund%, class %FromClass% to fund %ToFund%, class %ToClass% is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transfer from fund %FromFund%, class %FromClass% to fund %ToFund%, class %ToClass% is not allowed.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Transfer from fund %FromFund%, class %FromClass% to fund %ToFund%, class %ToClass% is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un transfert du fonds %FromFund% et de la classe %FromClass% au fonds %ToFund% et à la classe %ToClass% n'est pas autorisé.")); }

        // Actions
	};
}



