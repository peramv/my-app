#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_contract_type_and_version_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_contract_type_and_version_required() { }
		~CIFast_IFast_ifastcbo_warn_contract_type_and_version_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CONTRACT_TYPE_AND_VERSION_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract Type %CONTRACT_TYPE% and Contract Version %CONTRACT_VERSION% need to be setup first.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La type de contrat %CONTRACT_TYPE% et la version de contrat %CONTRACT_VERSION% doivent d'abord être réglés.")); }

        // Actions
	};
}



