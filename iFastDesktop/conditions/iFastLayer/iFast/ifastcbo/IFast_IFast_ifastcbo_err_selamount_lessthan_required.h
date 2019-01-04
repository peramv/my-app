#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_selamount_lessthan_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_selamount_lessthan_required() { }
		~CIFast_IFast_ifastcbo_err_selamount_lessthan_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SELAMOUNT_LESSTHAN_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Selected Amount is less than minimum required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant sélectionné est inférieur au minimum requis.")); }

        // Actions
	};
}



