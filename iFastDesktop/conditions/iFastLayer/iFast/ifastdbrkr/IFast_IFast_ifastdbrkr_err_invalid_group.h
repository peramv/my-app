#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_group : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_group() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_group() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_GROUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Group.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Group.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Gruppe")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Grupo no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Groupe invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige groep")); }

        // Actions
	};
}



