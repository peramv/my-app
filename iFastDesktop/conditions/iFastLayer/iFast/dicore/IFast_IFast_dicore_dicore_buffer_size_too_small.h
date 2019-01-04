#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_dicore_buffer_size_too_small : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_dicore_buffer_size_too_small() { }
		~CIFast_IFast_dicore_dicore_buffer_size_too_small() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_BUFFER_SIZE_TOO_SMALL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Run Mode not valid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Run Mode not valid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Laufmodus ungültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El modo de ejecución no es válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mode exécution invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Uitvoeringsmodus is niet geldig")); }

        // Actions
	};
}



