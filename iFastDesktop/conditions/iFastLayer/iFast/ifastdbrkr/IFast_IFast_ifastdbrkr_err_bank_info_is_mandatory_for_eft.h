#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_bank_info_is_mandatory_for_eft : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_bank_info_is_mandatory_for_eft() { }
		~CIFast_IFast_ifastdbrkr_err_bank_info_is_mandatory_for_eft() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BANK_INFO_IS_MANDATORY_FOR_EFT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank information is mandatory for EFT purchases.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bankinformation ist  für EFT-Käufe obligatorisch.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La información de banco es obligatoria para compras EFT")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information bancaire est requise pour les achats TEF.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bankgegevens zijn verplicht voor EFO-aankoop")); }

        // Actions
	};
}



