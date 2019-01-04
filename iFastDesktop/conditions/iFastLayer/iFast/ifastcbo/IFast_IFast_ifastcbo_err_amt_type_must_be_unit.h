#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amt_type_must_be_unit : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amt_type_must_be_unit() { }
		~CIFast_IFast_ifastcbo_err_amt_type_must_be_unit() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMT_TYPE_MUST_BE_UNIT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount Type must be unit.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betragsart muss Anteil sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de monto debe ser una unidad.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de montant doit être en unités.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedragtype moet eenheid zijn")); }

        // Actions
	};
}



