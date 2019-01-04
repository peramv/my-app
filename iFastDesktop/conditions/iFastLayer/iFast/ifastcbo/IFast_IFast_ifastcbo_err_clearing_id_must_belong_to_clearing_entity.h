#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_clearing_id_must_belong_to_clearing_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_clearing_id_must_belong_to_clearing_entity() { }
		~CIFast_IFast_ifastcbo_err_clearing_id_must_belong_to_clearing_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLEARING_ID_MUST_BELONG_TO_CLEARING_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Clearing Platform Id must belong to Clearing Platform Entity.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de plateforme de compensation doit appartenir à l'entité de plateforme de compensation.")); }

        // Actions
	};
}



