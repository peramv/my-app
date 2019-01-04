#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cannot_modify_a_bad_rec : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cannot_modify_a_bad_rec() { }
		~CIFast_IFast_ifastdbrkr_err_cannot_modify_a_bad_rec() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_MODIFY_A_BAD_REC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot modify a bad record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Cannot modify a bad record.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cannot modify a bad record.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de modifier un enregistrement Mauvais.")); }

        // Actions
	};
}



