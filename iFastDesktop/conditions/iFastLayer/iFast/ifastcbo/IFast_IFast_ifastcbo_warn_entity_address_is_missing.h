﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_entity_address_is_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_entity_address_is_missing() { }
		~CIFast_IFast_ifastcbo_warn_entity_address_is_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ENTITY_ADDRESS_IS_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entity address is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'adresse de l'entité est manquante.")); }

        // Actions
	};
}



