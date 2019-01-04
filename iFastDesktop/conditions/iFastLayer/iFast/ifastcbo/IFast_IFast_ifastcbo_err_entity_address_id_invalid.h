#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_entity_address_id_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_entity_address_id_invalid() { }
		~CIFast_IFast_ifastcbo_err_entity_address_id_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTITY_ADDRESS_ID_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entity Address ID can be 0 or a valid existing Address ID.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Entity Address ID can be 0 or a valid existing Address ID.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code d'adresse de l'entité peut être 0 ou un code d'adresse valide existant.")); }

        // Actions
	};
}



