#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_address_used_for_mailing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_address_used_for_mailing() { }
		~CIFast_IFast_ifastdbrkr_err_address_used_for_mailing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDRESS_USED_FOR_MAILING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Address used for mailing.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Adresse utilisee pour mailing, veuillez la reaffecter.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Adresse wird für Mailing verwendet, bitte weisen Sie neu zu.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Dirección utilizada para correspondencia, por favor reasígnela.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Adresse postale")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Adres wordt gebruikt voor mailing, wijs opnieuw toe")); }

        // Actions
	};
}



