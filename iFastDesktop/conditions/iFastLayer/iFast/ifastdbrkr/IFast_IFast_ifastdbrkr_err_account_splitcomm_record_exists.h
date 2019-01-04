#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_account_splitcomm_record_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_account_splitcomm_record_exists() { }
		~CIFast_IFast_ifastdbrkr_err_account_splitcomm_record_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_SPLITCOMM_RECORD_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A record already exists for this entity.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein Eintrag für dieses Objekt  existiert bereits.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Ya existe un registro para esta entidad.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un enregistrement existe déjà pour cette entité.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er bestaat al een record voor deze eenheid")); }

        // Actions
	};
}



