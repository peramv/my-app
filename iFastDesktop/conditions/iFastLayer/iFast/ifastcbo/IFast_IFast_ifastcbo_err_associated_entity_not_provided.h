#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_associated_entity_not_provided : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_associated_entity_not_provided() { }
		~CIFast_IFast_ifastcbo_err_associated_entity_not_provided() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ASSOCIATED_ENTITY_NOT_PROVIDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Associated entity not provided.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité associée n'est pas fournie.")); }

        // Actions
	};
}



