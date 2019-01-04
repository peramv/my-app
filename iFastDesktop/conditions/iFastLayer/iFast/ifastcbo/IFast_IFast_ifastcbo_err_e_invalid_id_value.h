#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_e_invalid_id_value : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_e_invalid_id_value() { }
		~CIFast_IFast_ifastcbo_err_e_invalid_id_value() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_E_INVALID_ID_VALUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("ID Value is invalid.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Valeur de code invalide")); }

        // Actions
	};
}



