#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_entry_empty_or_contains_only_space : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_entry_empty_or_contains_only_space() { }
		~CIFast_Infrastructure_ifastcbo_err_entry_empty_or_contains_only_space() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

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



