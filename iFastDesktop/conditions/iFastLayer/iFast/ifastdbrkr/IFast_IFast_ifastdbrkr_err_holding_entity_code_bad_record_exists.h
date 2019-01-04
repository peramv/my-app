#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_holding_entity_code_bad_record_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_holding_entity_code_bad_record_exists() { }
		~CIFast_IFast_ifastdbrkr_err_holding_entity_code_bad_record_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_HOLDING_ENTITY_CODE_BAD_RECORD_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Holding Entity record with same Holding Company code is already deleted.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L’enregistrement de l’entité de portefeuille du même code de société de portefeuille a déjà été supprimé.")); }

        // Actions
	};
}



