#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deposit_type_24_not_supported : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deposit_type_24_not_supported() { }
		~CIFast_IFast_ifastcbo_err_deposit_type_24_not_supported() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPOSIT_TYPE_24_NOT_SUPPORTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("For %TransTypeDescr% deposit type 24 is not currently supported.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("For %TransTypeDescr% deposit type 24 is not currently supported.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de dépôt 24 n'est pas supporté actuellement pour %TransTypeDescr%.")); }

        // Actions
	};
}



