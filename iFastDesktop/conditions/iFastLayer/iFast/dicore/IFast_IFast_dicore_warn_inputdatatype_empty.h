#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_warn_inputdatatype_empty : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_warn_inputdatatype_empty() { }
		~CIFast_IFast_dicore_warn_inputdatatype_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INPUTDATATYPE_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund invalid for registered account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Fund invalid for registered account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds für Ausländerkonten ungültig")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fondo no válido para la cuenta registrada")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fonds invalide pour le compte enregistré")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds is ongeldig voor registeraccount")); }

        // Actions
	};
}



