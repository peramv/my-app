#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bpbase_bp_err_duplicate_key_in_field_details : public CConditionObject
	{
	public:
		CBase_Infrastructure_bpbase_bp_err_duplicate_key_in_field_details() { }
		~CBase_Infrastructure_bpbase_bp_err_duplicate_key_in_field_details() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_DUPLICATE_KEY_IN_FIELD_DETAILS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("STS error.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("STS error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("STS-Fehler.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de STS.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur STS")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("STS-fout")); }

        // Actions
	};
}



