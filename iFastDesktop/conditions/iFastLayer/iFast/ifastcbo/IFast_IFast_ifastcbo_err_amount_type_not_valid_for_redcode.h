#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_type_not_valid_for_redcode : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_type_not_valid_for_redcode() { }
		~CIFast_IFast_ifastcbo_err_amount_type_not_valid_for_redcode() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_TYPE_NOT_VALID_FOR_REDCODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount type %AMTYPE% not valid for redemption code %REDCODE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de montant %AMTYPE% est invalide pour le code de rachat %REDCODE%.")); }

        // Actions
	};
}



