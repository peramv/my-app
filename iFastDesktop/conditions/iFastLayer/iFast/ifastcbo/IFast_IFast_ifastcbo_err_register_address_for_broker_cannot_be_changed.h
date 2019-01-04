#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_register_address_for_broker_cannot_be_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_register_address_for_broker_cannot_be_changed() { }
		~CIFast_IFast_ifastcbo_err_register_address_for_broker_cannot_be_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REGISTER_ADDRESS_FOR_BROKER_CANNOT_BE_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Register broker address can not be changed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Register broker address can not be changed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'adresse du courtier enregistrée ne peut être changée.")); }

        // Actions
	};
}



