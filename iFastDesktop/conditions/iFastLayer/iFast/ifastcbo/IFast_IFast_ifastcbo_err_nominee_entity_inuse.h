#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_nominee_entity_inuse : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_nominee_entity_inuse() { }
		~CIFast_IFast_ifastcbo_err_nominee_entity_inuse() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOMINEE_ENTITY_INUSE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Nominee Owner entity is already in use. Salutation, last and first names cannot be changed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité titulaire nominée est déjà en cours d'utilisation. La salutation, les nom et prénom ne peuvent être changés.")); }

        // Actions
	};
}



