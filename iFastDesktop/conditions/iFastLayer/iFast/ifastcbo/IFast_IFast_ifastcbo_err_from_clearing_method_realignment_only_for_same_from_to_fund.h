#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_from_clearing_method_realignment_only_for_same_from_to_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_from_clearing_method_realignment_only_for_same_from_to_fund() { }
		~CIFast_IFast_ifastcbo_err_from_clearing_method_realignment_only_for_same_from_to_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FROM_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Realignment Method for From side of Settlement Instruction allowed only for same From and To Fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Realignment Method for From side of Settlement Instruction allowed only for same From and To Fund.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Realignment Method for From side of Settlement Instruction allowed only for same From and To Fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La méthode de réalignement des instructions de règlement source n'est autorisée que pour les mêmes fonds source et cible.")); }

        // Actions
	};
}



