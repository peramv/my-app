#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_aip_entity_not_canadien : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_aip_entity_not_canadien() { }
		~CIFast_IFast_ifastcbo_err_aip_entity_not_canadien() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AIP_ENTITY_NOT_CANADIEN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entity is not Canadian resident.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité n'est pas un résident canadien.")); }

        // Actions
	};
}



