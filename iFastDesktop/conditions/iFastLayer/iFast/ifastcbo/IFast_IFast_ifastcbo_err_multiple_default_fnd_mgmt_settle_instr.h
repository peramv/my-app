#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_multiple_default_fnd_mgmt_settle_instr : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_multiple_default_fnd_mgmt_settle_instr() { }
		~CIFast_IFast_ifastcbo_err_multiple_default_fnd_mgmt_settle_instr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_DEFAULT_FND_MGMT_SETTLE_INSTR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple default items assigned for fund mgmt settlement instruction")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Multiple default items assigned for fund mgmt settlement instruction")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plusieurs éléments par défaut sont attribués aux instructions de règlement de la gestion de fonds.")); }

        // Actions
	};
}



