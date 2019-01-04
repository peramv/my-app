#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_from_delivery_to_must_be_supplied_for_clearing_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_from_delivery_to_must_be_supplied_for_clearing_account() { }
		~CIFast_IFast_ifastcbo_err_from_delivery_to_must_be_supplied_for_clearing_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FROM_DELIVERY_TO_MUST_BE_SUPPLIED_FOR_CLEARING_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Delivery To is mandatory for From side of Settlement Instruction for Clearing Account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Delivery To is mandatory for a Clearing Account.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Delivery To is mandatory for a Clearing Account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Livraison à doit être rempli pour les instructions de règlement source du compte de compensation.")); }

        // Actions
	};
}



