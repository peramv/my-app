#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_dod_entity_type_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_dod_entity_type_missing() { }
		~CIFast_IFast_ifastcbo_err_dod_entity_type_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DOD_ENTITY_TYPE_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Date of Death of the %ENTITY_TYPE% missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de décès du type d'entité %ENTITY_TYPE% est manquante.")); }

        // Actions
	};
}



