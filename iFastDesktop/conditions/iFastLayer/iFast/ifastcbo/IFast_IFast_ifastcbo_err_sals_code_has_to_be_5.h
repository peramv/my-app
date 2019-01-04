#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_sals_code_has_to_be_5 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_sals_code_has_to_be_5() { }
		~CIFast_IFast_ifastcbo_err_sals_code_has_to_be_5() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SALS_CODE_HAS_TO_BE_5")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sales rep code can not be longer than 5 characters.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sales rep code can not be longer than 5 characters.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de représentant des ventes ne peut être composé de plus de 5 caractères.")); }

        // Actions
	};
}



