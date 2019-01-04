#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_entity_lastname_cannot_be_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_entity_lastname_cannot_be_blank() { }
		~CIFast_IFast_ifastcbo_err_entity_lastname_cannot_be_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTITY_LASTNAME_CANNOT_BE_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The last name for the entity should be entered at least one character.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The last name for the entity should be entered at least one character.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins un caractère devrait être saisi pour le nom de famille de l'entité.")); }

        // Actions
	};
}



