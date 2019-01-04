#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_aggregation_ref_number_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_aggregation_ref_number_blank() { }
		~CIFast_IFast_ifastdbrkr_err_aggregation_ref_number_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AGGREGATION_REF_NUMBER_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Aggregation Reference Number cannot be blank")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aggregation Reference Number cannot be blank")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de référence de regroupement est requis.")); }

        // Actions
	};
}



