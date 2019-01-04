#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_clearing_platform_id_type_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_clearing_platform_id_type_required() { }
		~CIFast_IFast_ifastcbo_err_clearing_platform_id_type_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLEARING_PLATFORM_ID_TYPE_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Clearing Platform ID is required for Clearing Platform Entity.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de plateforme de compensation est requis pour l'entité de plateforme de compensation.")); }

        // Actions
	};
}



