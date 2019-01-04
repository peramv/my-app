#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_bank_master_del_on_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_bank_master_del_on_date() { }
		~CIFast_IFast_ifastdbrkr_err_bank_master_del_on_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BANK_MASTER_DEL_ON_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Can only delete on date bank master record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Can only delete on date bank master record.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Can only delete on date bank master record.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Suppression possible uniquement à la date de l'enregistrement principal de la banque")); }

        // Actions
	};
}



