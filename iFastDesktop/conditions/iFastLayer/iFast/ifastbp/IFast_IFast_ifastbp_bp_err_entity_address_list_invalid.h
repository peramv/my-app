#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_entity_address_list_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_entity_address_list_invalid() { }
		~CIFast_IFast_ifastbp_bp_err_entity_address_list_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_ENTITY_ADDRESS_LIST_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entity Address List is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Entity Address List is invalid.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La liste d'adresse de l'entité est invalide.")); }

        // Actions
	};
}



