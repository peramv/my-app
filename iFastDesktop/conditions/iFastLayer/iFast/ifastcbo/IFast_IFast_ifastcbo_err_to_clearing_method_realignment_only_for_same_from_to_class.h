#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_to_clearing_method_realignment_only_for_same_from_to_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_to_clearing_method_realignment_only_for_same_from_to_class() { }
		~CIFast_IFast_ifastcbo_err_to_clearing_method_realignment_only_for_same_from_to_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TO_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Realignment Method for To side of Settlement Instruction allowed only for same From and To Class.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Realignment Method for To side of Settlement Instruction allowed only for same From and To Class.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Realignment Method for To side of Settlement Instruction allowed only for same From and To Class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La méthode de réalignement des instructions de règlement cible n'est autorisée que pour les mêmes classes source et cible.")); }

        // Actions
	};
}



