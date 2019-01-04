#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_dicore_save_key_fail : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_dicore_save_key_fail() { }
		~CIFast_IFast_dicore_dicore_save_key_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_SAVE_KEY_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Id Type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Id Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger ID-Typ.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de identificación no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de code invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig ID-type")); }

        // Actions
	};
}



