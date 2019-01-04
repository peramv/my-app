#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_national_id_required_for_tax_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_national_id_required_for_tax_type() { }
		~CIFast_IFast_ifastcbo_err_national_id_required_for_tax_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NATIONAL_ID_REQUIRED_FOR_TAX_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("National Id is required for the tax type")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un code d'identification national est requis pour le type d'impôt.")); }

        // Actions
	};
}



